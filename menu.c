#include <stdio.h>
#include "menu.h"

void exibirMenuPrincipal(){
    printf("---------- Menu Principal ----------\n\n");
    printf("1- CAMINHOES\n");
    printf("2- DOCAS\n");
    printf("4- OPERACOES\n");
    printf("5- Consulta Filtrada de Operacoes"); // Mostra TODOS os dados de TODOS os registros de operações a partir de uma caracteristica especifica
    printf("6- Gerar relatórios\n");
    printf("\n");
    printf("0- SAIR\n");
}

void exibirSubMenuCaminhoes(){
    printf("---- Menu Caminhoes ----\n\n");
    printf("1- CADASTRO de Veículo\n");
    printf("2- CONSULTA de Veículo\n");
    printf("3- ALTERACAO DE DADOS de Veículo\n");
    printf("4- REMOCAO de Veículo\n");
    printf("5- LISTAGEM de todos os Caminhoes\n"); //Listagem de TODOS os dados de TODOS os caminhoes
    printf("\n");
    printf("0- Voltar ao Menu Principal\n");
}

void exibirSubMenuDocas(){
    printf("---- Menu Docas ----\n\n");
    printf("1- CADASTRO de Doca\n");
    printf("2- CONSULTA de Doca\n");
    printf("3- ALTERACAO DE DADOS de Doca\n");
    printf("4- REMOCAO de Doca\n");
    printf("5- LISTAGEM de todas as Docas\n"); //Listagem de TODOS os dados de TODAS as docas
    printf("\n");
    printf("0- Voltar ao Menu Principal\n");
}

void exibirSubMenuOperacoes(){
    printf("---- Menu Operacoes ----\n\n");
    printf("1- CADASTRO de Operacao\n");
    printf("2- CONSULTA de Operacao\n");
    printf("3- ALTERACAO DE DADOS de Operacao\n");
    printf("4- REMOCAO de Operacao\n");
    printf("\n");
    printf("0- Voltar ao Menu Principal\n");
}

void exibirSubMenuRelatorios(){
    printf("----- Menu Relatorios -----\n\n");
    printf("1- Filtrar por DATA\n");
    printf("2- Filtrar por PRODUTO\n");
    printf("3- Filtrar por DOCA\n");
    printf("\n");
    printf("0- Voltar ao Menu Principal\n\n");
}