

# 📋 Plano de Execução – 2ª Entrega (Prazo: 02/02/2026)

**Equipe:**

- Giovani de Oliveira Lopes Neto
- Felipe Miranda Morais
- Lucas Philipsen Borges
- Pedro Batista Ribeiro
- Vitor Eduardo Gonçalves Vasconcelos

**Prazo final:** Segunda-feira, 02/02/2026 às 23:59

***

## 🎯 O que precisa estar pronto

- [ ] **3 Estruturas** (Caminhões, Docas, Operações)
- [ ] **1 Vetor de 5 elementos** para cada estrutura
- [ ] **Sistema de Menus**
- [ ] **Funções iniciais** (manipulação básica)
- [ ] **CRUD completo** das Estruturas 1 e 2 (Caminhões e Docas)

***

## 📅 Cronograma Semanal

### Semana 1: 22/01 a 26/01 – Estruturas e Configuração

| Dia | Atividade | Responsável | Entrega |
| :-- | :-- | :-- | :-- |
| **22/01 (Qui)** | Criar repositório GitHub + estrutura de pastas | **Giovani** | Repo criado + README |
| **22/01 (Qui)** | Definir structs das 3 estruturas em C | **Felipe** | Arquivo `structs.h` |
| **23/01 (Sex)** | Implementar vetores de 5 elementos + inicialização | **Lucas** | Arquivo `dados.c` |
| **24/01 (Sáb)** | Criar sistema de menus (principal + submenus) | **Pedro** | Arquivo `menu.c` |
| **25/01 (Dom)** | Revisão em grupo (todos testam no próprio PC) | **Todos** | Feedback no grupo |


***

### Semana 2: 27/01 a 02/02 – CRUDs e Finalização

| Dia | Atividade | Responsável | Entrega |
| :-- | :-- | :-- | :-- |
| **27/01 (Seg)** | CRUD Estrutura 1 (Caminhões): Create + Read | **Giovani + Felipe** | Funções `cadastrarCaminhao()`, `listarCaminhoes()` |
| **28/01 (Ter)** | CRUD Estrutura 1 (Caminhões): Update + Delete | **Giovani + Felipe** | Funções `editarCaminhao()`, `deletarCaminhao()` |
| **29/01 (Qua)** | CRUD Estrutura 2 (Docas): Create + Read | **Lucas + Pedro** | Funções `cadastrarDoca()`, `listarDocas()` |
| **30/01 (Qui)** | CRUD Estrutura 2 (Docas): Update + Delete | **Lucas + Pedro** | Funções `editarDoca()`, `deletarDoca()` |
| **31/01 (Sex)** | Integração dos CRUDs com menus + testes | **Vitor** | Sistema funcionando completo |
| **01/02 (Sáb)** | Testes finais + correção de bugs | **Todos** | Sistema validado |
| **02/02 (Dom)** | Preparar entrega: comentar código + gerar .zip | **Vitor** | **ENTREGA 23:59** |


***

## 📂 Estrutura de Arquivos do Projeto

```
├── projeto_patio.cbp          # Projeto CodeBlocks
├── main.c                      # Arquivo principal (main)
├── structs.h                   # Definição das structs
├── dados.c                     # Vetores + inicialização
├── dados.h                     # Cabeçalho do dados.c
├── menu.c                      # Sistema de menus
├── menu.h                      # Cabeçalho do menu.c
├── caminhoes.c                 # CRUD de Caminhões (Estrutura 1)
├── caminhoes.h                 # Cabeçalho do caminhoes.c
├── docas.c                     # CRUD de Docas (Estrutura 2)
├── docas.h                     # Cabeçalho do docas.c
└── README.md                   # Documentação do projeto
```


***

## 🔧 Divisão Técnica Detalhada

### 1️⃣ **Giovani + Felipe** → CRUD Caminhões (Estrutura 1)

**Funções a implementar:**

```c
// CREATE
void cadastrarCaminhao(Caminhao caminhoes[], int *qtd);

// READ
void listarCaminhoes(Caminhao caminhoes[], int qtd);
Caminhao* buscarCaminhaoPorPlaca(Caminhao caminhoes[], int qtd, char *placa);

// UPDATE
void editarCaminhao(Caminhao caminhoes[], int qtd);

// DELETE
void deletarCaminhao(Caminhao caminhoes[], int *qtd);
```

**Validações obrigatórias:**

- Placa não pode repetir (identificador único)
- Capacidade de carga > 0
- Nome do motorista não pode estar vazio

