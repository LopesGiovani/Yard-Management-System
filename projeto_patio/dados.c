#include <stdlib.h>
#include <stdio.h>
#include "dados.h"


Caminhao *caminhoes;
Doca *docas;
Operacao *operacoes;

// Total de registros cadastrados
int totalCaminhoes  = 0;
int totalDocas      = 0;
int totalOperacoes  = 0;

// Capacidade atual alocada (total + slots livres)
int capCaminhoes  = 0;
int capDocas      = 0;
int capOperacoes  = 0;


void inicializarDados()
{
    caminhoes = calloc(EXTRA, sizeof(Caminhao));
    docas     = calloc(EXTRA, sizeof(Doca));
    operacoes = calloc(EXTRA, sizeof(Operacao));

    if (caminhoes == NULL || docas == NULL || operacoes == NULL) {
        printf("ERRO: Falha ao alocar memoria inicial!\n");
        exit(1);
    }

    capCaminhoes = EXTRA;
    capDocas     = EXTRA;
    capOperacoes = EXTRA;

    // chamar carregarDados() para ler os .bin
    // Por enquanto manter os dados mockados:
    caminhoes[0] = (Caminhao){"ABC1234","TransporteA","CaminhaoA","Joao Silva",10};
    caminhoes[1] = (Caminhao){"DEF5678","TransporteB","CaminhaoB","Maria Silva",15};
    totalCaminhoes = 2;
    docas[0] = (Doca){1, CARGA, LIVRE, 20.0};
    docas[1] = (Doca){2, DESCARGA, LIVRE, 25.0};
    totalDocas = 2;
}