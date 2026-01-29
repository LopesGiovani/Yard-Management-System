#ifndef DOCAS_H
#define DOCAS_H

#include <stdio.h>
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

#endif