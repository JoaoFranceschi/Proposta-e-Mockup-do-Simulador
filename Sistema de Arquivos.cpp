#include <iostream>     // Para entrada e saída padrão (cin e cout) 
#include <iomanip>      // Para utilizar formatação de saída(setw e left) 
#include <vector>       // Para usar vector (disco)
#include <map>          // Para usar map (tabela de diretório)
#include <string>       // Para manipular strings
#include <algorithm>    // std::max

using namespace std;    // Evita usar std:: antes de cout, cin, etc.

struct Arquivo {
    string nome;              // Nome do aquivo
    int tamanhoKB;            // tamanho real do arquivo
    vector<int> blocos;       // blocos ocupados
    int blocoIndice = -1;     // usado apenas em indexada
};

// Variáveis globais
vector<char> disco;             // Representa os blocos
map<string, Arquivo> diretorio; // Tabela de diretório
int tamanhoBlocoKB;             // Tamanho fixo de bloco em KB (Alteravél pelo usuário)
int metodo = 1;                 // 1 = contíguo, 2 = encadeado, 3 = indexado
string nomeMetodo[3] = {"Contiguo", "Encadeada", "Indexada"};

// Função que exibe o estado atual do disco na tela
void mostrarDisco() {
    int countBlocos = 0;       // contador de blocos usados
    cout << "\n=== Disco ===\n";
    for (char c : disco) {
        if(countBlocos == 8) { // Quebra de linha a cada 8 blocos
            cout << "\n";      
            countBlocos = 0;   
        }
        cout << "[" << (c == '-' ? ' ' : c) << "]";   // 
        countBlocos++;
    }
    cout << "\n";
}

// Função que exibe o diretório de arquivos, mostrando nome, tamanho e blocos ocupados
void mostrarDiretorio() {
    cout << "\nDiretorio:\n";
    if (metodo == 1) {  // Para alocação contígua
        // Definimos o cabeçalho da tabela
        cout << left << setw(10) << "Arquivo"
             << " | " << setw(8) << "Tamanho"
             << " | " << "Blocos\n" 
             << "------------------------------\n";            
        for (auto &p : diretorio) {
            // Percorre cada arquivo no diretório e imprime suas informações
            cout << left << setw(10) << p.second.nome
                 << " | " << setw(8) << (to_string(p.second.tamanhoKB) + "KB")
                 << " | ";
            for (int b : p.second.blocos) cout << b << " ";
            cout << "\n";
        }
    } else if (metodo == 2) { // Para alocação encadeada
        // Definimos o cabeçalho da tabela
        cout << left << setw(10) << "Arquivo"
             << " | " << setw(14) << "Tamanho"
             << " | " << setw(8) << "1o Bloco"
             << " | " << "Encadeamento\n"
             << "-----------------------------------------------------\n";
        for (auto &p : diretorio) {
            // Percorre cada arquivo no diretório e imprime suas informações
            cout << left << setw(10) << p.second.nome 
                 << " | " << setw(14) << (to_string(p.second.tamanhoKB) + "KB")
                 << " | ";
            if (!p.second.blocos.empty())
                cout << setw(8) << p.second.blocos.front() << " | ";
            for (int b : p.second.blocos) {
                // Imprime os blocos com setas entre eles
                cout << b;
                if (b != p.second.blocos.back()) cout << "->";
            }
            cout << "\n";
        }
    } else if (metodo == 3) { // Para alocação indexada
        // Definimos o cabeçalho da tabela
        cout << left << setw(10) << "Arquivo"
             << " | " << setw(14) << "Tamanho"
             << " | " << setw(12) << "Bloco indice"
             << " | " << "Bloco de dados\n"
             << "-----------------------------------------------------------\n";
        for (auto &p : diretorio) {
            // Percorre cada arquivo no diretório e imprime suas informações
            cout << left << setw(10) << p.second.nome 
                 << " | " << setw(14) << (to_string(p.second.tamanhoKB) + "KB")
                 << " | " << setw(12) << p.second.blocoIndice
                 << " | ";
            for (int b : p.second.blocos) cout << b << " "; // Imprime os blocos de dados
            cout << "\n";
        }
    }
}

