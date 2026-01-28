#include <stdio.h>
#include "dados.h"

Caminhao caminhoes[5];
Doca docas[5];
Operacao operacoes[5];

void inicializarDados()
{
    caminhoes[0] = (Caminhao){"ABC1234", "TransporteA", "CaminhaoA", "Joao Silva", 10};
    caminhoes[1] = (Caminhao){"DEF5678", "TransporteB", "CaminhaoB", "Maria Silva", 15};
    caminhoes[2] = (Caminhao){"GHI9012", "TransporteC", "CaminhaoC", "Carlos Oliveira", 20};

    docas[0] = (Doca){1, CARGA, LIVRE, 20.0};
    docas[1] = (Doca){2, DESCARGA, LIVRE, 25.0};
    docas[2] = (Doca){3, CARGA, LIVRE, 30.0};

    operacoes[0] = (Operacao){"OP001", "ABC1234", 1, {0}, {0}, {0}, CARGA, "ProdutoA", 10.0, PENDENTE};
    operacoes[1] = (Operacao){"OP002", "DEF5678", 2, {0}, {0}, {0}, DESCARGA, "ProdutoB", 15.0, PENDENTE};
    operacoes[2] = (Operacao){"OP003", "GHI9012", 3, {0}, {0}, {0}, CARGA, "ProdutoC", 20.0, PENDENTE};
}