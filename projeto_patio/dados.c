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
    caminhoes = calloc(10 + EXTRA, sizeof(Caminhao));
    docas = calloc(10 + EXTRA, sizeof(Doca));
    operacoes = calloc(10 + EXTRA, sizeof(Operacao));

    if (caminhoes == NULL || docas == NULL || operacoes == NULL)
    {
        printf("ERRO: Falha ao alocar memoria inicial!\n");
        exit(1);
    }

    capCaminhoes = 10 + EXTRA;
    capDocas = 10 + EXTRA;
    capOperacoes = 10 + EXTRA;

    // Dados iniciais (carregados apenas se nao houver .bin salvo)
    caminhoes[0] = (Caminhao){"ABC1234", "TransporteA",  "Caminhao Bau",         "Joao Silva",   10.0};
    caminhoes[1] = (Caminhao){"DEF5678", "TransporteB",  "Caminhao Tanque",      "Maria Santos", 15.0};
    caminhoes[2] = (Caminhao){"GHI9012", "TransporteC",  "Caminhao Frigorifico", "Carlos Lima",  20.0};
    caminhoes[3] = (Caminhao){"JKL3456", "TransporteD",  "Caminhao Carga Seca",  "Ana Souza",    12.0};
    caminhoes[4] = (Caminhao){"MNO7890", "TransporteE",  "Carreta",              "Paulo Mendes", 30.0};
    caminhoes[5] = (Caminhao){"PQR1234", "TransporteA",  "Caminhao Bau",         "Jose Alves",   10.0};
    caminhoes[6] = (Caminhao){"STU5678", "TransporteF",  "Caminhao Aberto",      "Marcos Rocha", 14.0};
    caminhoes[7] = (Caminhao){"VWX9012", "TransporteG",  "Carreta",              "Lucas Gomes",  28.0};
    caminhoes[8] = (Caminhao){"YZA3456", "TransporteA",  "Caminhao Frigorifico", "Mateus Cruz",  18.0};
    caminhoes[9] = (Caminhao){"BCD7890", "TransporteH",  "Caminhao Tanque",      "Thiago Rosa",  16.0};
    totalCaminhoes = 10;

    docas[0] = (Doca){1,  CARGA,    LIVRE,   20.0};
    docas[1] = (Doca){2,  DESCARGA, LIVRE,   25.0};
    docas[2] = (Doca){3,  CARGA,    OCUPADA, 18.0};
    docas[3] = (Doca){4,  DESCARGA, LIVRE,   30.0};
    docas[4] = (Doca){5,  CARGA,    LIVRE,   22.0};
    docas[5] = (Doca){6,  DESCARGA, OCUPADA, 28.0};
    docas[6] = (Doca){7,  CARGA,    LIVRE,   20.0};
    docas[7] = (Doca){8,  DESCARGA, LIVRE,   35.0};
    docas[8] = (Doca){9,  CARGA,    LIVRE,   15.0};
    docas[9] = (Doca){10, DESCARGA, OCUPADA, 25.0};
    totalDocas = 10;

    // Operacoes (campos de tempo zerados com calloc, recebendo o tempo atual no mock)
    time_t t = time(NULL);

    operacoes[0].numeroDoca = 1; operacoes[0].tipo = CARGA;
    operacoes[0].pesoCarga = 5.0; operacoes[0].status = CONCLUIDA;
    strcpy(operacoes[0].codigoOperacao, "OP001");
    strcpy(operacoes[0].placaCaminhao,  "ABC1234");
    strcpy(operacoes[0].produto,        "Eletronicos");
    operacoes[0].dataHoraChegada = *localtime(&t);

    operacoes[1].numeroDoca = 2; operacoes[1].tipo = DESCARGA;
    operacoes[1].pesoCarga = 8.0; operacoes[1].status = CONCLUIDA;
    strcpy(operacoes[1].codigoOperacao, "OP002");
    strcpy(operacoes[1].placaCaminhao,  "DEF5678");
    strcpy(operacoes[1].produto,        "Alimentos");
    operacoes[1].dataHoraChegada = *localtime(&t);

    operacoes[2].numeroDoca = 3; operacoes[2].tipo = CARGA;
    operacoes[2].pesoCarga = 12.0; operacoes[2].status = ATIVA;
    strcpy(operacoes[2].codigoOperacao, "OP003");
    strcpy(operacoes[2].placaCaminhao,  "GHI9012");
    strcpy(operacoes[2].produto,        "Quimicos");
    operacoes[2].dataHoraChegada = *localtime(&t);

    operacoes[3].numeroDoca = 4; operacoes[3].tipo = DESCARGA;
    operacoes[3].pesoCarga = 7.5; operacoes[3].status = PENDENTE;
    strcpy(operacoes[3].codigoOperacao, "OP004");
    strcpy(operacoes[3].placaCaminhao,  "JKL3456");
    strcpy(operacoes[3].produto,        "Autopecas");
    operacoes[3].dataHoraChegada = *localtime(&t);

    operacoes[4].numeroDoca = 5; operacoes[4].tipo = CARGA;
    operacoes[4].pesoCarga = 20.0; operacoes[4].status = CONCLUIDA;
    strcpy(operacoes[4].codigoOperacao, "OP005");
    strcpy(operacoes[4].placaCaminhao,  "MNO7890");
    strcpy(operacoes[4].produto,        "Cimento");
    operacoes[4].dataHoraChegada = *localtime(&t);

    operacoes[5].numeroDoca = 6; operacoes[5].tipo = DESCARGA;
    operacoes[5].pesoCarga = 15.0; operacoes[5].status = ATIVA;
    strcpy(operacoes[5].codigoOperacao, "OP006");
    strcpy(operacoes[5].placaCaminhao,  "PQR1234");
    strcpy(operacoes[5].produto,        "Roupas");
    operacoes[5].dataHoraChegada = *localtime(&t);

    operacoes[6].numeroDoca = 7; operacoes[6].tipo = CARGA;
    operacoes[6].pesoCarga = 10.0; operacoes[6].status = PENDENTE;
    strcpy(operacoes[6].codigoOperacao, "OP007");
    strcpy(operacoes[6].placaCaminhao,  "STU5678");
    strcpy(operacoes[6].produto,        "Moveis");
    operacoes[6].dataHoraChegada = *localtime(&t);

    operacoes[7].numeroDoca = 8; operacoes[7].tipo = DESCARGA;
    operacoes[7].pesoCarga = 25.0; operacoes[7].status = CONCLUIDA;
    strcpy(operacoes[7].codigoOperacao, "OP008");
    strcpy(operacoes[7].placaCaminhao,  "VWX9012");
    strcpy(operacoes[7].produto,        "Soja");
    operacoes[7].dataHoraChegada = *localtime(&t);

    operacoes[8].numeroDoca = 9; operacoes[8].tipo = CARGA;
    operacoes[8].pesoCarga = 12.0; operacoes[8].status = ATIVA;
    strcpy(operacoes[8].codigoOperacao, "OP009");
    strcpy(operacoes[8].placaCaminhao,  "YZA3456");
    strcpy(operacoes[8].produto,        "Carnes");
    operacoes[8].dataHoraChegada = *localtime(&t);

    operacoes[9].numeroDoca = 10; operacoes[9].tipo = DESCARGA;
    operacoes[9].pesoCarga = 14.0; operacoes[9].status = PENDENTE;
    strcpy(operacoes[9].codigoOperacao, "OP010");
    strcpy(operacoes[9].placaCaminhao,  "BCD7890");
    strcpy(operacoes[9].produto,        "Combustivel");
    operacoes[9].dataHoraChegada = *localtime(&t);

    totalOperacoes = 10;
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