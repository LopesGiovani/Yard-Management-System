#ifndef CAMINHOES_H
#define CAMINHOES_H

#include "structs.h"

// Create
void cadastrarCaminhao(Caminhao *caminhoes, int *totalCaminhoes);

// Read
void listarCaminhoes(Caminhao *caminhoes, int *totalCaminhoes);
Caminhao *buscarCaminhaoPorPlaca(Caminhao *caminhoes, int *totalCaminhoes, char *placa);

// Update
void editarCaminhao(Caminhao *caminhoes, int *totalCaminhoes);

// Delete
void deletarCaminhao(Caminhao *caminhoes, int *totalCaminhoes);

#endif
