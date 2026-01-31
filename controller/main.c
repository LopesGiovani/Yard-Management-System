#include <stdio.h>
#include "menu.h"
#include "caminhoes.h"
#include "docas.h"

int main() {
    Caminhao listaCaminhoes[5];
    int totalCaminhoes = 0;

    Doca listaDocas[5];
    int totalDocas = 0;

    int escolha = -1;

    printf("Bem vindo ao sistema de gestao de patio e docas!\n");

    while (escolha != 0) {
        exibirMenuPrincipal();
        printf("\nEscolha uma opcao: ");
        scanf("%d", &escolha);

        switch (escolha) {
            case 1: // OPÇÃO 1: CAMINHÕES
            {
                int subEscolhaCaminhoes = -1;
                while (subEscolhaCaminhoes != 0) {
                    exibirSubMenuCaminhoes();
                    printf("\nEscolha uma opcao: ");
                    scanf("%d", &subEscolhaCaminhoes);

                    switch (subEscolhaCaminhoes) { // SUBMENU CAMINHÕES
                        case 1:
                            cadastrarCaminhao(listaCaminhoes, &totalCaminhoes);
                            break;
                        case 2: {
                            char placaBusca[8];
                            printf("\nDigite a placa do caminhao: ");
                            scanf("%s", placaBusca);

                            Caminhao *caminhaoEncontrado = buscarCaminhaoPorPlaca(listaCaminhoes, &totalCaminhoes, placaBusca);

                            if (caminhaoEncontrado != NULL) {
                                printf("\nCaminhao encontrado!\n");
                                printf("Transportadora: %s\n", caminhaoEncontrado->transportadora);
                                printf("Nome do motorista: %s\n", caminhaoEncontrado->motoristaNome);
                                printf("Tipo de veiculo: %s\n", caminhaoEncontrado->tipoVeiculo);
                                printf("Capacidade de carga: %.2lf\n", caminhaoEncontrado->capacidadeCarga);
                            } else {
                                printf("\nCaminhao nao encontrado!\n");
                            }
                            break;
                        }
                        case 3:
                            editarCaminhao(listaCaminhoes, &totalCaminhoes);
                            break;
                        case 4:
                            deletarCaminhao(listaCaminhoes, &totalCaminhoes);
                            break;
                        case 5:
                            listarCaminhoes(listaCaminhoes, &totalCaminhoes);
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
                while (subEscolhaDocas != 0) {
                    exibirSubMenuDocas();
                    printf("\nEscolha uma opcao: ");
                    scanf("%d", &subEscolhaDocas);

                    switch (subEscolhaDocas) { // SUBMENU DOCAS
                        case 1:
                            cadastrarDoca(listaDocas, &totalDocas);
                            break;
                        case 2: {
                            int docaBusca;
                            printf("\nDigite o numero da doca: ");
                            scanf("%d", &docaBusca); 

                            Doca *docaEncontrada = buscarDocaPorNumero(listaDocas, &totalDocas, docaBusca);

                            if (docaEncontrada != NULL) {
                                printf("\n--- Doca Encontrada ---\n");
                                printf("Numero: %d\n", docaEncontrada->numeroDoca);
                                printf("Capacidade: %.2f Ton\n", docaEncontrada->capacidadeMaxima);
                                printf("Operacao: %s\n", traduzirTipo(docaEncontrada->tipo));
                                printf("Situacao: %s\n", traduzirStatus(docaEncontrada->status));
                            } else {
                                printf("\nErro: Doca %d nao existe no sistema.\n", docaBusca);
                            }
                            break;
                        }
                        case 3:
                            editarDoca(listaDocas, &totalDocas);
                            break;
                        case 4:
                            deletarDoca(listaDocas, &totalDocas);
                            break;

                        case 5:
                            listarDocas(listaDocas, &totalDocas);
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

            case 3: // OPÇÃO 3: OPERAÇÕES
                exibirSubMenuOperacoes();
                break;

            case 0:
                printf("Saindo do sistema...\n");
                break;

            default:
                printf("Opcao invalida!\n");
                break;
        }
    }

    return 0;
}