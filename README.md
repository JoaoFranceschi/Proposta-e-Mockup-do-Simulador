# 💾 SISTEMAS DE ARQUIVOS

## Sumário
   - 👥 [Integrantes](https://github.com/JoaoFranceschi/Proposta-e-Mockup-do-Simulador/blob/main/README.md#-integrantes)
   - 🗯️ [Informações sobre o projeto](https://github.com/JoaoFranceschi/Proposta-e-Mockup-do-Simulador/blob/main/README.md#%EF%B8%8F-informa%C3%A7%C3%B5es-sobre-o-projeto)
   - ⚙️ [Descrição do Projeto](https://github.com/JoaoFranceschi/Proposta-e-Mockup-do-Simulador/blob/main/README.md#%EF%B8%8F-descri%C3%A7%C3%A3o-do-projeto)
   - 🧪 Instruções de compilação/execução → [Linux](https://github.com/JoaoFranceschi/Proposta-e-Mockup-do-Simulador/blob/main/README.md#-pr%C3%A9-requisitos---gnulinux) e/ou [Windows](https://github.com/JoaoFranceschi/Proposta-e-Mockup-do-Simulador/blob/main/README.md#-pr%C3%A9-requisitos---windows-11)
   -   Exemplo

---

## 👥 Integrantes
- João Paulo da Silva Franceschi (188358@upf.br)
- Octávio Francisco Petry Bortoluzzi (188380@upf.br)

---

## 🗯️ Informações sobre o projeto
- Linguagem: C++
- Interface: Terminal
- Tópico 3: Alocação em Sistemas de Arquivos

---

## ⚙️ Descrição do Projeto

   O projeto foi pensado para ajudar a compreender na prática o funcionamento de diferentes métodos de alocação em um sistema de arquivos. Para isso, impementamos um simulador em C++ que permite uma interação direta com um disco virtual, no que facilita a visualização de como os arquivos são armazenados, estendidos, lidos e removidos em diferentes métodos de alocação.
   
  A interface foi planejada para ser simples e intuitiva para qualquer pessoa, utilizamos menus interativos no terminal, de forma que até usuários sem experiência em programação, consiga explorar as funcionalidades do nosso sistema. Para a representação do disco utilizamos blocos(`[]`), sua quantidade e tamanho são totalmente customizaveis, tudo isso para melhorar mostrar de maneira clara a distribuição dos arquivos no disco e ver como cada método de alocação reage aos espaços do disco.
  
   Alem disso, o programa fornece métricas importantes — como a fragmentação interna e externa, utilização do disco e tempo de acesso(sequencial e aleatório) — premitindo o usuário avaliar o impacto de cada método em termos de desempenho e eficiência.

---

## 🧪 Instruções de compilação/execução.
## ✅ Pré-requisitos - GNU/Linux
- Compilador: `g++` com suporte a __C++17__ (ou superior)
Para instalar o g++, execute (caso ainda não tenha):
```bash
sudo apt update
sudo apt install g++
```

### 📂 1. Salvando o Código
Salve o código-fonte em um arquivo, por exemplo:
```bash
Sistema de Arquivos.cpp
```

### 🧱 2. Compilando o Código
No terminal, acesse a pasta onde está o arquivo e compile com:
```bash
g++ -o sistema "Sistema de Arquivos.cpp"
```
- `-o sistema` → define o nome do executável como `sistema`

### 🚀 3. Executando o Programa
- No terminal dentro da pasta que esta alocado o arquivo
```bash
./sistema
```

---

## ✅ Pré-requisitos - Windows 11
- Instalar extensões do C++ e Compile:

<img width="457" height="274" alt="image" src="https://github.com/user-attachments/assets/52cdddec-f260-4482-af0e-81a8c479dbb9" />

### Guia de Instalação TDM-GCC (Para o funcionamento do compilador) 
- Dentro da página do C/C++ Compile Run

<img width="1262" height="908" alt="image" src="https://github.com/user-attachments/assets/9ab853d6-e49b-4398-86a6-90bad3b2c56a" />

- Clique no link -> https://jmeubank.github.io/tdm-gcc/download/
   - Baixe o executável

<img width="1788" height="592" alt="image" src="https://github.com/user-attachments/assets/26b44b5b-9114-4b07-99ea-7b772dd90b7a" />

- Dentro do executável clique em CREATE e siga o passo a passo

<img width="634" height="497" alt="image" src="https://github.com/user-attachments/assets/0549c8b2-2b8d-45e1-89c8-e7ff1aadc073" />
<img width="478" height="376" alt="image" src="https://github.com/user-attachments/assets/42e3f389-051b-4f44-a359-cc36646c6568" />
<img width="488" height="375" alt="image" src="https://github.com/user-attachments/assets/d62525fd-5da6-44c4-8bb3-617602416e51" />


### 📂 1. Salvando o Código
Salve o código-fonte em um arquivo, por exemplo:
```bash
Sistema de Arquivos.cpp
```

### 🧱 2. Compilando o Código
Após a instalação do TDM-GCC, basta apenas que clique na execução do código dentro do VsCode

<img width="1826" height="787" alt="image" src="https://github.com/user-attachments/assets/89c90a77-43f4-427f-a1f4-05a738542960" />

### 🚀 3. Executando o Programa
Para executar o programa há dois métodos existentes
   - 1º Método: Executar pelo botao `Compile & Run`: Ele compilará e ira executar no terminal do próprio VsCode

<img width="1192" height="450" alt="image" src="https://github.com/user-attachments/assets/aad8ef1b-548e-47d8-b0e8-f9a7c4bc5ae3" />

   - 2º Método: Após compilar, ir na pasta que esta o arquivo do programa e ir em `output`
     <img width="600" height="250" alt="image" src="https://github.com/user-attachments/assets/e0c6f7d3-a78a-4052-bbc1-dfd1f1c0d5de" />
     
     - Após entrar na pasta, executar o executável com o nome do programa
     <img width="600" height="150" alt="image" src="https://github.com/user-attachments/assets/0ff250b8-3e9b-4c13-a818-05c3b1182d29" />
     
     - Agora o programa sera executado no terminal do windows 
     <img width="800" height="600" alt="image" src="https://github.com/user-attachments/assets/6c923c0a-d5e5-4d4a-bdb2-0c6693b7b3f4" />



