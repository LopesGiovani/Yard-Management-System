#include "operacoes.h"
#include "dados.h"
#include "structs.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

static void limparBuffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF);

}

const char *traduzirStatusOperacao(StatusOperacao status)
{
    switch (status)
    {
    case PENDENTE:
        return "PENDENTE";
    case ATIVA:
        return "ATIVA";
    case CONCLUIDA:
        return "CONCLUIDA";
    case CANCELADA:
        return "CANCELADA";
    default:
        return "DESCONHECIDO";
    }
}

// Retorna o indice do registro com aquele codigo, ou -1 se nao encontrar
int buscarIndicePorCodigo(Operacao *operacoes, int totalOperacoes, char *codigoOperacao)
{
    for (int i = 0; i < totalOperacoes; i++)
    {
        if (strcmp(operacoes[i].codigoOperacao, codigoOperacao) == 0)
            return i;
    }
    return -1;
}

void cadastrarOperacao(Operacao **operacoes, int *totalOperacoes, Caminhao *caminhoes, int totalCaminhoes, Doca *docas, int totalDocas, int *capOperacoes)
{
    if (*totalOperacoes >= *capOperacoes)
    {
        int novaCap = *capOperacoes + EXTRA;
        Operacao *temp = realloc(*operacoes, novaCap * sizeof(Operacao));

        if (temp == NULL)
        {
            printf("\nERRO: Falha ao realocar memoria para operacoes!\n");
            return;
        }

        *operacoes = temp;
        *capOperacoes = novaCap;
    }

    Operacao nova;

    printf("\n--- Cadastrar Operacao ---\n");
    printf("Codigo da operacao (ex: OP010): ");

    fgets(nova.codigoOperacao, sizeof(nova.codigoOperacao), stdin);
    nova.codigoOperacao[strcspn(nova.codigoOperacao, "\n")] = 0;

    if (buscarIndicePorCodigo(*operacoes, *totalOperacoes, nova.codigoOperacao) != -1)
    {
        printf("ERRO: Ja existe uma operacao com este codigo.\n");
        return;
    }

    printf("Placa do caminhao: ");
    fgets(nova.placaCaminhao, sizeof(nova.placaCaminhao), stdin);
    nova.placaCaminhao[strcspn(nova.placaCaminhao, "\n")] = 0;

    int caminhaoOk = 0;
    for (int i = 0; i < totalCaminhoes; i++)
    {
        if (strcmp(caminhoes[i].placa, nova.placaCaminhao) == 0)
        {
            caminhaoOk = 1;
            break;
        }
    }
    if (caminhaoOk == 0)
    {
        printf("ERRO: Caminhao '%s' nao cadastrado. Cadastre-o primeiro.\n", nova.placaCaminhao);
        return;
    }

    printf("Numero da doca: ");
    scanf("%d", &nova.numeroDoca);
    limparBuffer();

    int docaOk = 0;
    for (int i = 0; i < totalDocas; i++)
    {
        if (docas[i].numeroDoca == nova.numeroDoca)
        {
            docaOk = 1;
            break;
        }
    }
    if (docaOk == 0)
    {
        printf("ERRO: Doca %d nao cadastrada. Cadastre-a primeiro.\n", nova.numeroDoca);
        return;
    }

    //CARGA
    do
    {
        printf("Carga: ");
        fgets(nova.carga, sizeof(nova.carga), stdin);
        nova.carga[strcspn(nova.carga, "\n")] = 0;
        if (strlen(nova.carga) == 0)
            printf("ERRO: O campo nao pode ser vazio.\n");
    } while (strlen(nova.carga) == 0);

    //PESO
    do
    {
        printf("Peso da carga (toneladas): ");
        scanf("%f", &nova.pesoCarga);
        limparBuffer();
        if (nova.pesoCarga <= 0)
            printf("ERRO: O peso deve ser maior que zero.\n");
    } while (nova.pesoCarga <= 0);
    
    //TIPO
    int tipoValido = 0;
    do
    {
        printf("Tipo (CARGA [0] / DESCARGA [1]): ");
        scanf("%d", (int *)&nova.tipo);
        limparBuffer();
        if (nova.tipo == CARGA || nova.tipo == DESCARGA)
            tipoValido = 1;
        else
            printf("ERRO: Digite 0 para CARGA ou 1 para DESCARGA.\n");
    } while (tipoValido == 0);

    // Status inicial
    nova.status = PENDENTE;

    // Registra a Data e Hora de Chegada
    time_t t = time(NULL);
    nova.dataHoraChegada = *localtime(&t);

    // Zera os outros tempos
    memset(&nova.horaInicio, 0, sizeof(struct tm));
    memset(&nova.horaTermino, 0, sizeof(struct tm));

    (*operacoes)[*totalOperacoes] = nova;   // coloca na posição atual
    (*totalOperacoes)++;
    printf("Operacao cadastrada com sucesso!\n");
}

