#ifndef DADOS_H
#define DADOS_H

#include "structs.h"

// Global arrays - actual storage in dados.c
extern Caminhao caminhoes[5];
extern Doca docas[5];
extern Operacao operacoes[5];

void inicializarDados();

#endif