// Calcula a fragmentação interna de um arquivo (espaço desperdiçado no último bloco)
// O que é? fragmentação interna é o espaço desperdiçado dentro do último bloco alocado de um arquivo,
// pois o arquivo pode não ocupar completamente o último bloco (devido ao tamanho fixo dos blocos).
int calcularFragInterna(const Arquivo &arq) {
    // Primeiramente calculamos a quantidade de blocos necessarios
    /*O -1 serve para fazer o arredondamento para cima. Ex: tamanhdoBloco = 4 e arq.tamanhoKB = 10
        - Sem o -1: (10 + 4) / 4 = 14 / 4 = 3 blocos (mas isso não é o cálculo correto para arredondar para cima)
        - Com o -1: (10 + 4 - 1) / 4 = (13) / 4 = 3 blocos (agora sim garante que qualquer resto na
        divisão resulta em um bloco extra, 3 blocos = 12KB, suficiente para 10KB) */
    int blocosNecessarios = (arq.tamanhoKB + tamanhoBlocoKB - 1) / tamanhoBlocoKB;
    // O desperdicio é calculado com os BlocosNecessario vezes o tamanho do bloco no disco menos o tamanho do arquivo.,
    int desperdicio = blocosNecessarios * tamanhoBlocoKB - arq.tamanhoKB;
    return desperdicio;
}

// Calcula a maior sequência de blocos livres contíguos (fragmentação externa)
// O que é? Fragmentação externa refere-se ao espaço total de armazenamento que está
// disponível, mas que não pode ser utilizado devido à falta de blocos contíguos.
int calcularFragExterna() {
    // Para calcular a fragmentação externa, precisamos encontrar a maior sequência de blocos livres contíguos no disco.
    // A função "max" retorna o maior valor entre dois valores. Utilizamos ela para atualizar o maior valor encontrado,
    // comparando o valor atual com o maior valor armazenado. Se encontra um bloco vazio ("-"), incrementa o contador "atual".
    // Se encontra um bloco ocupado, compara o valor atual com o maior valor armazenado("maiorSeq") e reseta o contador atual.
    int maiorSeq = 0, atual = 0;
    for (char c : disco) {
        if (c == '-') atual++;
        else {
            maiorSeq = max(maiorSeq, atual);
            atual = 0;
        }
    }
    // Ao final, precisamos fazer uma última verificação para garantir que a maior sequência seja atualizada caso o disco
    // termine com blocos livres.
    return max(maiorSeq, atual);
}

// Cria um novo arquivo no disco, de acordo com o método de alocação selecionado
void criarArquivo(string nome, int tamanhoKB) {
    if (diretorio.count(nome)) {
        cout << "Erro: Arquivo ja existe.\n"; 
        return;
    }
    int blocosNecessarios = (tamanhoKB + tamanhoBlocoKB - 1) / tamanhoBlocoKB;
    Arquivo novo{nome, tamanhoKB};

    if (metodo == 1) { // Contíguo
        int livre = 0, inicio = -1;
        for (int i = 0; i < disco.size(); i++) {
            if (disco[i] == '-') {
                if (inicio == -1) inicio = i;
                livre++;
                if (livre == blocosNecessarios) {
                    for (int j = inicio; j < inicio + blocosNecessarios; j++)
                        disco[j] = nome[0];
                    for (int j = inicio; j < inicio + blocosNecessarios; j++)
                        novo.blocos.push_back(j);
                    diretorio[nome] = novo;
                    cout << ">> Arquivo " << nome << " criado (contiguo).\n";
                    return;
                }
            } else {
                livre = 0; inicio = -1;
            }
        }
        cout << ">> Erro: Nao ha espaco contiguo suficiente.\n";
    } else if (metodo == 2) { // Encadeada
        // Primeiro, encontre todos os blocos livres necessários
        vector<int> livres;
        for (int i = 0; i < disco.size(); i++) {
            if (disco[i] == '-') livres.push_back(i);
            if (livres.size() == blocosNecessarios) break;
        }
        if (livres.size() == blocosNecessarios) {
            // Só agora marque como ocupado e registre no arquivo
            for (int idx : livres) {
                disco[idx] = nome[0];
                novo.blocos.push_back(idx);
            }
            diretorio[nome] = novo;
            cout << ">> Arquivo " << nome << " criado (encadeado).\n";
        } else {
            cout << ">> Erro: Espaco insuficiente.\n";
        }        
    } else if (metodo == 3) { // Indexada
        vector<int> posLivres;
        for (int i = 0; i < disco.size(); i++)
            if (disco[i] == '-') posLivres.push_back(i);

        if (posLivres.size() < blocosNecessarios + 1) {
            cout << ">> Erro: Espaco insuficiente.\n";
            return;
        }

        int blocoIndice = posLivres[0];
        disco[blocoIndice] = 'I';
        novo.blocoIndice = blocoIndice;

        for (int i = 1; i <= blocosNecessarios; i++) {
            disco[posLivres[i]] = nome[0];
            novo.blocos.push_back(posLivres[i]);
        }
        diretorio[nome] = novo;
        cout << ">> Arquivo " << nome << " criado (indexado).\n";
    }
}

