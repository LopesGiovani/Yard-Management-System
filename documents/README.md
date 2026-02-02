# Sistema de Gestão de Pátio e Docas

Trabalho da disciplina **Algoritmos e Programação II** – 1ª entrega.  
Objetivo: implementar em C um sistema de gestão de pátio e docas para controlar caminhões que chegam a uma empresa/armazém para operações de **carga** e **descarga**.

## Autores

- Giovani de Oliveira Lopes Neto  
- Felipe Miranda Morais  
- Lucas Philipsen Borges  
- Pedro Batista Ribeiro  
- Vitor Eduardo Gonçalves Vasconcelos  

## Visão geral do sistema

O sistema simula o funcionamento de um **Yard Management System** simplificado, permitindo:

- Cadastro e consulta de **caminhões**
- Cadastro e consulta de **docas**
- Registro de **operações/agendamentos** (caminhão + doca + horários + produto)
- Consultas filtradas (por tipo de operação, placa, doca)
- Geração de **relatórios em arquivo texto** a partir de filtros (transportadora, produto, período, docas)

Tudo é implementado usando **structs em C**, com foco em manipulação de dados em memória e operações básicas de entrada/saída.

## Estruturas principais

### Estrutura 1 – Caminhões

Armazena os dados dos caminhões que chegam na empresa:

- `placa` (identificador único – não pode repetir)
- `transportadora`
- `tipoVeiculo` (ex: carreta, truck, toco)
- `motorista`
- `capacidadeCarga` (em toneladas ou kg)

### Estrutura 2 – Docas

Representa as docas disponíveis no armazém:

- `numeroDoca` (identificador único – ex: "Doca 1")
- `tipo` (carga ou descarga)
- `status` (livre ou ocupada)
- `capacidadeMaxima`

### Estrutura 3 – Operações / Agendamentos

Relaciona caminhões com docas:

- `codigoOperacao` (identificador único – ex: "OP-101")
- `placaCaminhao` (referência à Estrutura 1)
- `numeroDoca` (referência à Estrutura 2)
- `dataHoraChegada`
- `horaInicio`
- `horaTermino`
- `tipoOperacao` (carga ou descarga)
- `produto`
- `pesoCarga`

## Fluxo básico de uso

Exemplo de uso no dia a dia:

1. Um caminhão placa `ABC-1234` chega para **descarregar** 15 toneladas de arroz.
2. O sistema verifica se o caminhão já está cadastrado (Estrutura 1).
3. O sistema verifica quais docas de **descarga** estão livres (Estrutura 2).
4. O sistema cria uma **operação** vinculando o caminhão à doca (Estrutura 3).
5. São registrados: data/hora de chegada, início e término da operação.

## Consultas disponíveis

### 1. Operações ativas por tipo (Carga/Descarga)

- Filtro: tipo de operação (**carga** ou **descarga**).
- Retorna apenas operações **ativas** (sem hora de término).
- Exibe:
  - Estrutura 3: código da operação, data de chegada, hora de início, produto, peso.
  - Estrutura 1: placa do caminhão, nome do motorista.
  - Estrutura 2: número da doca.

### 2. Histórico de operações por placa

- Filtro: **placa do caminhão**.
- Exibe todas as operações (passadas e presentes) daquela placa:
  - Estrutura 3: código da operação, data de chegada, hora de início, hora de término, tipo, produto, peso.
  - Estrutura 2: número da doca.
  - Estrutura 1: placa e nome do motorista (no cabeçalho da consulta).

### 3. Operações por doca específica

- Filtro: **número da doca**.
- Exibe todas as operações daquela doca, priorizando a operação ativa (se existir):
  - Estrutura 3: código da operação, status (Ativa ou Concluída), data de chegada, produto, peso.
  - Estrutura 1: placa do caminhão, transportadora.
  - Estrutura 2: número da doca (no título da consulta).

## Relatórios em arquivo texto

O sistema gera arquivos `.txt` formatados, com base em filtros fornecidos pelo usuário.

### Opção 1 – Relatório por Transportadora (em período)

- Filtros:
  - Nome da **transportadora** (Estrutura 1)
  - **Período** (data inicial e final)
- Lógica:
  - Busca todas as placas da transportadora (Estrutura 1).
  - Filtra todas as operações dessas placas dentro do período (Estrutura 3).
- Saída:
  - Arquivo exemplo: `Relatorio_TranspNobre_Nov2025.txt`
  - Inclui dados completos da operação, caminhão e doca.

### Opção 2 – Relatório por Produto (em período)

- Filtros:
  - Nome do **produto/mercadoria** (Estrutura 3)
  - **Período** (data inicial e final)
- Lógica:
  - Filtra todas as operações do produto no período.
- Saída:
  - Arquivo exemplo: `Relatorio_Arroz_Nov2025.txt`
  - Lista operações de carga e descarga do produto, com dados do caminhão e da doca.

### Opção 3 – Relatório de Ocupação de Docas (em período)

- Filtro:
  - **Período** (data inicial e final)
- Lógica:
  - Agrupa operações por doca e calcula estatísticas.
- Saída:
  - Arquivo exemplo: `Relatorio_Docas_Nov2025.txt`
  - Para cada doca:
    - Tipo (carga/descarga)
    - Número total de operações no período
    - Peso total movimentado

## Como compilar e executar

### Opção 1: Via CodeBlocks (Recomendado)
1. Abra o arquivo `projeto_patio/projeto_patio.cbp`.
2. Clique em **Build & Run** (F9).

### Opção 2: Via Terminal (GCC)
```bash
cd projeto_patio
gcc main.c caminhoes.c docas.c dados.c menu.c -o gestao_patio
./gestao_patio
```
