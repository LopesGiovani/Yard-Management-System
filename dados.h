#ifndef DADOS_H 
#define DADOS_H 

#include "structs.h"

// Global arrays - actual storage in dados.c
extern Caminhao caminhoes[3]; 
extern Doca docas[3];
extern Operacao operacoes[3];

void inicializarDados();

#endif