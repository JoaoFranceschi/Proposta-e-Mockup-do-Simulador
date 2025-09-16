# 💾 SISTEMAS DE ARQUIVOS

## Sumário
   - 🗯️ [Informações sobre o projeto](https://github.com/JoaoFranceschi/Proposta-e-Mockup-do-Simulador/blob/main/README.md#%EF%B8%8F-informa%C3%A7%C3%B5es-sobre-o-projeto)
   - 📒 [Descrição do Projeto](https://github.com/JoaoFranceschi/Proposta-e-Mockup-do-Simulador/blob/main/README.md#-descri%C3%A7%C3%A3o-do-projeto)
   - ⚖️ Instruções de compilação/execução → [Linux](https://github.com/JoaoFranceschi/Proposta-e-Mockup-do-Simulador/blob/main/README.md#-linux) e/ou [Windows](https://github.com/JoaoFranceschi/Proposta-e-Mockup-do-Simulador/blob/main/README.md#-windows)
   - ⚙️ [Exemplos de Execução](https://github.com/JoaoFranceschi/Proposta-e-Mockup-do-Simulador/blob/main/README.md#%EF%B8%8F-exemplos-de-execu%C3%A7%C3%A3o)

---

## 🗯️ Informações sobre o projeto
### 👥 Integrantes:
- João Paulo da Silva Franceschi (188358@upf.br)
- Octávio Francisco Petry Bortoluzzi (188380@upf.br)
### 🔭 Especificações 
- Ambiente: Visual Studio Code
- Linguagem: C++
- Interface: Terminal com menu interativo

---

## 📒 Descrição do Projeto
   O tópico escolhido foi o 3 — Alocação em Sistemas de Arquivos.
   
   O projeto foi pensado para ajudar a compreender na prática o funcionamento de diferentes métodos de alocação em um sistema de arquivos. Para isso, implementamos um simulador em C++ que permite uma interação direta com um disco virtual, que facilita a visualização de como os arquivos são armazenados, estendidos, lidos e removidos nos diferentes métodos de alocação.
   
   A interface foi planejada para ser simples e intuitiva, utilizamos menus interativos no terminal, de forma que até usuários sem experiência prévia em programação possam explorar as funcionalidades do nosso sistema. Elaboramos uma representação de disco em blocos(`[ ]`), incluimos a customização total da sua quantidade(em blocos) e o tamanho de cada bloco(em KB),  permitindo observar de maneira clara a distribuição dos arquivos no disco e ver como cada estratégia de alocação reage aos espaços disponíveis do disco.
   
   Alem disso, o programa fornece métricas importantes — como a fragmentação interna e externa, utilização do disco e tempo de acesso(sequencial e aleatório) — permitindo o usuário avaliar o impacto de cada método em termos de desempenho e eficiência.

---
## ⚖️ Instruções de compilação/execução(Linux e Windows)
### 🐧 Linux
- Pré-requisito: Ter sistema GNU/Linux
- Extensões VSCode: C/C++ Extension Pack by Microsoft
- Compilador: `g++` com suporte a __C++17__ (ou superior)
Para instalar o g++, execute (caso ainda não tenha):
```bash
sudo apt update
sudo apt install g++
```

#### 📂 1. Salvando o Código
Salve o código-fonte em um arquivo, por exemplo:
```bash
Sistema de Arquivos.cpp
```

#### 🧱 2. Compilando o Código
No terminal, acesse a pasta onde está o arquivo e compile com:
```bash
g++ -o sistema "Sistema de Arquivos.cpp"
```
- `-o sistema` → define o nome do executável como `sistema`

#### 🚀 3. Executando o Programa
- No terminal dentro da pasta que está alocado o arquivo
```bash
./sistema
```

---

### 🪟 Windows
- Pré-requisito: Ter sistema Windows
- - Extensões VSCode: C/C++ Extension Pack by Microsoft e C/C++ Compile Run
<img width="457" height="274" alt="image" src="https://github.com/user-attachments/assets/52cdddec-f260-4482-af0e-81a8c479dbb9" />

#### 🪄 Guia de Instalação do compilador TDM-GCC
- Clique no link -> https://jmeubank.github.io/tdm-gcc/download/
   - Baixe o executável sublinhado em vermelho
<img width="1788" height="592" alt="image" src="https://github.com/user-attachments/assets/26b44b5b-9114-4b07-99ea-7b772dd90b7a" />

- Dentro do executável clique em CREATE e siga o passo a passo
<img width="450" height="400" alt="image" src="https://github.com/user-attachments/assets/02d3854c-a079-4f69-ae8b-8a700e327154" />
<img width="450" height="400" alt="image" src="https://github.com/user-attachments/assets/569a7627-2b60-41cf-bf9c-802e7bf9d7ac" />
<img width="450" height="400" alt="image" src="https://github.com/user-attachments/assets/7f97e40e-5534-44af-ac1f-ba335175d387" />

#### 📂 1. Salvando o Código
Salve o código-fonte em um arquivo, por exemplo:
```bash
Sistema de Arquivos.cpp
```

#### 🧱 2. Compilando o Código
Após a instalação do TDM-GCC, basta apenas que clique na execução do código dentro do VsCode

<img width="600" height="370" alt="image" src="https://github.com/user-attachments/assets/89c90a77-43f4-427f-a1f4-05a738542960" />

#### 🚀 3. Executando o Programa
Para executar o programa há dois métodos existentes
   - 1º Método: Executar pelo botao `Compile & Run`: Ele compilará e ira executar no terminal do próprio VsCode

<img width="600" height="370" alt="image" src="https://github.com/user-attachments/assets/aad8ef1b-548e-47d8-b0e8-f9a7c4bc5ae3" />

   - 2º Método: Após compilar, ir na pasta que esta o arquivo do programa e ir em `output`
     <img width="600" height="250" alt="image" src="https://github.com/user-attachments/assets/e0c6f7d3-a78a-4052-bbc1-dfd1f1c0d5de" />
     
     - Após entrar na pasta, executar o executável com o nome do programa
     <img width="600" height="250" alt="image" src="https://github.com/user-attachments/assets/0ff250b8-3e9b-4c13-a818-05c3b1182d29" />
     
     - Agora o programa sera executado no terminal do windows 
     <img width="800" height="600" alt="image" src="https://github.com/user-attachments/assets/6c923c0a-d5e5-4d4a-bdb2-0c6693b7b3f4" />

---

## ⚙️ Exemplos de Execução

### Start
```bash
=====================================================
=== SIMULADOR DE ALOCACAO EM SISTEMAS DE ARQUIVOS ===
=====================================================

Digite o tamanho do disco (em blocos): 16
Digite o tamanho de cada bloco (em KB): 4
>> Disco resetado.

Selecione o metodo de alocacao:
| 1. Contiguo
| 2. Encadeado
| 3. Indexado
| 4. Sair
Escolha uma opcao: 
```

### Contiguo
```bash
===============================================================================
>> Operacao: Ler Arquivo GG
- Acesso sequencial: 1 passos
- Acesso aleatorio (qualquer bloco): 1 passo
Metricas:
- Fragmentacao interna: 3 KB
- Fragmentacao externa: 0 blocos livres contiguos
===============================================================================

=== Disco ===
[Z][B][B][B][B][B][B][G]

Diretorio:
Arquivo    | Tamanho  | Blocos
------------------------------
Bortoluzzi | 21KB     | 1 2 3 4 5 6
GG         | 1KB      | 7
Ze         | 2KB      | 0

[Metodo Contiguo] Menu:
| 1. Criar Arquivo
| 2. Estender Arquivo
| 3. Deletar Arquivo
| 4. Ler Arquivo
| 5. Resetar Disco
| 6. Sair
Escolha uma opcao:
```

### Encadeado
```bash
===============================================================================
>> Operacao: Ler Arquivo A
Qual bloco voce deseja simular o acesso aleatorio? (1 a 6): 5
- Acesso sequencial: 11 passos
- Acesso aleatorio (5o bloco): 5 passo(s)
Metricas:
- Fragmentacao interna: 3 KB
- Fragmentacao externa: 2 blocos livres contiguos
===============================================================================

=== Disco ===
[A][A][A][A][C][C][C][C]
[C][ ][ ][A][A][D][D][D]

Diretorio:
Arquivo    | Tamanho        | 1o Bloco | Encadeamento
-----------------------------------------------------
A          | 21KB           | 0        | 0->1->2->3->11->12
C          | 17KB           | 4        | 4->5->6->7->8
D          | 12KB           | 13       | 13->14->15

[Metodo Encadeado] Menu:
| 1. Criar Arquivo
| 2. Estender Arquivo
| 3. Deletar Arquivo
| 4. Ler Arquivo
| 5. Resetar Disco
| 6. Sair
Escolha uma opcao:
```

### Indexado
```bash
===============================================================================
>> Operacao: Ler Arquivo D
- Acesso sequencial: 7 passos
- Acesso aleatorio (qualquer bloco): 2 passos
Metricas:
- Fragmentacao interna: 0 KB
- Fragmentacao externa: 5 blocos livres contiguos
===============================================================================

=== Disco ===
[I][A][A][A][I][D][A][A]
[A][A][A][A][D][D][D][I]
[C][C][C][C][C][C][C][C]
[C][D][D][ ][ ][ ][ ][ ]

Diretorio:
Arquivo    | Tamanho        | Bloco indice | Bloco de dados
-----------------------------------------------------------
A          | 36KB           | 0            | 1 2 3 6 7 8 9 10 11
C          | 34KB           | 15           | 16 17 18 19 20 21 22 23 24
D          | 24KB           | 4            | 5 12 13 14 25 26

[Metodo Indexado] Menu:
| 1. Criar Arquivo
| 2. Estender Arquivo
| 3. Deletar Arquivo
| 4. Ler Arquivo
| 5. Resetar Disco
| 6. Sair
Escolha uma opcao:
```

