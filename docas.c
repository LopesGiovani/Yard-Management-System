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

    if (buscarDocaPorNumero(docas, *totalDocas, new.numeroDoca) != NULL)
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
            return;
        }
    } while (new.capacidadeMaxima == 0);

    docas[*totalDocas] = new;
    (*totalDocas)++;
    printf("Doca cadastrada com sucesso!\n");
}
