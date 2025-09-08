#include <iostream>
#include <iomanip>
#include <vector>
#include <map>
#include <string>
#include <algorithm>

using namespace std;

struct Arquivo {
    string nome;
    int tamanhoKB;            // tamanho real do arquivo
    vector<int> blocos;       // blocos ocupados
    int blocoIndice = -1;     // usado apenas em indexada
};

// Variáveis globais
vector<char> disco;             // representa os blocos
map<string, Arquivo> diretorio; // tabela de diretório
int tamanhoBlocoKB = 4;         // tamanho fixo de bloco
int metodo = 1;                 // 1 = contíguo, 2 = encadeado, 3 = indexado

// Função para exibir o disco
void mostrarDisco() {
    cout << "\nDisco: ";
    for (char c : disco) {
        cout << "[" << (c == '-' ? ' ' : c) << "]";
    }
    cout << "\n";
}

// Função para mostrar diretório
void mostrarDiretorio() {
    cout << "\nDiretorio:\n";
    if (metodo == 1) {
        cout << "Arquivo | Tamanho | Blocos\n";
        for (auto &p : diretorio) {
            cout << p.second.nome << "       | "
                 << p.second.tamanhoKB << "KB | ";
            for (int b : p.second.blocos) cout << b << " ";
            cout << "\n";
        }
    } else if (metodo == 2) {
        cout << "Arquivo | Bloco inicial | Encadeamento\n";
        for (auto &p : diretorio) {
            cout << p.second.nome << "       | "
                 << p.second.blocos.front() << "             | ";
            for (int b : p.second.blocos) {
                cout << b;
                if (b != p.second.blocos.back()) cout << "→";
            }
            cout << "\n";
        }
    } else if (metodo == 3) {
        cout << "Arquivo | Bloco indice | Blocos de dados\n";
        for (auto &p : diretorio) {
            cout << p.second.nome << "       | "
                 << p.second.blocoIndice << "            | ";
            for (int b : p.second.blocos) cout << b << " ";
            cout << "\n";
        }
    }
}

// Calcular fragmentação interna
int calcularFragInterna(const Arquivo &arq) {
    int blocosNecessarios = (arq.tamanhoKB + tamanhoBlocoKB - 1) / tamanhoBlocoKB;
    int desperdicio = blocosNecessarios * tamanhoBlocoKB - arq.tamanhoKB;
    return desperdicio;
}

// Calcular fragmentação externa (contígua)
int calcularFragExterna() {
    int maiorSeq = 0, atual = 0;
    for (char c : disco) {
        if (c == '-') atual++;
        else {
            maiorSeq = max(maiorSeq, atual);
            atual = 0;
        }
    }
    return max(maiorSeq, atual);
}

// Criar arquivo
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
                    cout << "Arquivo " << nome << " criado (contiguo).\n";
                    return;
                }
            } else {
                livre = 0; inicio = -1;
            }
        }
        cout << "Erro: Nao ha espaço contiguo suficiente.\n";

    } else if (metodo == 2) { // Encadeada
        int alocados = 0;
        for (int i = 0; i < disco.size() && alocados < blocosNecessarios; i++) {
            if (disco[i] == '-') {
                disco[i] = nome[0];
                novo.blocos.push_back(i);
                alocados++;
            }
        }
        if (alocados == blocosNecessarios) {
            diretorio[nome] = novo;
            cout << "Arquivo " << nome << " criado (encadeado).\n";
        } else cout << "Erro: Espaco insuficiente.\n";

    } else if (metodo == 3) { // Indexada
        vector<int> posLivres;
        for (int i = 0; i < disco.size(); i++)
            if (disco[i] == '-') posLivres.push_back(i);

        if (posLivres.size() < blocosNecessarios + 1) {
            cout << "Erro: Espaco insuficiente.\n";
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
        cout << "Arquivo " << nome << " criado (indexado).\n";
    }
}

