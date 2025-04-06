// graph.cpp
#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <fstream>
#include <sstream>

class Graph {
private:
    int numVertices;
    std::vector<std::vector<int>> M;
    std::vector<std::vector<int>> L;

    
    public:
    Graph(int n) : numVertices(n), M(n, std::vector<int>(n, 0)), L(n) {}
    
    void loadFrom(const std::string& filename) {
        std::ifstream infile(filename);
        std::string line;
        int lineNum = 0;
        while (getline(infile, line)) {
            std::istringstream iss(line);
            if (lineNum == 0) {
                lineNum++;
                continue;
            }
            int valor, col = 0;
            while (iss >> valor) {
                M[lineNum - 1][col] = valor;
                if (valor != 0) {
                    L[lineNum - 1].push_back(col);
                }
                col++;
            }
            lineNum++;
        }
    }
    
    void imprimirMatrizAdjacencia() const {
        std::cout << "Matriz de Adjacência:\n";
        for (int i = 0; i < numVertices; ++i) {
            for (int j = 0; j < numVertices; ++j) {
                std::cout << M[i][j] << "\t";
            }
            std::cout << "\n";
        }
    }
    
    void imprimirListaAdjacencia() const {
        std::cout << "Lista de Adjacência:\n";
        for (int i = 0; i < numVertices; ++i) {
            std::cout << "[" << i << "] -> ";
            for (int viz : L[i]) {
                std::cout << viz << " ";
            }
            std::cout << "\n";
        }
    }
    
    void dfs(int inicio, std::vector<bool>& visitados, std::vector<int>& pred) const {
        std::stack<int> pilha;
        pilha.push(inicio);
        visitados[inicio] = true;

        while (!pilha.empty()) {
            int v = pilha.top();
            pilha.pop();
            std::cout << "Visitando: " << v << "\n";
            for (int u : L[v]) {
                if (!visitados[u]) {
                    pilha.push(u);
                    visitados[u] = true;
                    pred[u] = v;
                }
            }
        }
    }
    void dfs_all() const {
        std::vector<bool> visitados(numVertices, false);
        std::vector<int> pred(numVertices, -1);

        for (int i = 0; i < numVertices; ++i) {
            if (!visitados[i]) {
                dfs(i, visitados, pred);
            }
        }

        std::cout << "Predecessores:\n";
        for (int i = 0; i < numVertices; ++i) {
            std::cout << "pred[" << i << "] = " << pred[i] << "\n";
        }
    }

    std::vector<int> bfs(int inicio) const {
        std::vector<bool> visitados(numVertices, false);
        std::vector<int> pred(numVertices, -1);

        std::queue<int> fila;
        fila.push(inicio);
        visitados[inicio] = true;

        while (!fila.empty()) {
            int v = fila.front();
            fila.pop();
            std::cout << "Visitando: " << v << "\n";

            for (int u : L[v]) {
                if (!visitados[u]) {
                    fila.push(u);
                    visitados[u] = true;
                    pred[u] = v;
                }
            }
        }
        return pred;
    }

    void imprimirCaminho(int s, int t) const {
        std::vector<int> pred = bfs(s);
        if (pred[t] == -1 && s != t) {
            std::cout << "Não há caminho entre " << s << " e " << t << "\n";
            return;
        }

        std::stack<int> caminho;
        for (int v = t; v != -1; v = pred[v]) {
            caminho.push(v);
            if (v == s) break;
        }

        std::cout << "Caminho: ";
        while (!caminho.empty()) {
            std::cout << caminho.top();
            caminho.pop();
            if (!caminho.empty()) std::cout << " -> ";
        }
        std::cout << "\n";
    }
};

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cout << "Uso: ./grafo <arquivo.txt>\n";
        return 1;
    }

    std::ifstream infile(argv[1]);
    if (!infile) {
        std::cerr << "Erro ao abrir o arquivo!\n";
        return 1;
    }

    int n;
    infile >> n;
    infile.close();

    Graph g(n);
    g.loadFrom(argv[1]);

    int opcao;
    do {
        std::cout << "\n1 - Imprimir Lista de Adjacência\n";
        std::cout << "2 - Imprimir Matriz de Adjacência\n";
        std::cout << "3 - Testar DFS\n";
        std::cout << "4 - Imprimir Caminho\n";
        std::cout << "5 - Sair\n";
        std::cout << "Input: ";
        std::cin >> opcao;

        if (opcao == 1) g.imprimirListaAdjacencia();
        else if (opcao == 2) g.imprimirMatrizAdjacencia();
        else if (opcao == 3) g.dfs_all();
        else if (opcao == 4) {
            int s, t;
            std::cout << "Digite o vértice inicial: ";
            std::cin >> s;
            std::cout << "Digite o vértice final: ";
            std::cin >> t;
            g.imprimirCaminho(s, t);
        }
    } while (opcao != 5);

    return 0;
}
