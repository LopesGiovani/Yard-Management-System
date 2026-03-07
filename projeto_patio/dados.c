#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "dados.h"

Caminhao *caminhoes;
Doca *docas;
Operacao *operacoes;

// Total de registros cadastrados
int totalCaminhoes = 0;
int totalDocas = 0;
int totalOperacoes = 0;

// Capacidade atual alocada (total + slots livres)
int capCaminhoes = 0;
int capDocas = 0;
int capOperacoes = 0;

void inicializarDados()
{
    caminhoes = calloc(EXTRA, sizeof(Caminhao));
    docas = calloc(EXTRA, sizeof(Doca));
    operacoes = calloc(EXTRA, sizeof(Operacao));

    if (caminhoes == NULL || docas == NULL || operacoes == NULL)
    {
        printf("ERRO: Falha ao alocar memoria inicial!\n");
        exit(1);
    }

    capCaminhoes = EXTRA;
    capDocas = EXTRA;
    capOperacoes = EXTRA;

    // Dados iniciais (carregados apenas se nao houver .bin salvo)
    caminhoes[0] = (Caminhao){"ABC1234", "TransporteA",  "Caminhao Bau",         "Joao Silva",   10.0};
    caminhoes[1] = (Caminhao){"DEF5678", "TransporteB",  "Caminhao Tanque",      "Maria Santos", 15.0};
    caminhoes[2] = (Caminhao){"GHI9012", "TransporteC",  "Caminhao Frigorifico", "Carlos Lima",  20.0};
    caminhoes[3] = (Caminhao){"JKL3456", "TransporteD",  "Caminhao Carga Seca",  "Ana Souza",    12.0};
    totalCaminhoes = 4;

    docas[0] = (Doca){1, CARGA,    LIVRE,   20.0};
    docas[1] = (Doca){2, DESCARGA, LIVRE,   25.0};
    docas[2] = (Doca){3, CARGA,    OCUPADA, 18.0};
    docas[3] = (Doca){4, DESCARGA, LIVRE,   30.0};
    totalDocas = 4;

    // Operacoes (campos de tempo zerados com calloc)
    operacoes[0].numeroDoca = 1; operacoes[0].tipo = CARGA;
    operacoes[0].pesoCarga = 5.0; operacoes[0].status = CONCLUIDA;
    strcpy(operacoes[0].codigoOperacao, "OP001");
    strcpy(operacoes[0].placaCaminhao,  "ABC1234");
    strcpy(operacoes[0].carga,          "Eletronicos");

    operacoes[1].numeroDoca = 2; operacoes[1].tipo = DESCARGA;
    operacoes[1].pesoCarga = 8.0; operacoes[1].status = CONCLUIDA;
    strcpy(operacoes[1].codigoOperacao, "OP002");
    strcpy(operacoes[1].placaCaminhao,  "DEF5678");
    strcpy(operacoes[1].carga,          "Alimentos");

    operacoes[2].numeroDoca = 3; operacoes[2].tipo = CARGA;
    operacoes[2].pesoCarga = 12.0; operacoes[2].status = ATIVA;
    strcpy(operacoes[2].codigoOperacao, "OP003");
    strcpy(operacoes[2].placaCaminhao,  "GHI9012");
    strcpy(operacoes[2].carga,          "Quimicos");

    operacoes[3].numeroDoca = 4; operacoes[3].tipo = DESCARGA;
    operacoes[3].pesoCarga = 7.5; operacoes[3].status = PENDENTE;
    strcpy(operacoes[3].codigoOperacao, "OP004");
    strcpy(operacoes[3].placaCaminhao,  "JKL3456");
    strcpy(operacoes[3].carga,          "Autopecas");

    totalOperacoes = 4;
}
void salvarDados()
{
    FILE *fp;
    fp = fopen("caminhoes.bin", "wb");
    if (fp != NULL)
    {
        fwrite(&totalCaminhoes, sizeof(totalCaminhoes), 1, fp);
        fwrite(caminhoes, sizeof(Caminhao), totalCaminhoes, fp);
        fclose(fp);
    }
    else
        printf("ERRO: Nao foi possivel salvar caminhoes.bin\n");

    fp = fopen("docas.bin", "wb");
    if (fp != NULL)
    {
        fwrite(&totalDocas, sizeof(totalDocas), 1, fp);
        fwrite(docas, sizeof(Doca), totalDocas, fp);
        fclose(fp);
    }
    else
        printf("ERRO: Nao foi possivel salvar docas.bin\n");

    fp = fopen("operacoes.bin", "wb");
    if (fp != NULL)
    {
        fwrite(&totalOperacoes, sizeof(totalOperacoes), 1, fp);
        fwrite(operacoes, sizeof(Operacao), totalOperacoes, fp);
        fclose(fp);
    }
    else
        printf("ERRO: Nao foi possivel salvar operacoes.bin\n");

    printf("Dados salvos com sucesso.\n");
}

static void carregarCaminhoes()
{
    int total;
    FILE *fp = fopen("caminhoes.bin", "rb");

    if (fp == NULL)
        return;

    fread(&total, sizeof(total), 1, fp);
    if (total > capCaminhoes)
    {
        Caminhao *temp = realloc(caminhoes, (total + EXTRA) * sizeof(Caminhao));
        if (temp == NULL)
        {
            printf("ERRO: Falha ao carregar caminhoes.bin\n");
            fclose(fp);
            return;
        }
        caminhoes = temp;
        capCaminhoes = total + EXTRA;
    }
    fread(caminhoes, sizeof(Caminhao), total, fp);
    totalCaminhoes = total;
    fclose(fp);
}

static void carregarDocas()
{
    int total;
    FILE *fp = fopen("docas.bin", "rb");

    if (fp == NULL)
        return;

    fread(&total, sizeof(total), 1, fp);
    if (total > capDocas)
    {
        Doca *temp = realloc(docas, (total + EXTRA) * sizeof(Doca));
        if (temp == NULL)
        {
            printf("ERRO: Falha ao carregar docas.bin\n");
            fclose(fp);
            return;
        }
        docas = temp;
        capDocas = total + EXTRA;
    }
    fread(docas, sizeof(Doca), total, fp);
    totalDocas = total;
    fclose(fp);
}

static void carregarOperacoes()
{
    int total;
    FILE *fp = fopen("operacoes.bin", "rb");

    if (fp == NULL)
        return;

    fread(&total, sizeof(total), 1, fp);
    if (total > capOperacoes)
    {
        Operacao *temp = realloc(operacoes, (total + EXTRA) * sizeof(Operacao));
        if (temp == NULL)
        {
            printf("ERRO: Falha ao carregar operacoes.bin\n");
            fclose(fp);
            return;
        }
        operacoes = temp;
        capOperacoes = total + EXTRA;
    }
    fread(operacoes, sizeof(Operacao), total, fp);
    totalOperacoes = total;
    fclose(fp);
}

void carregarDados()
{
    carregarCaminhoes();
    carregarDocas();
    carregarOperacoes();
}