#include <stdio.h>
#include <stdlib.h>
#include "dados.h"
#include "docas.h"

static void limparBuffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void cadastrarDoca(Doca **docas, int *totalDocas, int *capDocas)
{
    if (*totalDocas >= *capDocas)
    {
        int novaCap = *capDocas + EXTRA;
        Doca *temp = realloc(*docas, novaCap * sizeof(Doca));
        if (temp == NULL)
        {
            printf("\nERRO: Falha ao realocar memoria para docas!\n");
            return;
        }
        *docas = temp;
        *capDocas = novaCap;
    }

    Doca novo;
    printf("\n--- Cadastrar Doca ---\n");
    printf("Digite o numero da doca: ");
    scanf("%d", &novo.numeroDoca);
    limparBuffer();

    if (buscarDocaPorNumero(*docas, *totalDocas, novo.numeroDoca) != NULL)
    {
        printf("ERRO: Ja existe uma doca cadastrada com este numero.\n");
        return;
    }

    do
    {
        printf("Digite o tipo da Doca (CARGA [0] ou DESCARGA [1]): ");
        scanf("%d", (int *)&novo.tipo);
        limparBuffer();
        if (novo.tipo != CARGA && novo.tipo != DESCARGA)
            printf("ERRO: O tipo deve ser CARGA [0] ou DESCARGA [1].\n");
    } while (novo.tipo != CARGA && novo.tipo != DESCARGA);

    do
    {
        printf("Digite o status da Doca (LIVRE [0] ou OCUPADA [1]): ");
        scanf("%d", (int *)&novo.status);
        limparBuffer();
        if (novo.status != LIVRE && novo.status != OCUPADA)
            printf("ERRO: O status deve ser LIVRE [0] ou OCUPADA [1].\n");
    } while (novo.status != LIVRE && novo.status != OCUPADA);

    do
    {
        printf("Digite a capacidade maxima da Doca (em toneladas): ");
        scanf("%f", &novo.capacidadeMaxima);
        limparBuffer();
        if (novo.capacidadeMaxima <= 0)
        {
            printf("ERRO: A capacidade maxima deve ser maior que zero.\n");
        }
    } while (novo.capacidadeMaxima <= 0);
    (*docas)[(*totalDocas)] = novo;
    (*totalDocas)++;
    printf("Doca cadastrada com sucesso!\n");
}

void listarDocas(Doca *docas, int totalDocas)
{
    printf("\n--- Lista de Docas ---\n");

    if (totalDocas == 0)
    {
        printf("Nenhuma doca cadastrada.\n");
        return;
    }

    for (int i = 0; i < totalDocas; i++)
    {
        printf("Doca %d\n", i + 1);
        printf("Numero: %d\n", (docas + i)->numeroDoca);
        printf("Tipo: %s\n", traduzirTipo((docas + i)->tipo));
        printf("Status: %s\n", traduzirStatus((docas + i)->status));
        printf("Capacidade Maxima: %.2f toneladas\n", (docas + i)->capacidadeMaxima);
        printf("--------------------------\n");
    }
}

void deletarDoca(Doca **docas, int *totalDocas, int *capDocas, Operacao *operacoes, int totalOperacoes)
{
    int numero;
    printf("\n--- Deletar Doca ---\n");
    printf("Digite o numero da doca a ser deletada: ");
    scanf("%d", &numero);
    limparBuffer();

    int indice = -1;
    for (int i = 0; i < *totalDocas; i++)
    {
        if ((*docas + i)->numeroDoca == numero)
        {
            indice = i;
            break;
        }
    }
    if (indice == -1)
    {
        printf("ERRO: Doca com numero %d nao encontrada.\n", numero);
        return;
    }

    for (int i = 0; i < totalOperacoes; i++)
    {
        if (operacoes[i].numeroDoca == numero)
        {
            printf("ERRO: Doca esta em uso na operacao '%s'. Remova a operacao primeiro.\n",
                   operacoes[i].codigoOperacao);
            return;
        }
    }

    for (int i = indice; i < *totalDocas - 1; i++)
        (*docas)[i] = (*docas)[i + 1];
    (*totalDocas)--;

    int livres = *capDocas - *totalDocas;
    if (livres > EXTRA)
    {
        int novaCap = *totalDocas + EXTRA;
        Doca *temp = realloc(*docas, novaCap * sizeof(Doca));
        if (temp != NULL)
        {
            *docas = temp;
            *capDocas = novaCap;
        }
    }

    printf("Doca deletada com sucesso!\n");
}

void editarDoca(Doca *docas, int totalDocas)
{

    int numero;
    printf("\n--- Editar Doca ---\n");
    printf("Digite o numero da doca a ser editada: ");
    scanf("%d", &numero);
    limparBuffer();

    Doca *doca = buscarDocaPorNumero(docas, totalDocas, numero);
    if (doca == NULL)
    {
        printf("ERRO: Doca com numero %d nao encontrada.\n", numero);
        return;
    }

    do
    {
        printf("Digite o novo tipo da Doca (CARGA [0] ou DESCARGA [1]): ");
        scanf("%d", (int *)&doca->tipo);
        limparBuffer();
        if (doca->tipo != CARGA && doca->tipo != DESCARGA)
            printf("ERRO: O tipo deve ser CARGA [0] ou DESCARGA [1].\n");
    } while (doca->tipo != CARGA && doca->tipo != DESCARGA);

    do
    {
        printf("Digite o novo status da Doca (LIVRE [0] ou OCUPADA [1]): ");
        scanf("%d", (int *)&doca->status);
        limparBuffer();
        if (doca->status != LIVRE && doca->status != OCUPADA)
            printf("ERRO: O status deve ser LIVRE [0] ou OCUPADA [1].\n");
    } while (doca->status != LIVRE && doca->status != OCUPADA);

    do
    {
        printf("Digite a capacidade maxima da Doca (em toneladas): ");
        scanf("%f", &doca->capacidadeMaxima);
        limparBuffer();
        if (doca->capacidadeMaxima <= 0)
        {
            printf("ERRO: A capacidade maxima deve ser maior que zero.\n");
        }
    } while (doca->capacidadeMaxima <= 0);
    printf("Doca editada com sucesso!\n");
}

Doca *buscarDocaPorNumero(Doca *docas, int totalDocas, int numero)
{
    for (int i = 0; i < totalDocas; i++)
    {
        if ((docas + i)->numeroDoca == numero)
        {
            return (docas + i);
        }
    }
    return NULL;
}

const char *traduzirTipo(TipoDoca tipo)
{
    switch (tipo)
    {
    case CARGA:
        return "Carga";
    case DESCARGA:
        return "Descarga";
    default:
        return "Indefinido";
    }
}

const char *traduzirStatus(StatusDoca status)
{
    switch (status)
    {
    case LIVRE:
        return "Livre";
    case OCUPADA:
        return "Ocupada";
    default:
        return "Indefinido";
    }
}