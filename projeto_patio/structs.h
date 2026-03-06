#ifndef STRUCTS_H
#define STRUCTS_H

#include <time.h>

typedef enum
{
    PENDENTE,
    ATIVA,
    CONCLUIDA,
    CANCELADA
} StatusOperacao;

typedef enum
{
    CARGA,
    DESCARGA
} TipoDoca;

typedef enum
{
    LIVRE,
    OCUPADA
} StatusDoca;

typedef struct
{
    char placa[8];
    char transportadora[50];
    char tipoVeiculo[50];
    char motoristaNome[50];
    float capacidadeCarga; // Tons

} Caminhao;

typedef struct
{
    int numeroDoca;
    TipoDoca tipo;
    StatusDoca status;
    float capacidadeMaxima;
} Doca;

typedef struct
{
    char codigoOperacao[10];
    char placaCaminhao[8];  // FK to Caminhao
    int numeroDoca;         // FK to Doca
    struct tm dataHoraChegada;
    struct tm horaInicio;
    struct tm horaTermino;
    TipoDoca tipo;
    char carga[50];
    float pesoCarga; // Tons
    StatusOperacao status;
} Operacao;

#endif