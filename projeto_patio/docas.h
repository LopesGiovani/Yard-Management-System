#ifndef DOCAS_H
#define DOCAS_H

#include "structs.h"


// Create
void cadastrarDoca(Doca *docas, int *totalDocas);

// Read
void listarDocas(Doca *docas, int *totalDocas);
Doca *buscarDocaPorNumero(Doca *docas, int *totalDocas, int numero);

// Update
void editarDoca(Doca *docas, int *totalDocas);

// Delete
void deletarDoca(Doca *docas, int *totalDocas);

// Operações para que os enums sejam legiveis na main ao serem printados
const char* traduzirTipo(TipoDoca tipo);
const char* traduzirStatus(StatusDoca status);

#endif