// Estende um arquivo existente, alocando mais blocos se necessário
void estenderArquivo(string nome, int extraKB) {
    if (diretorio.count(nome) == 0) {
        cout << ">> Arquivo nao encontrado.\n";
        return;
    }
    Arquivo &arq = diretorio[nome];
    int novoTamanho = arq.tamanhoKB + extraKB;
    int blocosNecessarios = (novoTamanho + tamanhoBlocoKB - 1) / tamanhoBlocoKB;
    int blocosAtuais = arq.blocos.size();
    int blocosParaAdicionar = blocosNecessarios - blocosAtuais;
    if (blocosParaAdicionar <= 0) {
        arq.tamanhoKB = novoTamanho;
        cout << ">> Arquivo " << nome << " estendido (sem novos blocos).\n";
        return;
    }

    if (metodo == 1) { // Contíguo
        // Precisa realocar tudo!
        // Salva dados antigos
        vector<int> antigos = arq.blocos;
        for (int b : antigos) disco[b] = '-';
        // Tenta achar espaço contíguo maior
        int livre = 0, inicio = -1;
        for (int i = 0; i < disco.size(); i++) {
            if (disco[i] == '-') {
                if (inicio == -1) inicio = i;
                livre++;
                if (livre == blocosNecessarios) {
                    for (int j = inicio; j < inicio + blocosNecessarios; j++)
                        disco[j] = nome[0];
                    arq.blocos.clear();
                    for (int j = inicio; j < inicio + blocosNecessarios; j++)
                        arq.blocos.push_back(j);
                    arq.tamanhoKB = novoTamanho;
                    cout << ">> Arquivo " << nome << " estendido (contiguo).\n";
                    return;
                }
            } else {
                livre = 0; inicio = -1;
            }
        }
        // Se não conseguir, restaura os blocos antigos
        for (int b : antigos) disco[b] = nome[0];
        cout << ">> Erro: Nao ha espaco contiguo suficiente para estender.\n";
    } else if (metodo == 2) { // Encadeada
        int alocados = 0;
        for (int i = 0; i < disco.size() && alocados < blocosParaAdicionar; i++) {
            if (disco[i] == '-') {
                disco[i] = nome[0];
                arq.blocos.push_back(i);
                alocados++;
            }
        }
        if (alocados == blocosParaAdicionar) {
            arq.tamanhoKB = novoTamanho;
            cout << ">> Arquivo " << nome << " estendido (encadeado).\n";
        } else {
            // Se não conseguir, desfaz
            for (int i = 0; i < alocados; i++) {
                disco[arq.blocos.back()] = '-';
                arq.blocos.pop_back();
            }
            cout << ">> Erro: Espaco insuficiente para estender.\n";
        }
    } else if (metodo == 3) { // Indexada
        vector<int> posLivres;
        for (int i = 0; i < disco.size(); i++)
            if (disco[i] == '-') posLivres.push_back(i);
        // Remove blocoIndice from posLivres if present
        posLivres.erase(remove(posLivres.begin(), posLivres.end(), arq.blocoIndice), posLivres.end());
          
        if (posLivres.size() < blocosParaAdicionar) {
            cout << ">> Erro: Espaco insuficiente para estender.\n";
            return;
        }
        for (int i = 0; i < blocosParaAdicionar; i++) {
            disco[posLivres[i]] = nome[0];
            arq.blocos.push_back(posLivres[i]);
        }
        arq.tamanhoKB = novoTamanho;
        cout << ">> Arquivo " << nome << " estendido (indexado).\n";
    }
}

// Remove um arquivo do disco e libera seus blocos
void deletarArquivo(string nome) {
    if (diretorio.count(nome) == 0) {
        cout << ">> Arquivo nao encontrado.\n"; return;
    }
    Arquivo &arq = diretorio[nome]; // Use reference para evitar cópia desnecessária
    for (int b : arq.blocos) disco[b] = '-';
    if (arq.blocoIndice != -1) disco[arq.blocoIndice] = '-';
    diretorio.erase(nome);
    cout << ">> Arquivo " << nome << " deletado.\n";
}