void consultarOperacoesFiltradas(Operacao *operacoes, int totalOperacoes,
                                  Caminhao *caminhoes, int totalCaminhoes,
                                  Doca *docas, int totalDocas)
{
    printf("\nFiltrar por:\n");
    printf("  1 - Placa do Caminhao\n");
    printf("  2 - Numero da Doca\n");
    printf("  3 - Status\n");
    printf("Opcao: ");

    int opcao;
    scanf("%d", &opcao);

    int encontrou = 0;

    for (int i = 0; i < totalOperacoes; i++)
    {
        Operacao *op = &operacoes[i];
        int exibir = 0;

        if (opcao == 1) {
            char placa[8];
            printf("Placa: "); scanf("%7s", placa);
            if (strcmp(op->placaCaminhao, placa) == 0) exibir = 1;
        }
        else if (opcao == 2) {
            int numDoca;
            printf("Numero da doca: "); scanf("%d", &numDoca);
            if (op->numeroDoca == numDoca) exibir = 1;
        }
        else if (opcao == 3) {
            printf("Status (PENDENTE[0] ATIVA[1] CONCLUIDA[2] CANCELADA[3]): ");
            int st; scanf("%d", &st);
            if (op->status == (StatusOperacao)st) exibir = 1;
        }

        if (exibir) {
            printf("\n  Codigo : %s | Placa: %s | Doca: %d | Status: %s\n",
                   op->codigoOperacao, op->placaCaminhao,
                   op->numeroDoca, traduzirStatusOperacao(op->status));
            encontrou = 1;
            // se quiser exibir dados do caminhao/doca associados, busca aqui
        }
    }

    if (!encontrou)
        printf("Nenhuma operacao encontrada com esse filtro.\n");
}

void listarOperacoes(Operacao *operacoes, int totalOperacoes,
                     Caminhao *caminhoes, int totalCaminhoes,
                     Doca *docas, int totalDocas)
{
    if (totalOperacoes == 0)
    {
        printf("\nNenhuma operacao cadastrada.\n");
        return;
    }

    printf("\n--- Lista de Operacoes ---\n");

    for (int i = 0; i < totalOperacoes; i++)
    {
        printf("\nCodigo: %s", operacoes[i].codigoOperacao);
        printf("\nPlaca Caminhao: %s", operacoes[i].placaCaminhao);
        printf("\nNumero Doca: %d", operacoes[i].numeroDoca);
        printf("\nCarga: %s", operacoes[i].carga);
        printf("\nPeso: %.2f toneladas", operacoes[i].pesoCarga);
        printf("\nStatus: %s\n", traduzirStatusOperacao(operacoes[i].status));
    }
}

void buscarOperacao(Operacao *operacoes, int totalOperacoes,
                    Caminhao *caminhoes, int totalCaminhoes,
                    Doca *docas, int totalDocas)
{
    char codigo[10];

    printf("\nDigite o codigo da operacao: ");
    scanf("%9s", codigo);
    limparBuffer();

    int indice = buscarIndicePorCodigo(operacoes, totalOperacoes, codigo);

    if (indice == -1)
    {
        printf("Operacao nao encontrada.\n");
        return;
    }

    Operacao *op = &operacoes[indice];

    printf("\n--- Operacao Encontrada ---\n");
    printf("Codigo: %s\n", op->codigoOperacao);
    printf("Placa: %s\n", op->placaCaminhao);
    printf("Doca: %d\n", op->numeroDoca);
    printf("Carga: %s\n", op->carga);
    printf("Peso: %.2f\n", op->pesoCarga);
    printf("Status: %s\n", traduzirStatusOperacao(op->status));

    char bufferTempo[50];
    strftime(bufferTempo, sizeof(bufferTempo), "%d/%m/%Y %H:%M:%S", &op->dataHoraChegada);
    printf("Chegada no patio: %s\n", bufferTempo);

    if (op->status == ATIVA || op->status == CONCLUIDA) {
        strftime(bufferTempo, sizeof(bufferTempo), "%d/%m/%Y %H:%M:%S", &op->horaInicio);
        printf("Inicio da operacao: %s\n", bufferTempo);
    }
    
    if (op->status == CONCLUIDA) {
        strftime(bufferTempo, sizeof(bufferTempo), "%d/%m/%Y %H:%M:%S", &op->horaTermino);
        printf("Termino da operacao: %s\n", bufferTempo);
    }
}

