#ifndef DADOS_H
#define DADOS_H

#include "structs.h"
#define EXTRA 5;

// Declaração das variáveis globais
extern Caminhao *caminhoes;
extern Doca *docas;
extern Operacao *operacoes;

// Declaração dos contadores de itens
extern int totalCaminhoes;
extern int totalDocas;
extern int totalOperacoes;

extern int capCaminhoes;
extern int capDocas;
extern int capOperacoes;

void inicializarDados();

#endif