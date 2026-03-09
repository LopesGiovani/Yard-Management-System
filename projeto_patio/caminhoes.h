#ifndef CAMINHOES_H
#define CAMINHOES_H

#include "structs.h"

// CREATE
void cadastrarCaminhao(Caminhao **caminhoes, int *totalCaminhoes, int *capCaminhoes);

// READ
void listarCaminhoes(Caminhao *caminhoes, int totalCaminhoes);
int buscarCaminhaoPorPlaca(Caminhao *caminhoes, int totalCaminhoes, char *placa);

// UPDATE
void editarCaminhao(Caminhao *caminhoes, int totalCaminhoes);

// DELETE
void deletarCaminhao(Caminhao **caminhoes, int *totalCaminhoes, int *capCaminhoes,
                     Operacao *operacoes, int totalOperacoes);

#endif