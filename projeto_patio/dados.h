#ifndef DADOS_H
#define DADOS_H

#include "structs.h"

// Declaração das variáveis globais
extern Caminhao caminhoes[5];
extern Doca docas[5];
extern Operacao operacoes[5];

// Declaração dos contadores de itens
extern int totalCaminhoes;
extern int totalDocas;
extern int totalOperacoes;

void inicializarDados();

#endif