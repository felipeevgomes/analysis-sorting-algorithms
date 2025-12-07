#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <chrono>
#include <iomanip>
#include <algorithm>

using namespace std;
using namespace chrono;

struct MetricasBusca {
    long long comparacoes;
    double tempo_ms;
    bool encontrado;
    
    MetricasBusca() : comparacoes(0), tempo_ms(0.0), encontrado(false) {}
};

vector<int> carregarArquivo(const string& nomeArquivo, int& tamanho) {
    ifstream arquivo(nomeArquivo, ios::binary);
    
    if (!arquivo) {
        cerr << "Erro ao abrir arquivo " << nomeArquivo << endl;
        return vector<int>();
    }
    
    arquivo.read(reinterpret_cast<char*>(&tamanho), sizeof(int));
    vector<int> vetor(tamanho);
    arquivo.read(reinterpret_cast<char*>(vetor.data()), tamanho * sizeof(int));
    
    arquivo.close();
    return vetor;
}

MetricasBusca buscaSequencial(const vector<int>& vetor, int valor) {
    MetricasBusca m;
    auto inicio = high_resolution_clock::now();
    
    for (size_t i = 0; i < vetor.size(); i++) {
        m.comparacoes++;
        if (vetor[i] == valor) {
            m.encontrado = true;
            break;
        }
    }
    
    auto fim = high_resolution_clock::now();
    m.tempo_ms = duration_cast<microseconds>(fim - inicio).count() / 1000.0;
    return m;
}

MetricasBusca buscaBinaria(const vector<int>& vetor, int valor) {
    MetricasBusca m;
    auto inicio = high_resolution_clock::now();
    
    int esquerda = 0;
    int direita = vetor.size() - 1;
    
    while (esquerda <= direita) {
        int meio = esquerda + (direita - esquerda) / 2;
        m.comparacoes++;
        
        if (vetor[meio] == valor) {
            m.encontrado = true;
            break;
        }
        
        m.comparacoes++;
        if (vetor[meio] < valor) {
            esquerda = meio + 1;
        } else {
            direita = meio - 1;
        }
    }
    
    auto fim = high_resolution_clock::now();
    m.tempo_ms = duration_cast<microseconds>(fim - inicio).count() / 1000.0;
    return m;
}

int main() {
    int tamanho;
    vector<int> vetorOriginal = carregarArquivo("../dados/grande-aleatorios.bin", tamanho);
    
    if (vetorOriginal.empty()) {
        cerr << "Erro ao carregar arquivo!" << endl;
        return 1;
    }
    
    cout << "Arquivo: grande-aleatorio.bin (" << tamanho << " elementos)" << endl << endl;
    int valorExistente = vetorOriginal[tamanho / 2]; 
    int valorInexistente = 9999999; 
    
    ofstream resultado("resultados_busca.csv");
    resultado << "TipoBusca,TipoValor,Tempo_ms,Comparacoes,Encontrado,TempoOrdenacao_ms" << endl;
    
    cout << "--- BUSCA SEQUENCIAL ---" << endl;
    MetricasBusca m = buscaSequencial(vetorOriginal, valorExistente);
    cout << "Valor EXISTENTE (" << valorExistente << "):" << endl;
    cout << "  Tempo: " << fixed << setprecision(4) << m.tempo_ms << " ms" << endl;
    cout << "  Comparacoes: " << m.comparacoes << endl;
    cout << "  Encontrado: " << (m.encontrado ? "SIM" : "NAO") << endl << endl;
    resultado << "Sequencial,Existente," << fixed << setprecision(4) << m.tempo_ms << "," 
              << m.comparacoes << "," << (m.encontrado ? 1 : 0) << ",0" << endl;
    
    m = buscaSequencial(vetorOriginal, valorInexistente);
    cout << "Valor INEXISTENTE (" << valorInexistente << "):" << endl;
    cout << "  Tempo: " << fixed << setprecision(4) << m.tempo_ms << " ms" << endl;
    cout << "  Comparacoes: " << m.comparacoes << endl;
    cout << "  Encontrado: " << (m.encontrado ? "SIM" : "NAO") << endl << endl;
    resultado << "Sequencial,Inexistente," << fixed << setprecision(4) << m.tempo_ms << "," 
              << m.comparacoes << "," << (m.encontrado ? 1 : 0) << ",0" << endl;
    
    cout << "--- BUSCA BINARIA (com custo de ordenacao) ---" << endl;
    vector<int> vetorOrdenado = vetorOriginal;
    
    auto inicioOrd = high_resolution_clock::now();
    sort(vetorOrdenado.begin(), vetorOrdenado.end());
    auto fimOrd = high_resolution_clock::now();
    double tempoOrdenacao = duration_cast<microseconds>(fimOrd - inicioOrd).count() / 1000.0;
    
    cout << "Tempo de ordenacao: " << fixed << setprecision(2) << tempoOrdenacao << " ms" << endl << endl;

    m = buscaBinaria(vetorOrdenado, valorExistente);
    cout << "Valor EXISTENTE (" << valorExistente << "):" << endl;
    cout << "  Tempo: " << fixed << setprecision(4) << m.tempo_ms << " ms" << endl;
    cout << "  Comparacoes: " << m.comparacoes << endl;
    cout << "  Encontrado: " << (m.encontrado ? "SIM" : "NAO") << endl;
    cout << "  Tempo TOTAL (ord + busca): " << fixed << setprecision(2) 
         << (tempoOrdenacao + m.tempo_ms) << " ms" << endl << endl;
    resultado << "Binaria,Existente," << fixed << setprecision(4) << m.tempo_ms << "," 
              << m.comparacoes << "," << (m.encontrado ? 1 : 0) << "," 
              << fixed << setprecision(2) << tempoOrdenacao << endl;
    
    m = buscaBinaria(vetorOrdenado, valorInexistente);
    cout << "Valor INEXISTENTE (" << valorInexistente << "):" << endl;
    cout << "  Tempo: " << fixed << setprecision(4) << m.tempo_ms << " ms" << endl;
    cout << "  Comparacoes: " << m.comparacoes << endl;
    cout << "  Encontrado: " << (m.encontrado ? "SIM" : "NAO") << endl;
    cout << "  Tempo TOTAL (ord + busca): " << fixed << setprecision(2) 
         << (tempoOrdenacao + m.tempo_ms) << " ms" << endl << endl;
    resultado << "Binaria,Inexistente," << fixed << setprecision(4) << m.tempo_ms << "," 
              << m.comparacoes << "," << (m.encontrado ? 1 : 0) << "," 
              << fixed << setprecision(2) << tempoOrdenacao << endl;
    
    cout << endl << "=== ANALISE COMPARATIVA ===" << endl;
    cout << "A busca binaria eh mais rapida para buscar, mas..." << endl;
    cout << "Considerando o custo de ordenacao:" << endl;
    cout << "  - Sequencial eh melhor para poucas buscas" << endl;
    cout << "  - Binaria compensa quando ha muitas buscas no mesmo vetor" << endl;
    
    resultado.close();
    
    cout << "Resultados salvos em: resultados_busca.csv" << endl;
    
    return 0;
}