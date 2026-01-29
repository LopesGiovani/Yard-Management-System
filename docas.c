#include <stdio.h>
#include "docas.h"
#include "structs.h"

void limparBuffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
        
}

void cadastrarDoca(Doca *docas, int *totalDocas)
{
    if (*totalDocas >= 5)
    {
        printf("\nERRO: Capacidade maxima de docas atingida (5).\n");
        return;
    }

    Doca new;
    printf("\n--- Cadastrar Doca ---\n");
    printf("Digite o numero da doca: ");
    limparBuffer();
    scanf("%d", &new.numeroDoca);

    if (buscarDocaPorNumero(docas, totalDocas, new.numeroDoca) != NULL)
    {
        printf("ERRO: Ja existe uma doca cadastrada com este numero.\n");
        return;
    }

    do
    {
        printf("Digite o tipo da Doca (CARGA [0] ou DESCARGA [1]): ");
        limparBuffer();
        scanf("%d", (int *)&new.tipo);
        if (new.tipo != 0 && new.tipo != 1)
            printf("ERRO: O tipo deve ser CARGA [0] ou DESCARGA [1].\n");
    } while (new.tipo != 0 && new.tipo != 1);

    do
    {
        printf("Digite o status da Doca (LIVRE [0] ou OCUPADA [1]): ");
        limparBuffer();
        scanf("%d", (int *)&new.status);
        if (new.status != 0 && new.status != 1)
            printf("ERRO: O status deve ser LIVRE [0] ou OCUPADA [1].\n");
    } while (new.status != 0 && new.status != 1);

    do
    {
        printf("Digite a capacidade maxima da Doca (em toneladas): ");
        limparBuffer();
        scanf("%f", &new.capacidadeMaxima);
        if (new.capacidadeMaxima == 0)
        {
            printf("ERRO: A capacidade maxima deve ser maior que zero.\n");
        }
    } while (new.capacidadeMaxima == 0);

    docas[*totalDocas] = new;
    (*totalDocas)++;
    printf("Doca cadastrada com sucesso!\n");
}
void listarDocas(Doca *docas, int *totalDocas)
{
    printf("\n--- Lista de Docas ---\n");

    if (*totalDocas == 0)
    {
        printf("Nenhuma doca cadastrada.\n");
        return;
    }

    for (int i = 0; i < *totalDocas; i++)
    {
        printf("Doca %d\n", i + 1);
        printf("Numero: %d\n", (docas + i)->numeroDoca);
        printf("Tipo: %s\n", (docas + i)->tipo == CARGA ? "CARGA" : "DESCARGA");
        printf("Status: %s\n", (docas + i)->status == LIVRE ? "LIVRE" : "OCUPADA");
        printf("Capacidade Maxima: %.2f toneladas\n", (docas + i)->capacidadeMaxima);
        printf("--------------------------\n");
    }
}

void deletarDoca(Doca *docas, int *totalDocas)
{
    int numero;
    printf("\n--- Deletar Doca ---\n");
    printf("Digite o numero da doca a ser deletada: ");
    limparBuffer();
    scanf("%d", &numero);

    int indice = -1;
    for (int i = 0; i < *totalDocas; i++)
    {
        if ((docas + i)->numeroDoca == numero)
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

    for (int i = indice; i < *totalDocas - 1; i++)
    {
        docas[i] = docas[i + 1];
    }
    (*totalDocas)--;
    printf("Doca deletada com sucesso!\n");
}
    

    void editarDoca(Doca *docas, int *totalDocas)
    {
        
        int numero;
        printf("\n--- Editar Doca ---\n");
        printf("Digite o numero da doca a ser editada: ");
        limparBuffer();
        scanf("%d", &numero);

        Doca *doca = buscarDocaPorNumero(docas, totalDocas, numero);
        if (doca == NULL)
        {
            printf("ERRO: Doca com numero %d nao encontrada.\n", numero);
            return;
        }

        do
    {
        printf("Digite o novo tipo da Doca (CARGA [0] ou DESCARGA [1]): ");
        limparBuffer();
        scanf("%d", (int *)&doca->tipo);
        if (doca->tipo != 0 && doca->tipo != 1)
            printf("ERRO: O tipo deve ser CARGA [0] ou DESCARGA [1].\n");
    } while (doca->tipo != 0 && doca->tipo != 1);

        do
    {
        printf("Digite o novo status da Doca (LIVRE [0] ou OCUPADA [1]): ");
        limparBuffer();
        scanf("%d", (int *)&doca->status);
        if (doca->status != 0 && doca->status != 1)
            printf("ERRO: O status deve ser LIVRE [0] ou OCUPADA [1].\n");
    } while (doca->status != 0 && doca->status != 1);

        do
    {
        printf("Digite a capacidade maxima da Doca (em toneladas): ");
        limparBuffer();
        scanf("%f", &doca->capacidadeMaxima);
        if (doca->capacidadeMaxima == 0)
        {
            printf("ERRO: A capacidade maxima deve ser maior que zero.\n");
        }
    } while (doca->capacidadeMaxima == 0);
        printf("Doca editada com sucesso!\n");
}

Doca *buscarDocaPorNumero(Doca *docas, int *totalDocas, int numero)
{
    for (int i = 0; i < *totalDocas; i++)
    {
        if ((docas + i)->numeroDoca == numero)
        {
            return (docas + i);
        }
    }
    return NULL;
}