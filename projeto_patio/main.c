#include <stdio.h>
#include <stdlib.h>
#include "menu.h"
#include "caminhoes.h"
#include "docas.h"
#include "operacoes.h"
#include "dados.h"

void limparBuffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

int main()
{
    inicializarDados();
    carregarDados();

    int escolha = -1;

    printf("Bem vindo ao sistema de gestao de patio e docas!\n");

    while (escolha != 0)
    {
        exibirMenuPrincipal();
        printf("\nEscolha uma opcao: ");
        if (scanf("%d", &escolha) != 1)
        {
            printf("\nOpcao invalida (digite um numero)!\n");
            limparBuffer();
            escolha = -1;
            continue;
        }

        switch (escolha)
        {
        case 1: // OPÇÃO 1: CAMINHÕES
        {
            int subEscolhaCaminhoes = -1;
            while (subEscolhaCaminhoes != 0)
            {
                exibirSubMenuCaminhoes();
                printf("\nEscolha uma opcao: ");
                if (scanf("%d", &subEscolhaCaminhoes) != 1)
                {
                    printf("\nOpcao invalida (digite um numero)!\n");
                    limparBuffer();
                    subEscolhaCaminhoes = -1;
                    continue;
                }

                switch (subEscolhaCaminhoes)
                { // SUBMENU CAMINHÕES
                case 1:
                    cadastrarCaminhao(&caminhoes, &totalCaminhoes, &capCaminhoes);
                    break;
                case 2:
                {
                    char placaBusca[8];
                    printf("\nDigite a placa do caminhao: ");
                    scanf("%7s", placaBusca);
                    limparBuffer();

                    Caminhao *caminhaoEncontrado = buscarCaminhaoPorPlaca(caminhoes, totalCaminhoes, placaBusca);

                    if (caminhaoEncontrado != NULL)
                    {
                        printf("\nCaminhao encontrado!\n");
                        printf("Transportadora: %s\n", caminhaoEncontrado->transportadora);
                        printf("Nome do motorista: %s\n", caminhaoEncontrado->motoristaNome);
                        printf("Tipo de veiculo: %s\n", caminhaoEncontrado->tipoVeiculo);
                        printf("Capacidade de carga: %.2lf\n", caminhaoEncontrado->capacidadeCarga);
                    }
                    else
                    {
                        printf("\nCaminhao nao encontrado!\n");
                    }
                    break;
                }
                case 3:
                    editarCaminhao(caminhoes, totalCaminhoes);
                    break;
                case 4:
                    deletarCaminhao(&caminhoes, &totalCaminhoes, &capCaminhoes, operacoes, totalOperacoes);
                    break;
                case 5:
                    listarCaminhoes(caminhoes, totalCaminhoes);
                    break;

                case 0:
                    printf("\nVoltando ao menu principal...\n");
                    break;
                default:
                    printf("\nEscolha invalida!\n");
                    break;
                }
            }
            break;
        }

        case 2: // OPÇÃO 2: DOCAS
        {
            int subEscolhaDocas = -1;
            while (subEscolhaDocas != 0)
            {
                exibirSubMenuDocas();
                printf("\nEscolha uma opcao: ");
                if (scanf("%d", &subEscolhaDocas) != 1)
                {
                    printf("\nOpcao invalida (digite um numero)!\n");
                    limparBuffer();
                    subEscolhaDocas = -1;
                    continue;
                }

                switch (subEscolhaDocas)
                { // SUBMENU DOCAS
                case 1:
                    cadastrarDoca(&docas, &totalDocas, &capDocas);
                    break;
                case 2:
                {
                    int docaBusca;
                    printf("\nDigite o numero da doca: ");
                    if (scanf("%d", &docaBusca) != 1)
                    {
                        printf("\nNumero invalido!\n");
                        limparBuffer();
                        break;
                    }

                    Doca *docaEncontrada = buscarDocaPorNumero(docas, totalDocas, docaBusca);

                    if (docaEncontrada != NULL)
                    {
                        printf("\n--- Doca Encontrada ---\n");
                        printf("Numero: %d\n", docaEncontrada->numeroDoca);
                        printf("Capacidade: %.2f Ton\n", docaEncontrada->capacidadeMaxima);
                        printf("Operacao: %s\n", traduzirTipo(docaEncontrada->tipo));
                        printf("Situacao: %s\n", traduzirStatus(docaEncontrada->status));
                    }
                    else
                    {
                        printf("\nErro: Doca %d nao existe no sistema.\n", docaBusca);
                    }
                    break;
                }
                case 3:
                    editarDoca(docas, totalDocas);
                    break;
                case 4:
                    deletarDoca(&docas, &totalDocas, &capDocas, operacoes, totalOperacoes);
                    break;

                case 5:
                    listarDocas(docas, totalDocas);
                    break;

                case 0:
                    printf("\nVoltando ao menu principal...\n");
                    break;
                default:
                    printf("\nEscolha invalida!\n");
                    break;
                }
            }
            break;
        }

        case 3: // OPÇÃO 3: OPERAÇÃO
        {
            int subEscolhaOp = -1;
            while (subEscolhaOp != 0)
            {
                exibirSubMenuOperacoes();
                printf("\nEscolha uma opcao: ");
                if (scanf("%d", &subEscolhaOp) != 1)
                {
                    printf("\nOpcao invalida (digite um numero)!\n");
                    limparBuffer();
                    subEscolhaOp = -1;
                    continue;
                }

                switch (subEscolhaOp)
                {
                case 1:
                    cadastrarOperacao(&operacoes, &totalOperacoes, caminhoes, totalCaminhoes, docas, totalDocas, &capOperacoes);
                    break;
                case 2:
                    buscarOperacao(operacoes, totalOperacoes, caminhoes, totalCaminhoes, docas, totalDocas);
                    break;
                case 3:
                    editarOperacao(operacoes, totalOperacoes);
                    break;
                case 4:
                    deletarOperacao(operacoes, &totalOperacoes);
                    break;
                case 5:
                    listarOperacoes(operacoes, totalOperacoes, caminhoes, totalCaminhoes, docas, totalDocas);
                    break;

                case 6:
                    consultarOperacoesFiltradas(operacoes, totalOperacoes,
                                                caminhoes, totalCaminhoes,
                                                docas, totalDocas);
                    break;
                case 0:
                    printf("\nVoltando ao menu principal...\n");
                    break;
                default:
                    printf("\nEscolha invalida!\n");
                    break;
                }
            }
            break;
        }
        
        case 0:
            printf("\nSaindo do sistema. Ate logo!\n");
            salvarDados();
            free(caminhoes);
            free(docas);
            free(operacoes);
            break;

        default:
            printf("Opcao invalida!\n");
            break;
        }
    }

    return 0;
}