***

### 2️⃣ **Lucas + Pedro** → CRUD Docas (Estrutura 2)

**Funções a implementar:**

```c
// CREATE
void cadastrarDoca(Doca docas[], int *qtd);

// READ
void listarDocas(Doca docas[], int qtd);
Doca* buscarDocaPorNumero(Doca docas[], int qtd, char *numero);

// UPDATE
void editarDoca(Doca docas[], int qtd);

// DELETE
void deletarDoca(Doca docas[], int *qtd);
```

**Validações obrigatórias:**

- Número da doca não pode repetir (identificador único)
- Tipo deve ser "carga" ou "descarga"
- Status deve ser "livre" ou "ocupada"
- Capacidade máxima > 0

***

### 3️⃣ **Vitor** → Sistema de Menus

**Estrutura do menu:**

```
========================================
  SISTEMA DE GESTÃO DE PÁTIO E DOCAS
========================================
1. Gerenciar Caminhões
2. Gerenciar Docas
3. Gerenciar Operações (ainda não implementado)
0. Sair
========================================
Escolha uma opção: _
```

**Submenus:**

- Submenu Caminhões: Cadastrar / Listar / Editar / Deletar
- Submenu Docas: Cadastrar / Listar / Editar / Deletar

***

### 4️⃣ **Vitor** → Inicialização de Dados

**Responsabilidade:**

- Criar vetores de 5 posições para cada estrutura
- Pré-preencher 2-3 registros de exemplo para facilitar testes

**Exemplo:**

```c
Caminhao caminhoes[5] = {
    {"ABC-1234", "Transportadora XYZ", "Carreta", "João Silva", 30000},
    {"DEF-5678", "Logística Total", "Truck", "Maria Santos", 15000},
    // Resto vazio
};
```


***

## ⚠️ Regras de Entrega

### ✅ O que INCLUIR no .zip

- Arquivo `.cbp` do CodeBlocks
- Todos os arquivos `.c` e `.h`
- Arquivo `README.md`
- Arquivos `.txt` ou `.bin` de dados pré-preenchidos (se houver)


### ❌ O que NÃO incluir

- Arquivos compilados (`.exe`, `.o`, `.obj`)
- Pastas `bin/` e `obj/` do CodeBlocks
- Arquivos de configuração pessoal (`.layout`, `.depend`)

***

## 📱 Comunicação da Equipe

**Grupo WhatsApp:**

- **Reuniões obrigatórias:** Domingo (25/01) e Sábado (01/02) às 20h **(Via Discord)**
- **Daily check-in:** Cada um posta no grupo às 21h o que fez no dia **Opicional**

**GitHub:**

- Todos devem fazer **commits diários** com mensagens descritivas em português
- Exemplo: `feat: adiciona função cadastrarCaminhao`

**Dúvidas técnicas:**

- Tirar no grupo IMEDIATAMENTE, não deixar acumular

***

## 🚨 Pontos Críticos de Atenção

1. **Não deixar para última hora** – A entrega é OBRIGATÓRIA, sem ela = conceito ZERO
2. **Testar no CodeBlocks** – Garantir que compila sem erros
3. **Nome do arquivo .zip** – Seguir EXATAMENTE o padrão (sem espaços/acentos)
4. **Validações** – Impedir entradas inválidas (placas repetidas, campos vazios)
5. **Comentários no código** – Facilita entendimento do professor

***

## ✅ Checklist Final (01/02)

Antes de compactar o arquivo, verificar:

- [ ] Projeto compila sem erros no CodeBlocks
- [ ] Todas as funções CRUD funcionam corretamente
- [ ] Menus navegam sem travar
- [ ] Validações impedem dados inválidos
- [ ] Código está comentado
- [ ] README.md está atualizado
- [ ] Nome da pasta segue o padrão (sem espaços/acentos)
- [ ] Arquivo .zip contém APENAS arquivos necessários
- [ ] Testado em pelo menos 2 máquinas diferentes

***

## 💡 Dicas Extras

- Use `fflush(stdin)` antes de `gets()` ou `fgets()` para evitar bugs de leitura
- Teste com placas duplicadas e valores negativos para garantir validações
- Committem no GitHub a cada função implementada
- Se travar em alguma parte, chama o grupo IMEDIATAMENTE

**Deadline crítico: 02/02/2026 às 23:59**
Sem essa entrega = conceito ZERO no trabalho final! 🚨