// Simula a leitura de um arquivo, mostrando métricas de acesso e fragmentação
void lerArquivo(string nome) {
    if (diretorio.count(nome) == 0) {
        cout << ">> Arquivo nao encontrado.\n"; return;
    }
    Arquivo arq = diretorio[nome];
    cout << "===============================================================================\n";
    cout << ">> Operacao: Ler Arquivo " << nome << "\n";

    int passosAleatorio = 1;
    int blocoDesejado = 1;

    if (metodo == 1) { // Contíguo
        cout << "- Acesso sequencial: " << arq.blocos.size() << " passos\n";
        cout << "- Acesso aleatorio (qualquer bloco): 1 passo\n";
    } else if (metodo == 2) { // Encadeada
        // Pergunta ao usuário qual bloco deseja acessar (1 a N)
        if (!arq.blocos.empty()) {
            cout << "Qual bloco voce deseja simular o acesso aleatorio? (1 a " << arq.blocos.size() << "): ";
            cin >> blocoDesejado;
            cin.ignore(10000, '\n');
            if (blocoDesejado < 1 || blocoDesejado > arq.blocos.size()) {
                cout << "Bloco invalido. Usando o 1o bloco.\n";
                blocoDesejado = 1;
            }
        }
        passosAleatorio = blocoDesejado;
        cout << "- Acesso sequencial: " << arq.blocos.size() + (arq.blocos.size()-1) << " passos\n";
        cout << "- Acesso aleatorio (" << blocoDesejado << "o bloco): " << passosAleatorio << " passo(s)\n";
    } else if (metodo == 3) { // Indexada
        cout << "- Acesso sequencial: " << arq.blocos.size() + 1 << " passos\n";
        cout << "- Acesso aleatorio (qualquer bloco): 2 passos\n";
    }

    cout << "Metricas:\n";
    cout << "- Fragmentacao interna: " << calcularFragInterna(arq) << " KB\n";
    cout << "- Fragmentacao externa: " << calcularFragExterna() << " blocos livres contiguos\n";
    cout << "===============================================================================\n";
}

// Limpa o disco e o diretório, reiniciando o sistema de arquivos
void resetarDisco(int n) {
    disco.assign(n, '-');
    diretorio.clear();
    cout << ">> Disco resetado.\n";
}

// Função auxiliar para ler um inteiro válido
int lerInteiro(const string& mensagem, int min = INT_MIN, int max = INT_MAX) {
    int valor;
    while (true) {
        cout << mensagem;
        if (!(cin >> valor)) {
            cout << "Entrada invalida: LETRAS, numeros MENORES que ZERO, e numeros fora das opcoes nao sao aceitos.\nTente novamente...\n";
            cin.clear();
            cin.ignore(10000, '\n');
        } else if (valor < min || valor > max) {
            cout << "Valor fora do intervalo permitido.\nTente novamente...\n";
            cin.ignore(10000, '\n');
        } else {
            cin.ignore(10000, '\n'); // Limpa o buffer após leitura válida
            return valor;
        }
    }
}

// Função principal: gerencia o menu, entrada do usuário e fluxo do programa
int main(){
    int n;
    cout << "======================================\n";
    cout << "=== SIMULADOR SISTEMAS DE ARQUIVOS ===\n";
    cout << "======================================\n\n";
    n = lerInteiro("Digite o tamanho do disco (em blocos): ", 1); // Garante que o tamanho do bloco seja pelo menos 1KB
    tamanhoBlocoKB = lerInteiro("Digite o tamanho de cada bloco (em KB): ", 1); // Garante que o tamanho do bloco seja pelo menos 1KB
    resetarDisco(n);

    while (true) {
        cout << "\nSelecione o metodo de alocacao:\n";
        cout << "| 1. Contiguo" << endl;
        cout << "| 2. Encadeada" << endl;
        cout << "| 3. Indexada" << endl;
        cout << "| 4. Sair" << endl;

        metodo = lerInteiro("Escolha uma opcao: ", 1, 4);
        if (metodo == 4) break;

        resetarDisco(n); // Resetar disco ao trocar método

        int opcao;
        do {
            mostrarDisco();
            mostrarDiretorio();
            cout << "\n[Metodo " << nomeMetodo[metodo - 1] << "] Menu:\n";
            cout << "| 1. Criar Arquivo" << endl;
            cout << "| 2. Estender Arquivo" << endl;
            cout << "| 3. Deletar Arquivo" << endl;
            cout << "| 4. Ler Arquivo" << endl;
            cout << "| 5. Resetar Disco" << endl;
            cout << "| 6. Sair" << endl;
            
            opcao = lerInteiro("Escolha uma opcao: ", 1, 6);

            string nome;
            int tam, extra;
            switch (opcao) {
                case 1:
                    cout << "Nome do arquivo: "; getline(cin, nome);
                    tam = lerInteiro("Tamanho (KB): ", 1);
                    criarArquivo(nome, tam);
                    break;
                case 2:
                    cout << "Arquivo a estender(nome): "; getline(cin, nome);  
                    extra = lerInteiro("Tamanho extra (KB): ", 1);
                    estenderArquivo(nome, extra);
                    break;
                case 3:
                    cout << "Arquivo a deletar(nome): "; getline(cin, nome);
                    deletarArquivo(nome);
                    break;
                case 4:
                    cout << "Arquivo a ler: "; getline(cin, nome); 
                    lerArquivo(nome);
                    break;
                case 5:
                    resetarDisco(n);
                    break;
                case 6:
                    break;
                default:
                    cout << "Opcao invalida.\n";
            }
        } while (opcao != 6);
    }
    return 0;
}