// Estender arquivo
void estenderArquivo(string nome, int extraKB) {
    if (diretorio.count(nome) == 0) {
        cout << "Arquivo nao encontrado.\n";
        return;
    }
    Arquivo &arq = diretorio[nome];
    int novoTamanho = arq.tamanhoKB + extraKB;
    int blocosNecessarios = (novoTamanho + tamanhoBlocoKB - 1) / tamanhoBlocoKB;
    int blocosAtuais = arq.blocos.size();
    int blocosParaAdicionar = blocosNecessarios - blocosAtuais;
    if (blocosParaAdicionar <= 0) {
        arq.tamanhoKB = novoTamanho;
        cout << "Arquivo " << nome << " estendido (sem novos blocos).\n";
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
                    cout << "Arquivo " << nome << " estendido (contiguo).\n";
                    return;
                }
            } else {
                livre = 0; inicio = -1;
            }
        }
        // Se não conseguir, restaura os blocos antigos
        for (int b : antigos) disco[b] = nome[0];
        cout << "Erro: Nao ha espaço contiguo suficiente para estender.\n";
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
            cout << "Arquivo " << nome << " estendido (encadeado).\n";
        } else {
            // Se não conseguir, desfaz
            for (int i = 0; i < alocados; i++) {
                disco[arq.blocos.back()] = '-';
                arq.blocos.pop_back();
            }
            cout << "Erro: Espaco insuficiente para estender.\n";
        }
    } else if (metodo == 3) { // Indexada
        vector<int> posLivres;
        for (int i = 0; i < disco.size(); i++)
            if (disco[i] == '-') posLivres.push_back(i);

        if (posLivres.size() < blocosParaAdicionar) {
            cout << "Erro: Espaco insuficiente para estender.\n";
            return;
        }
        for (int i = 0; i < blocosParaAdicionar; i++) {
            disco[posLivres[i]] = nome[0];
            arq.blocos.push_back(posLivres[i]);
        }
        arq.tamanhoKB = novoTamanho;
        cout << "Arquivo " << nome << " estendido (indexado).\n";
    }
}

// Deletar arquivo
void deletarArquivo(string nome) {
    if (diretorio.count(nome) == 0) {
        cout << "Arquivo nao encontrado.\n"; return;
    }
    Arquivo arq = diretorio[nome];
    for (int b : arq.blocos) disco[b] = '-';
    if (arq.blocoIndice != -1) disco[arq.blocoIndice] = '-';
    diretorio.erase(nome);
    cout << "Arquivo " << nome << " deletado.\n";
}

// Ler arquivo
void lerArquivo(string nome) {
    if (diretorio.count(nome) == 0) {
        cout << "Arquivo nao encontrado.\n"; return;
    }
    Arquivo arq = diretorio[nome];
    cout << "Operacao: Ler Arquivo " << nome << "\n";

    if (metodo == 1) {
        cout << "- Acesso sequencial: " << arq.blocos.size() << " passos\n";
        cout << "- Acesso aleatorio (3º bloco): 1 passo\n";
    } else if (metodo == 2) {
        cout << "- Acesso sequencial: " << arq.blocos.size() + (arq.blocos.size()-1) << " passos\n";
        cout << "- Acesso aleatorio (3º bloco): " << min(3, (int)arq.blocos.size()) << " passos\n";
    } else if (metodo == 3) {
        cout << "- Acesso sequencial: " << arq.blocos.size() + 1 << " passos\n";
        cout << "- Acesso aleatorio (3º bloco): 2 passos\n";
    }

    cout << "Metricas:\n";
    cout << "- Fragmentacao interna: " << calcularFragInterna(arq) << " KB\n";
    cout << "- Fragmentacao externa: " << calcularFragExterna() << " blocos livres contiguos\n";
}

// Resetar disco
void resetarDisco(int n) {
    disco.assign(n, '-');
    diretorio.clear();
    cout << "Disco resetado.\n";
}

int main() {
    int n;
    cout << "================================\n";
    cout << "Simulador de Sistemas de Arquivos\n\n";
    cout << "Digite o tamanho do disco (em blocos): ";
    cin >> n;
    resetarDisco(n);

    while (true) {
        cout << "\nSeleção do metodo de alocacao:\n";
        cout << "1. Contiguo" << endl;
        cout << "2. Encadeada" << endl;
        cout << "3. Indexada" << endl;
        cout << "4. Sair" << endl;
        cin >> metodo;
        if (metodo == 4) break;

        resetarDisco(n); // Resetar disco ao trocar método

        int opcao;
        do {
            mostrarDisco();
            mostrarDiretorio();
            cout << "\n[Metodo " << metodo << "] Menu:\n";
            cout << "1. Criar Arquivo" << endl;
            cout << "2. Estender Arquivo" << endl;
            cout << "3. Deletar Arquivo" << endl;
            cout << "4. Ler Arquivo" << endl;
            cout << "5. Resetar Disco" << endl;
            cout << "6. Sair" << endl;
            cin >> opcao;

            if (opcao == 1) {
                string nome; int tam;
                cout << "Nome do arquivo: "; cin >> nome;
                cout << "Tamanho (KB): "; cin >> tam;
                criarArquivo(nome, tam);
            } else if (opcao == 2) {
                string nome; int extra;
                cout << "Arquivo a estender: "; cin >> nome;
                cout << "Tamanho extra (KB): "; cin >> extra;
                estenderArquivo(nome, extra);
            } else if (opcao == 3) {
                string nome;
                cout << "Arquivo a deletar: "; cin >> nome;
                deletarArquivo(nome);
            } else if (opcao == 4) {
                string nome;
                cout << "Arquivo a ler: "; cin >> nome;
                lerArquivo(nome);
            } else if (opcao == 5) {
                resetarDisco(n);
            }
        } while (opcao != 6);
    }
    return 0;
}
