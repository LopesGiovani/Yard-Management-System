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
    float capacidadeCarga; // Capacidade do caminhao em Toneladas

} Caminhao;

typedef struct
{
    int numeroDoca;
    TipoDoca tipo;     // Tipo carga ou descarga
    StatusDoca status; // Tipo Livre ou ocupada
    float capacidadeMaxima;
} Doca;

typedef struct
{
    char codigoOperacao[10];
    char placaCaminhao[8]; // referencia Caminhao
    int numeroDoca;        // referencia Doca
    struct tm dataHoraChegada;
    struct tm horaInicio;
    struct tm horaTermino;
    TipoDoca tipo; // Tipo carga ou descarga
    char produto[50];
    float pesoCarga; // Peso da carga em toneladas
    StatusOperacao status;
} Operacao;