#include "caminhoes.h"
#include "dados.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// 'static' torna a funcao visivel apenas neste arquivo, evitando conflito de nomes com outros modulos (erro de linker)
static void limparBuffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void cadastrarCaminhao(Caminhao **caminhoes, int *totalCaminhoes, int *capCaminhoes)
{

    if (*totalCaminhoes >= *capCaminhoes)
    {
        int novaCap = *capCaminhoes + EXTRA;
        Caminhao *temp = realloc(*caminhoes, novaCap * sizeof(Caminhao));

        if(temp==NULL){

            printf("\nERRO: Capacidade maxima de caminhoes atingida (5).\n");
            return;           
        }

        *caminhoes = temp;
        *capCaminhoes = novaCap;
    }

    Caminhao novo;
    printf("\n--- Cadastrar Caminhao ---\n");
    printf("Digite a placa do caminhao: ");
    limparBuffer();
    fgets(novo.placa, sizeof(novo.placa), stdin);
    novo.placa[strcspn(novo.placa, "\n")] = 0;

    if (buscarCaminhaoPorPlaca(*caminhoes, *totalCaminhoes, novo.placa) != -1)
    {
        printf("ERRO: Ja existe um caminhao cadastrado com esta placa.\n");
        return;
    }

    do
    {
        printf("Digite a transportadora: ");

        fgets(novo.transportadora, sizeof(novo.transportadora), stdin);
        novo.transportadora[strcspn(novo.transportadora, "\n")] = 0;
        if (strlen(novo.transportadora) == 0)
            printf("ERRO: O campo nao pode ser vazio.\n");
    } while (strlen(novo.transportadora) == 0);

    do
    {
        printf("Tipo de Veiculo: ");

        fgets(novo.tipoVeiculo, sizeof(novo.tipoVeiculo), stdin);
        novo.tipoVeiculo[strcspn(novo.tipoVeiculo, "\n")] = 0;
        if (strlen(novo.tipoVeiculo) == 0)
            printf("ERRO: O campo nao pode ser vazio.\n");
    } while (strlen(novo.tipoVeiculo) == 0);

    do
    {
        printf("Nome do Motorista: ");
        fgets(novo.motoristaNome, sizeof(novo.motoristaNome), stdin);
        novo.motoristaNome[strcspn(novo.motoristaNome, "\n")] = 0;
        if (strlen(novo.motoristaNome) == 0)
            printf("ERRO: O campo nao pode ser vazio.\n");
    } while (strlen(novo.motoristaNome) == 0);

    do
    {
        printf("Capacidade de Carga (toneladas): ");
        scanf("%f", &novo.capacidadeCarga);
        limparBuffer();
        if(novo.capacidadeCarga <= 0)
            printf("ERRO: A capacidade deve ser maior que zero.\n");
    } while (novo.capacidadeCarga <= 0 );
    
    (*caminhoes)[(*totalCaminhoes)] = novo;
    (*totalCaminhoes)++;
    printf("Caminhao cadastrado com sucesso!\n");
}

void listarCaminhoes(Caminhao *caminhoes, int totalCaminhoes)
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
        printf("  Placa         : %s\n", (caminhoes + i)->placa);
        printf("  Transportadora: %s\n", (caminhoes + i)->transportadora);
        printf("  Tipo de Veiculo: %s\n", (caminhoes + i)->tipoVeiculo);
        printf("  Motorista     : %s\n", (caminhoes + i)->motoristaNome);
        printf("  Cap. de Carga : %.2f toneladas\n", (caminhoes + i)->capacidadeCarga);
        printf("  -----------------------------\n");
    }
}

int buscarCaminhaoPorPlaca(Caminhao *caminhoes, int totalCaminhoes, char *placa)
{
    for (int i = 0; i < totalCaminhoes; i++)
    {
        if (strcmp((caminhoes + i)->placa, placa) == 0)
            return i;
    }

    return -1;
}

void editarCaminhao(Caminhao *caminhoes, int totalCaminhoes)
{
    char placaTemp[8];
    printf("\n--- Editar Caminhao ---\n");
    printf("Digite a placa do caminhao desejado: ");
    limparBuffer();
    fgets(placaTemp, sizeof(placaTemp), stdin);
    placaTemp[strcspn(placaTemp, "\n")] = 0;

    int indiceEncontrado = buscarCaminhaoPorPlaca(caminhoes, totalCaminhoes, placaTemp);

    if (indiceEncontrado == -1)
    {
        printf("ERRO: Caminhao nao encontrado.\n");
        return;
    }

    Caminhao *encontrado = &caminhoes[indiceEncontrado];

    printf("Editando caminhao da placa %s\n", placaTemp);
    
    char novaTransp[50];
    printf("Nova Transportadora (Enter mantem '%s'): ", encontrado->transportadora);

    fgets(novaTransp, sizeof(novaTransp), stdin);
    if (novaTransp[0] != '\n')
    {
        novaTransp[strcspn(novaTransp, "\n")] = 0;
        strcpy(encontrado->transportadora, novaTransp);
    }

    char novoMotorista[50];
    printf("Novo motorista (Enter mantem '%s'): ", encontrado->motoristaNome);

    fgets(novoMotorista, sizeof(novoMotorista), stdin);
    if (novoMotorista[0] != '\n')
    {
        novoMotorista[strcspn(novoMotorista, "\n")] = 0;
        strcpy(encontrado->motoristaNome, novoMotorista);
    }

    printf("Caminhao atualizado!\n");
}

void deletarCaminhao(Caminhao **caminhoes, int *totalCaminhoes, int *capCaminhoes,
                     Operacao *operacoes, int totalOperacoes)
{
    char placaTemp[8];
    printf("\n--- Deletar Caminhao ---\n");
    printf("Digite a placa do caminhao desejado: ");
    limparBuffer();
    fgets(placaTemp, sizeof(placaTemp), stdin);
    placaTemp[strcspn(placaTemp, "\n")] = 0;

    // Verifica se o caminhao existe
    int indice = -1;
    for (int i = 0; i < *totalCaminhoes; i++)
    {
        if (strcmp((*caminhoes + i)->placa, placaTemp) == 0)
        {
            indice = i;
            break;
        }
    }
    if (indice == -1)
    {
        printf("ERRO: Caminhao nao encontrado.\n");
        return;
    }

    // Restricao de integridade: nao pode deletar se estiver em alguma operacao
    for (int i = 0; i < totalOperacoes; i++)
    {
        if (strcmp(operacoes[i].placaCaminhao, placaTemp) == 0)
        {
            printf("ERRO: Caminhao esta em uso na operacao '%s'. Remova a operacao primeiro.\n",
                   operacoes[i].codigoOperacao);
            return;
        }
    }

    // Desloca elementos para preencher o buraco
    for (int i = indice; i < *totalCaminhoes - 1; i++)
        (*caminhoes)[i] = (*caminhoes)[i + 1];
    (*totalCaminhoes)--; 

    // Verifica se ha posicoes livres demais e reduz
    int livres = *capCaminhoes - *totalCaminhoes;
    if (livres > EXTRA) 
    {
        int novaCap = *totalCaminhoes + EXTRA;
        Caminhao *temp = realloc(*caminhoes, novaCap * sizeof(Caminhao));
        if (temp != NULL)
        {
            *caminhoes    = temp;
            *capCaminhoes = novaCap;
        }
    }

    printf("Caminhao removido com sucesso.\n");
}