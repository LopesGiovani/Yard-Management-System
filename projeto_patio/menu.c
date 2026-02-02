#include <stdio.h>
#include "menu.h"

void exibirMenuPrincipal(){
    printf("\n--------- Menu Principal ----------\n\n");
    printf("1- CAMINHOES\n");
    printf("2- DOCAS\n");
    printf("3- OPERACOES\n");
    printf("4- Consulta Filtrada de Operacoes\n");
    printf("5- Gerar relatorios\n");
    printf("-----------------------------------\n");
    printf("0- SAIR\n");
}

void exibirSubMenuCaminhoes(){
    printf("\n---- Menu Caminhoes ----\n\n");
    printf("1- CADASTRO de Veiculo\n");
    printf("2- CONSULTA de Veiculo\n");
    printf("3- ALTERACAO DE DADOS de Veiculo\n");
    printf("4- REMOCAO de Veiculo\n");
    printf("5- LISTAGEM de todos os Caminhoes\n");
    printf("\n");
    printf("0- Voltar ao Menu Principal\n");
}

void exibirSubMenuDocas(){
    printf("\n---- Menu Docas ----\n\n");
    printf("1- CADASTRO de Doca\n");
    printf("2- CONSULTA de Doca\n");
    printf("3- ALTERACAO DE DADOS de Doca\n");
    printf("4- REMOCAO de Doca\n");
    printf("5- LISTAGEM de todas as Docas\n");
    printf("\n");
    printf("0- Voltar ao Menu Principal\n");
}

void exibirSubMenuOperacoes(){
    printf("\n---- Menu Operacoes ----\n\n");
    printf("1- CADASTRO de Operacao\n");
    printf("2- CONSULTA de Operacao\n");
    printf("3- ALTERACAO DE DADOS de Operacao\n");
    printf("4- REMOCAO de Operacao\n");
    printf("\n");
    printf("0- Voltar ao Menu Principal\n");
}

void exibirSubMenuRelatorios(){
    printf("\n----- Menu Relatorios -----\n\n");
    printf("1- Filtrar por DATA\n");
    printf("2- Filtrar por PRODUTO\n");
    printf("3- Filtrar por DOCA\n");
    printf("\n");
    printf("0- Voltar ao Menu Principal\n\n");
}