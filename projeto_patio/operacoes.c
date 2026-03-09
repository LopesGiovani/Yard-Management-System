#include "operacoes.h"
#include "dados.h"
#include "structs.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

// Compara duas strings ignorando maiusculas/minusculas
// Retorna 0 se forem iguais, 1 se forem diferentes
int compararIgnoreCase(const char *str1, const char *str2)
{
    int i;

    if (strlen(str1) != strlen(str2))
        return 1;

    for (i = 0; str1[i] != '\0'; i++)
    {
        if (tolower(str1[i]) != tolower(str2[i]))
            return 1;
    }

    return 0;
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
    limparBuffer();
    fgets(nova.codigoOperacao, sizeof(nova.codigoOperacao), stdin);
    nova.codigoOperacao[strcspn(nova.codigoOperacao, "\n")] = 0;

    if (buscarIndicePorCodigo(*operacoes, *totalOperacoes, nova.codigoOperacao) != -1)
    {
        printf("ERRO: Ja existe uma operacao com este codigo.\n");
        return;
    }

    printf("Placa do caminhao: ");
    fgets(nova.placaCaminhao, sizeof(nova.placaCaminhao), stdin);
    if (strchr(nova.placaCaminhao, '\n') == NULL)
        limparBuffer();
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

    //PRODUTO
    do
    {
        printf("Produto: ");
        fgets(nova.produto, sizeof(nova.produto), stdin);
        nova.produto[strcspn(nova.produto, "\n")] = 0;
        if (strlen(nova.produto) == 0)
            printf("ERRO: O campo nao pode ser vazio.\n");
    } while (strlen(nova.produto) == 0);

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

void consultarAtivasPorTipo(Operacao *operacoes, int totalOperacoes, 
                            Caminhao *caminhoes, int totalCaminhoes, 
                            Doca *docas, int totalDocas)
{
    printf("\n=== Consultar Operacoes Ativas por Tipo ===\n");
    printf("Digite o tipo [0=CARGA, 1=DESCARGA]: ");
    int tipoFiltrado;
    scanf("%d", &tipoFiltrado);
    limparBuffer();

    int encontrou = 0;
    for (int i = 0; i < totalOperacoes; i++) {
        Operacao *op = &operacoes[i];
        
        // Filtra por tipo, e que nao tenha horaTermino registrada (ou seja, ano = 0 e esta ativa ou pendente)
        if (op->tipo == (TipoDoca)tipoFiltrado && op->status != CONCLUIDA && op->status != CANCELADA) {
            
            // Busca dados extras nas outras structs (embora o trabalho peca 1 relacao por vez, mostramos os que pudermos)
            char nomeMotorista[50] = "Nao Encontrado";
            for(int j=0; j<totalCaminhoes; j++) {
                if(strcmp(caminhoes[j].placa, op->placaCaminhao) == 0) {
                    strcpy(nomeMotorista, caminhoes[j].motoristaNome);
                    break;
                }
            }

            char strChegada[30];
            strftime(strChegada, sizeof(strChegada), "%d/%m %H:%M", &op->dataHoraChegada);

            char strInicio[30] = "Nao Iniciou";
            if (op->status == ATIVA) {
                strftime(strInicio, sizeof(strInicio), "%H:%M", &op->horaInicio);
            }

            printf("\n%s | %s | %s | %s | %.2ft | Placa: %s | Mot: %s | Doca: %d\n",
                op->codigoOperacao, strChegada, strInicio, op->produto, op->pesoCarga, 
                op->placaCaminhao, nomeMotorista, op->numeroDoca);
            
            encontrou = 1;
        }
    }
    
    if (!encontrou) printf("Nenhuma operacao ativa encontrada para este tipo.\n");
}

void consultarHistoricoPorPlaca(Operacao *operacoes, int totalOperacoes, 
                                Caminhao *caminhoes, int totalCaminhoes, 
                                Doca *docas, int totalDocas)
{
    printf("\n=== Consultar Historico de Operacoes por Placa ===\n");
    printf("Digite a Placa: ");
    char placaBusca[8];
    scanf("%7s", placaBusca);
    limparBuffer();

    // Busca o motorista
    char nomeMotorista[50] = "Desconhecido";
    for(int j=0; j<totalCaminhoes; j++) {
        if(strcmp(caminhoes[j].placa, placaBusca) == 0) {
            strcpy(nomeMotorista, caminhoes[j].motoristaNome);
            break;
        }
    }

    printf("Historico para Placa %s, Motorista: %s\n", placaBusca, nomeMotorista);

    int encontrou = 0;
    for (int i = 0; i < totalOperacoes; i++) {
        Operacao *op = &operacoes[i];

        if (strcmp(op->placaCaminhao, placaBusca) == 0) {
            char strChegada[30], strInicio[30], strTermino[30];
            strftime(strChegada, sizeof(strChegada), "%d/%m %H:%M", &op->dataHoraChegada);
            
            if(op->status == ATIVA || op->status == CONCLUIDA) 
                strftime(strInicio, sizeof(strInicio), "%H:%M", &op->horaInicio);
            else strcpy(strInicio, "---");

            if(op->status == CONCLUIDA) 
                strftime(strTermino, sizeof(strTermino), "%H:%M", &op->horaTermino);
            else strcpy(strTermino, "---");


            printf("%s | Chegou: %s | Inicio: %s | Fim: %s | %s | %s | %.2ft | Doca: %d\n",
                op->codigoOperacao, strChegada, strInicio, strTermino,
                op->tipo == CARGA ? "Carga":"Descarga", 
                op->produto, op->pesoCarga, op->numeroDoca);
            
            encontrou = 1;
        }
    }
    
    if (!encontrou) printf("Nenhuma operacao encontrada para a placa %s.\n", placaBusca);
}

void consultarOperacoesPorDoca(Operacao *operacoes, int totalOperacoes, 
                               Caminhao *caminhoes, int totalCaminhoes, 
                               Doca *docas, int totalDocas)
{
    printf("\n=== Consultar Operacoes por Doca Especifica ===\n");
    printf("Digite o Numero da Doca: ");
    int numDocaBusca;
    scanf("%d", &numDocaBusca);
    limparBuffer();

    printf("Operacoes da Doca %d:\n", numDocaBusca);

    int encontrou = 0;
    for (int i = 0; i < totalOperacoes; i++) {
        Operacao *op = &operacoes[i];

        if (op->numeroDoca == numDocaBusca) {
            char strChegada[30];
            strftime(strChegada, sizeof(strChegada), "%d/%m %H:%M", &op->dataHoraChegada);

            char transp[50] = "Desconhecida";
            for(int j=0; j<totalCaminhoes; j++) {
                if(strcmp(caminhoes[j].placa, op->placaCaminhao) == 0) {
                    strcpy(transp, caminhoes[j].transportadora);
                    break;
                }
            }

            printf("%s | %s | %s | %s | %.2ft | Placa: %s | Transp: %s\n",
                op->codigoOperacao, traduzirStatusOperacao(op->status),
                strChegada, op->produto, op->pesoCarga,
                op->placaCaminhao, transp);
            
            encontrou = 1;
        }
    }
    
    if (!encontrou) printf("Nenhuma operacao encontrada para a doca %d.\n", numDocaBusca);
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
        printf("\nProduto: %s", operacoes[i].produto);
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
    printf("Produto: %s\n", op->produto);
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

    char novoProduto[50];
    do {
        printf("Novo produto (atual: %s): ", op->produto);
        fgets(novoProduto, sizeof(novoProduto), stdin);
        novoProduto[strcspn(novoProduto, "\n")] = 0;
        if (strlen(novoProduto) == 0)
            printf("ERRO: O produto nao pode ser vazio.\n");
    } while (strlen(novoProduto) == 0);
    strcpy(op->produto, novoProduto);

    float novoPeso;
    do {
        printf("Novo peso em toneladas (atual: %.2f): ", op->pesoCarga);
        scanf("%f", &novoPeso);
        limparBuffer();
        if (novoPeso <= 0)
            printf("ERRO: O peso deve ser maior que zero.\n");
    } while (novoPeso <= 0);
    op->pesoCarga = novoPeso;

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

void deletarOperacao(Operacao **operacoes, int *totalOperacoes, int *capOperacoes)
{
    char codigo[10];

    printf("\nCodigo da operacao para deletar: ");
    scanf("%9s", codigo);
    limparBuffer();

    int indice = buscarIndicePorCodigo(*operacoes, *totalOperacoes, codigo);

    if (indice == -1)
    {
        printf("Operacao nao encontrada.\n");
        return;
    }

    for (int i = indice; i < *totalOperacoes - 1; i++)
    {
        (*operacoes)[i] = (*operacoes)[i + 1];
    }

    (*totalOperacoes)--;

    int livres = *capOperacoes - *totalOperacoes;
    if (livres > EXTRA)
    {
        int novaCap = *totalOperacoes + EXTRA;
        Operacao *temp = realloc(*operacoes, novaCap * sizeof(Operacao));
        if (temp != NULL)
        {
            *operacoes = temp;
            *capOperacoes = novaCap;
        }
    }

    printf("Operacao removida com sucesso.\n");
}

void gerarRelatorioTransportadora(Operacao *operacoes, int totalOperacoes,
                                  Caminhao *caminhoes, int totalCaminhoes,
                                  Doca *docas, int totalDocas)
{
    printf("\n=== Relatorio por Transportadora (Salvo em TXT) ===\n");
    printf("Digite o nome da Transportadora: ");
    limparBuffer();
    char transpBusca[50];
    fgets(transpBusca, sizeof(transpBusca), stdin);
    transpBusca[strcspn(transpBusca, "\n")] = 0;

    char strDataIni[15], strDataFim[15];
    printf("Data Inicial (DD/MM/AAAA): ");
    scanf("%14s", strDataIni);
    limparBuffer();
    struct tm tm_ini = {0};
    sscanf(strDataIni, "%d/%d/%d", &tm_ini.tm_mday, &tm_ini.tm_mon, &tm_ini.tm_year);
    tm_ini.tm_mon -= 1;
    tm_ini.tm_year -= 1900;
    time_t time_ini = mktime(&tm_ini);

    printf("Data Final (DD/MM/AAAA): ");
    scanf("%14s", strDataFim);
    limparBuffer();
    struct tm tm_fim = {0};
    sscanf(strDataFim, "%d/%d/%d", &tm_fim.tm_mday, &tm_fim.tm_mon, &tm_fim.tm_year);
    tm_fim.tm_mon -= 1;
    tm_fim.tm_year -= 1900;
    tm_fim.tm_hour = 23; tm_fim.tm_min = 59; tm_fim.tm_sec = 59;
    time_t time_fim = mktime(&tm_fim);

    FILE *f = fopen("Relatorio_Transportadora.txt", "w");
    if (f == NULL) {
        printf("ERRO: Nao foi possivel criar o arquivo.\n");
        return;
    }

    fprintf(f, "==================================================================\n");
    fprintf(f, "RELATÓRIO DE MOVIMENTAÇÃO - SISTEMA DE GESTÃO DE PÁTIO E DOCAS\n");
    fprintf(f, "==================================================================\n");
    fprintf(f, "Transportadora: %s\n", transpBusca);
    fprintf(f, "Período: %s a %s\n\n", strDataIni, strDataFim);

    int count = 0;
    for (int i = 0; i < totalOperacoes; i++) {
        Operacao *op = &operacoes[i];

        // Busca o caminhao pra ver se pertence a Transportadora
        int pertence = 0;
        char placa[8] = "";
        char motorista[50] = "";
        char veiculo[50] = "";

        for(int j=0; j<totalCaminhoes; j++) {
            if(strcmp(caminhoes[j].placa, op->placaCaminhao) == 0) {
                if(compararIgnoreCase(caminhoes[j].transportadora, transpBusca) == 0) {
                    pertence = 1;
                    strcpy(placa, caminhoes[j].placa);
                    strcpy(motorista, caminhoes[j].motoristaNome);
                    strcpy(veiculo, caminhoes[j].tipoVeiculo);
                }
                break;
            }
        }

        if (pertence) {
            time_t time_op = mktime(&op->dataHoraChegada);
            if (difftime(time_op, time_ini) >= 0 && difftime(time_fim, time_op) >= 0) {
                char strChegada[30];
                strftime(strChegada, sizeof(strChegada), "%d/%m/%Y %H:%M", &op->dataHoraChegada);

                // Pega dados da Doca
                char tipoDocaStr[20] = "Mista";
                float capDoca = 0.0;
                for(int k=0; k<totalDocas; k++) {
                    if(docas[k].numeroDoca == op->numeroDoca) {
                        strcpy(tipoDocaStr, docas[k].tipo == CARGA ? "Carga" : "Descarga");
                        capDoca = docas[k].capacidadeMaxima;
                        break;
                    }
                }

                fprintf(f, "[OPERAÇÃO: %s]\n", op->codigoOperacao);
                fprintf(f, " Data Chegada: %s\n", strChegada);
                fprintf(f, " Tipo: %s\n", op->tipo == CARGA ? "Carga" : "Descarga");
                fprintf(f, " Produto: %s\n", op->produto);
                fprintf(f, " Peso: %.2f toneladas\n", op->pesoCarga);
                fprintf(f, " Doca: Doca %d (Tipo: %s, Cap: %.2ft)\n", op->numeroDoca, tipoDocaStr, capDoca);
                fprintf(f, " Caminhão:\n");
                fprintf(f, "  Placa: %s\n", placa);
                fprintf(f, "  Motorista: %s\n", motorista);
                fprintf(f, "  Veículo: %s\n", veiculo);
                fprintf(f, "\n");
                count++;
            }
        }
    }

    if (count == 0) fprintf(f, "Nenhuma operacao encontrada para a transportadora %s no periodo.\n", transpBusca);

    fclose(f);
    printf("Relatorio 'Relatorio_Transportadora.txt' gerado com sucesso! (%d registros)\n", count);
}

void gerarRelatorioProduto(Operacao *operacoes, int totalOperacoes,
                           Caminhao *caminhoes, int totalCaminhoes,
                           Doca *docas, int totalDocas)
{
    printf("\n=== Relatorio por Produto (Salvo em TXT) ===\n");
    printf("Digite o nome do Produto: ");
    limparBuffer();
    char prodBusca[50];
    fgets(prodBusca, sizeof(prodBusca), stdin);
    prodBusca[strcspn(prodBusca, "\n")] = 0;

    char strDataIni[15], strDataFim[15];
    printf("Data Inicial (DD/MM/AAAA): ");
    scanf("%14s", strDataIni);
    limparBuffer();
    struct tm tm_ini = {0};
    sscanf(strDataIni, "%d/%d/%d", &tm_ini.tm_mday, &tm_ini.tm_mon, &tm_ini.tm_year);
    tm_ini.tm_mon -= 1;
    tm_ini.tm_year -= 1900;
    time_t time_ini = mktime(&tm_ini);

    printf("Data Final (DD/MM/AAAA): ");
    scanf("%14s", strDataFim);
    limparBuffer();
    struct tm tm_fim = {0};
    sscanf(strDataFim, "%d/%d/%d", &tm_fim.tm_mday, &tm_fim.tm_mon, &tm_fim.tm_year);
    tm_fim.tm_mon -= 1;
    tm_fim.tm_year -= 1900;
    tm_fim.tm_hour = 23; tm_fim.tm_min = 59; tm_fim.tm_sec = 59;
    time_t time_fim = mktime(&tm_fim);

    FILE *f = fopen("Relatorio_Produto.txt", "w");
    if (f == NULL) {
        printf("ERRO: Nao foi possivel criar o arquivo.\n");
        return;
    }

    fprintf(f, "==================================================================\n");
    fprintf(f, "RELATÓRIO DE MOVIMENTAÇÃO POR PRODUTO\n");
    fprintf(f, "==================================================================\n");
    fprintf(f, "Produto: %s\n", prodBusca);
    fprintf(f, "Período: %s a %s\n\n", strDataIni, strDataFim);

    int count = 0;
    for (int i = 0; i < totalOperacoes; i++) {
        Operacao *op = &operacoes[i];

        if (compararIgnoreCase(op->produto, prodBusca) == 0) {
            time_t time_op = mktime(&op->dataHoraChegada);
            if (difftime(time_op, time_ini) >= 0 && difftime(time_fim, time_op) >= 0) {
                char strChegada[30];
                strftime(strChegada, sizeof(strChegada), "%d/%m/%Y %H:%M", &op->dataHoraChegada);

                char placa[8] = "";
                char transp[50] = "";
                for(int j=0; j<totalCaminhoes; j++) {
                    if(strcmp(caminhoes[j].placa, op->placaCaminhao) == 0) {
                        strcpy(placa, caminhoes[j].placa);
                        strcpy(transp, caminhoes[j].transportadora);
                        break;
                    }
                }

                fprintf(f, "[OPERAÇÃO: %s | TIPO: %s]\n", op->codigoOperacao, op->tipo == CARGA ? "Carga" : "Descarga");
                fprintf(f, " Data Chegada: %s\n", strChegada);
                fprintf(f, " Peso: %.2f toneladas\n", op->pesoCarga);
                fprintf(f, " Doca: Doca %d\n", op->numeroDoca);
                fprintf(f, " Caminhão:\n");
                fprintf(f, "  Placa: %s\n", placa);
                fprintf(f, "  Transportadora: %s\n", transp);
                fprintf(f, "\n");
                count++;
            }
        }
    }

    if (count == 0) fprintf(f, "Nenhuma operacao encontrada para o produto %s.\n", prodBusca);

    fclose(f);
    printf("Relatorio 'Relatorio_Produto.txt' gerado com sucesso! (%d registros)\n", count);
}

void gerarRelatorioSumarioDocas(Operacao *operacoes, int totalOperacoes,
                                Caminhao *caminhoes, int totalCaminhoes,
                                Doca *docas, int totalDocas)
{
    printf("\n=== Sumario de Ocupacao de Docas (Salvo em TXT) ===\n");
    printf("Sumarizando dados gerais de operacao...\n");

    char strDataIni[15], strDataFim[15];
    printf("Data Inicial (DD/MM/AAAA): ");
    scanf("%14s", strDataIni);
    limparBuffer();
    struct tm tm_ini = {0};
    sscanf(strDataIni, "%d/%d/%d", &tm_ini.tm_mday, &tm_ini.tm_mon, &tm_ini.tm_year);
    tm_ini.tm_mon -= 1;
    tm_ini.tm_year -= 1900;
    time_t time_ini = mktime(&tm_ini);

    printf("Data Final (DD/MM/AAAA): ");
    scanf("%14s", strDataFim);
    limparBuffer();
    struct tm tm_fim = {0};
    sscanf(strDataFim, "%d/%d/%d", &tm_fim.tm_mday, &tm_fim.tm_mon, &tm_fim.tm_year);
    tm_fim.tm_mon -= 1;
    tm_fim.tm_year -= 1900;
    tm_fim.tm_hour = 23; tm_fim.tm_min = 59; tm_fim.tm_sec = 59;
    time_t time_fim = mktime(&tm_fim);

    FILE *f = fopen("Relatorio_Docas.txt", "w");
    if (f == NULL) {
        printf("ERRO: Nao foi possivel criar o arquivo.\n");
        return;
    }

    fprintf(f, "==================================================================\n");
    fprintf(f, "RELATÓRIO DE OCUPAÇÃO DE DOCAS\n");
    fprintf(f, "==================================================================\n");
    fprintf(f, "Período: %s a %s\n\n", strDataIni, strDataFim);

    for (int d = 0; d < totalDocas; d++) {
        Doca *doca = &docas[d];
        int numOps = 0;
        float totalPeso = 0.0;

        for (int i = 0; i < totalOperacoes; i++) {
            if (operacoes[i].numeroDoca == doca->numeroDoca) {
                time_t time_op = mktime(&operacoes[i].dataHoraChegada);
                if (difftime(time_op, time_ini) >= 0 && difftime(time_fim, time_op) >= 0) {
                    numOps++;
                    totalPeso += operacoes[i].pesoCarga;
                }
            }
        }

        fprintf(f, "[DOCA: %d]\n", doca->numeroDoca);
        fprintf(f, " Tipo: %s\n", doca->tipo == CARGA ? "Carga" : "Descarga");
        fprintf(f, " Operações totais registradas: %d\n", numOps);
        fprintf(f, " Peso total movimentado: %.1f Toneladas\n\n", totalPeso);
    }

    fclose(f);
    printf("Relatorio 'Relatorio_Docas.txt' gerado com sucesso! (Analise de %d docas)\n", totalDocas);
}