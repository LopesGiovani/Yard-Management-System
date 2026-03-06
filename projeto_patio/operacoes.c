#include "operacoes.h"
#include "dados.h"
#include "structs.h"
#include <stdio.h>

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
        Operacao *temp = realoc(*operacoes, novaCap * sizeof(Operacao));

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

    (*operacoes)[*totalOperacoes] = nova;   // coloca na posição atual
    (*totalOperacoes)++;
    printf("Operacao cadastrada com sucesso!\n");

}

