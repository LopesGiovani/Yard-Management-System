#ifndef OPERACOES_H
#define OPERACOES_H

#include "structs.h"

//Create
void cadastrarOperacao(Operacao **operacoes, int *totalOperacoes, Caminhao *caminhoes, int totalCaminhoes, Doca *docas, int totalDocas, int *capOperacoes);

//Retorna posição do registro
int buscarIndicePorCodigo(Operacao *operacoes, int totalOperacoes, char *codigoOperacao);

//Read
void listarOperacoes(Operacao *operacoes, int totalOperacoes, Caminhao *caminhoes, int totalCaminhoes, Doca *docas, int totalDocas);
void buscarOperacao(Operacao *operacoes, int totalOperacoes, Caminhao *caminhoes, int totalCaminhoes, Doca *docas, int totalDocas);

//Update
void editarOperacao(Operacao *operacoes, int totalOperacoes); 

//Delete
void deletarOperacao(Operacao **operacoes, int *totalOperacoes, int *capOperacoes);

//Traduz status da operação
const char *traduzirStatusOperacao(StatusOperacao status);

// Consultas Especificas
void consultarAtivasPorTipo(Operacao *operacoes, int totalOperacoes, Caminhao *caminhoes, int totalCaminhoes, Doca *docas, int totalDocas);
void consultarHistoricoPorPlaca(Operacao *operacoes, int totalOperacoes, Caminhao *caminhoes, int totalCaminhoes, Doca *docas, int totalDocas);
void consultarOperacoesPorDoca(Operacao *operacoes, int totalOperacoes, Caminhao *caminhoes, int totalCaminhoes, Doca *docas, int totalDocas);

// Gerar relatorios txt
void gerarRelatorioTransportadora(Operacao *operacoes, int totalOperacoes, Caminhao *caminhoes, int totalCaminhoes, Doca *docas, int totalDocas);
void gerarRelatorioProduto(Operacao *operacoes, int totalOperacoes, Caminhao *caminhoes, int totalCaminhoes, Doca *docas, int totalDocas);
void gerarRelatorioSumarioDocas(Operacao *operacoes, int totalOperacoes, Caminhao *caminhoes, int totalCaminhoes, Doca *docas, int totalDocas);

#endif