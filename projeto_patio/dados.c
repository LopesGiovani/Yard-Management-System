#include <stdlib.h>
#include <stdio.h>
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

    // chamar carregarDados() para ler os .bin
    // Por enquanto manter os dados mockados:
    caminhoes[0] = (Caminhao){"ABC1234", "TransporteA", "CaminhaoA", "Joao Silva", 10};
    caminhoes[1] = (Caminhao){"DEF5678", "TransporteB", "CaminhaoB", "Maria Silva", 15};
    totalCaminhoes = 2;
    docas[0] = (Doca){1, CARGA, LIVRE, 20.0};
    docas[1] = (Doca){2, DESCARGA, LIVRE, 25.0};
    totalDocas = 2;
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