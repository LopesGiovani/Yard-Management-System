#include "caminhoes.h"
#include <stdio.h>

void limparBuffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

void cadastrarCaminhao(Caminhao *caminhoes, int *totalCaminhoes)
{

    if (*totalCaminhoes >= 5)
    {
        printf("\nERRO: Capacidade maxima de caminhoes atingida (5).\n");
        return;
    }

    Caminhao new;
    printf("\n--- Cadastrar Caminhao ---\n");
    printf("Digite a placa do caminhao: ");
    limparBuffer();
    fgets(new.placa, 8, stdin);

    if (buscarCaminhaoPorPlaca(caminhoes, *totalCaminhoes, new.placa) != NULL)
    {
        printf("ERRO: Ja existe um caminhao cadastrado com esta placa.\n");
        return;
    }

    do
    {
        printf("Digite a transportadora: ");
        limparBuffer();
        fgets(new.transportadora, 50, stdin);
        if (strlen(new.transportadora) == 0)
            printf("ERRO: O campo nao pode ser vazio.\n");
    } while (strlen(new.transportadora) == 0);

    do
    {
        printf("Tipo de Veiculo: ");
        limparBuffer();
        fgets(new.tipoVeiculo, 50, stdin);
        if (strlen(new.tipoVeiculo) == 0)
            printf("ERRO: O campo nao pode ser vazio.\n");
    } while (strlen(new.tipoVeiculo) == 0);

    do
    {
        printf("Nome do Motorista: ");
        fgets(new.motoristaNome, 50, stdin);
        if (strlen(new.motoristaNome) == 0)
            printf("ERRO: O campo nao pode ser vazio.\n");
    } while (strlen(new.motoristaNome) == 0);

    printf("Capacidade de Carga (toneladas): ");
    scanf("%f", &new.capacidadeCarga);

    caminhoes[(*totalCaminhoes)] = new;

    (*totalCaminhoes)++;

    printf("Caminhao cadastrado com sucesso!\n");
}

void listarCaminhoes(Caminhao *caminhoes, int *totalCaminhoes)
{
    printf("\n--- Lista de Caminhoes Cadastrados ---\n");
    if (totalCaminhoes == 0)
    {
        printf("Nenhum caminhao cadastrado.\n");
        return;
    }

    for (int i = 0; i < totalCaminhoes; i++)
    {
        printf("Caminhao %d:\n", i + 1);
        printf("Placa: %s", (caminhoes + i)->placa);
        printf("Transportadora: %s", (caminhoes + i)->transportadora);
        printf("Tipo de Veiculo: %s", (caminhoes + i)->tipoVeiculo);
        printf("Motorista: %s", (caminhoes + i)->motoristaNome);
        printf("Capacidade de Carga: %.2f toneladas\n", (caminhoes + i)->capacidadeCarga);
        printf("-----------------------------\n");
    }
}

Caminhao *buscarCaminhaoPorPlaca(Caminhao *caminhoes, int *totalCaminhoes, char *placa)
{
    for (int i = 0; i < totalCaminhoes; i++)
    {
        if (strcmp((caminhoes + i)->placa, placa) == 0)
        {
            return (caminhoes + i);
        }
    }

    return NULL;
}

void editarCaminhao(Caminhao *caminhoes, int *totalCaminhoes)
{
    char placaTemp[8];
    printf("\n--- Editar Caminhao ---\n");
    printf("Digite a placa do caminhao desejado: ");
    limparBuffer();
    fgets(placaTemp, 8, stdin);
    Caminhao *encontrado = buscarCaminhaoPorPlaca(caminhoes, totalCaminhoes, placaTemp);

    if (encontrado == NULL)
    {
        printf("ERRO: Caminhao nao encontrado\n");
        return;
    }

    printf("Editando caminhao da placa %s\n", placaTemp);

    printf("Nova Transportadora (Enter mantem '%s'): ", encontrado->transportadora);
    char novaTransp[50];
    fgets(novaTransp, 50, stdin);
    if (novaTransp[0] != '\n')
    {
        strcpy(encontrado->transportadora, novaTransp);
    }

    printf("Novo motorista (Enter mantem '%s'): ", encontrado->motoristaNome);
    char novoMotorista[50];
    fgets(novoMotorista, 50, stdin);
    if (novoMotorista[0] != '\n')
    {
        strcpy(encontrado->transportadora, novoMotorista);
    }

    printf("Caminhao atualizado!\n");
}

void deletarCaminhao(Caminhao *caminhoes, int *totalCaminhoes)
{
    char placaTemp[8];
    printf("\n--- Deletar Caminhao ---\n");
    printf("Digite a placa do caminhao desejado: ");
    limparBuffer();
    fgets(placaTemp, 8, stdin);
    Caminhao *encontrado = buscarCaminhaoPorPlaca(caminhoes, totalCaminhoes, placaTemp);

    if (encontrado == NULL)
    {
        printf("ERRO: Caminhao nao encontrado\n");
        return;
    }

    int indice = -1;

    for (int i = 0; i < totalCaminhoes; i++)
    {
        if (strcmp((caminhoes + i)->placa) == 0)
        {
            indice = i;
            break; // Para sair do loop apenas
        }
    }

    if (indice == -1)
    {
        printf("ERRO: Caminhao nao encontrado.\n");
        return;
    }

    for (int i = indice; i < *totalCaminhoes - 1; i++)
    {
        caminhoes[i] = caminhoes[i + 1];
    }

    (*totalCaminhoes)--;
    printf("Caminhao removido com sucesso.\n");
}