void editarOperacao(Operacao *operacoes, int totalOperacoes)
{
    char codigo[10];

    printf("\nCodigo da operacao para editar: ");
    scanf("%9s", codigo);
    limparBuffer();

    int indice = buscarIndicePorCodigo(operacoes, totalOperacoes, codigo);

    if (indice == -1)
    {
        printf("Operacao nao encontrada.\n");
        return;
    }

    Operacao *op = &operacoes[indice];

    printf("Nova carga: ");
    fgets(op->carga, sizeof(op->carga), stdin);
    op->carga[strcspn(op->carga, "\n")] = 0;

    printf("Novo peso: ");
    scanf("%f", &op->pesoCarga);
    limparBuffer();

    printf("Alterar status da operacao?\n [0] PENDENTE\n [1] ATIVA (grava inicio)\n [2] CONCLUIDA (grava termino)\n [3] CANCELADA\n [4] Manter o atual\nOpcao: ");
    int novoStatus;
    scanf("%d", &novoStatus);
    limparBuffer();

    if (novoStatus >= 0 && novoStatus <= 3) {
        op->status = (StatusOperacao)novoStatus;
        time_t t = time(NULL);

        if (op->status == ATIVA) {
            op->horaInicio = *localtime(&t);
        } else if (op->status == CONCLUIDA) {
            op->horaTermino = *localtime(&t);
            // se foi concluida direto sem ATUAL, por seguranca gravamos ambos
            if (op->horaInicio.tm_year == 0) { 
                op->horaInicio = *localtime(&t);
            }
        }
    }

    printf("Operacao atualizada com sucesso!\n");
}

void deletarOperacao(Operacao *operacoes, int *totalOperacoes)
{
    char codigo[10];

    printf("\nCodigo da operacao para deletar: ");
    scanf("%9s", codigo);
    limparBuffer();

    int indice = buscarIndicePorCodigo(operacoes, *totalOperacoes, codigo);

    if (indice == -1)
    {
        printf("Operacao nao encontrada.\n");
        return;
    }

    for (int i = indice; i < *totalOperacoes - 1; i++)
    {
        operacoes[i] = operacoes[i + 1];
    }

    (*totalOperacoes)--;

    printf("Operacao removida com sucesso.\n");
}

void gerarRelatorio(Operacao *operacoes, int totalOperacoes,
                    Caminhao *caminhoes, int totalCaminhoes,
                    Doca *docas, int totalDocas)
{
    FILE *f = fopen("relatorio.txt", "w");
    if (f == NULL)
    {
        printf("ERRO: Nao foi possivel criar relatorio.txt\n");
        return;
    }

    fprintf(f, "=================================================\n");
    fprintf(f, "        RELATORIO GERAL DE OPERACOES             \n");
    fprintf(f, "=================================================\n\n");

    if (totalOperacoes == 0)
    {
        fprintf(f, "Nenhuma operacao cadastrada no sistema.\n");
    }
    else
    {
        for (int i = 0; i < totalOperacoes; i++)
        {
            Operacao *op = &operacoes[i];
            fprintf(f, "Codigo Operacao: %s\n", op->codigoOperacao);
            fprintf(f, "Status: %s\n", traduzirStatusOperacao(op->status));
            fprintf(f, "Tipo: %s\n", op->tipo == CARGA ? "CARGA" : "DESCARGA");
            fprintf(f, "Produto: %s (%.2f Toneladas)\n", op->carga, op->pesoCarga);
            fprintf(f, "Caminhao (Placa): %s\n", op->placaCaminhao);
            fprintf(f, "Doca (Numero): %d\n", op->numeroDoca);
            fprintf(f, "-------------------------------------------------\n");
        }
    }

    fclose(f);
    printf("Relatorio 'relatorio.txt' gerado com sucesso!\n");
}