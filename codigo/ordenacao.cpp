#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <chrono>
#include <iomanip>

using namespace std;
using namespace chrono;

struct Metricas {
    long long comparacoes;
    long long trocas;
    double tempo_ms;
    
    Metricas() : comparacoes(0), trocas(0), tempo_ms(0.0) {}
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

Metricas selectionSort(vector<int>& vetor) {
    Metricas m;
    auto inicio = high_resolution_clock::now();
    
    int n = vetor.size();
    for (int i = 0; i < n - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < n; j++) {
            m.comparacoes++;
            if (vetor[j] < vetor[min_idx]) {
                min_idx = j;
            }
        }
        if (min_idx != i) {
            swap(vetor[i], vetor[min_idx]);
            m.trocas++;
        }
    }
    
    auto fim = high_resolution_clock::now();
    m.tempo_ms = duration_cast<microseconds>(fim - inicio).count() / 1000.0;
    return m;
}

Metricas insertionSort(vector<int>& vetor) {
    Metricas m;
    auto inicio = high_resolution_clock::now();
    
    int n = vetor.size();
    for (int i = 1; i < n; i++) {
        int chave = vetor[i];
        int j = i - 1;
        
        while (j >= 0) {
            m.comparacoes++;
            if (vetor[j] > chave) {
                vetor[j + 1] = vetor[j];
                m.trocas++;
                j--;
            } else {
                break;
            }
        }
        vetor[j + 1] = chave;
    }
    
    auto fim = high_resolution_clock::now();
    m.tempo_ms = duration_cast<microseconds>(fim - inicio).count() / 1000.0;
    return m;
}

Metricas bubbleSort(vector<int>& vetor) {
    Metricas m;
    auto inicio = high_resolution_clock::now();
    
    int n = vetor.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            m.comparacoes++;
            if (vetor[j] > vetor[j + 1]) {
                swap(vetor[j], vetor[j + 1]);
                m.trocas++;
            }
        }
    }
    
    auto fim = high_resolution_clock::now();
    m.tempo_ms = duration_cast<microseconds>(fim - inicio).count() / 1000.0;
    return m;
}

Metricas bubbleSortOtimizado(vector<int>& vetor) {
    Metricas m;
    auto inicio = high_resolution_clock::now();
    
    int n = vetor.size();
    bool trocou;
    for (int i = 0; i < n - 1; i++) {
        trocou = false;
        for (int j = 0; j < n - i - 1; j++) {
            m.comparacoes++;
            if (vetor[j] > vetor[j + 1]) {
                swap(vetor[j], vetor[j + 1]);
                m.trocas++;
                trocou = true;
            }
        }
        if (!trocou) break; 
    }
    
    auto fim = high_resolution_clock::now();
    m.tempo_ms = duration_cast<microseconds>(fim - inicio).count() / 1000.0;
    return m;
}


void imprimirMetricas(const string& algoritmo, const string& arquivo, const Metricas& m) {
  cout << left << setw(25) << algoritmo << " | " 
      << setw(25) << arquivo << " | "
      << setw(12) << fixed << setprecision(2) << m.tempo_ms << " ms | "
      << setw(15) << m.comparacoes << " | "
      << setw(15) << m.trocas << endl;
}

int main() {
    vector<string> arquivos = {
        "../dados/pequeno_aleatorio.bin",
        "../dados/pequeno_crescente.bin",
        "../dados/pequeno_decrescente.bin",
        "../dados/medio_aleatorio.bin",
        "../dados/medio_crescente.bin",
        "../dados/medio_decrescente.bin",
        "../dados/grande_aleatorio.bin",
        "../dados/grande_crescente.bin",
        "../dados/grande_decrescente.bin"
    };

    ofstream resultado("resultados_ordenacao.csv");
    resultado << "Algoritmo,Arquivo,Tempo_ms,Comparacoes,Trocas" << endl;
    
    cout << "=== ANÁLISE DE ALGORITMOS DE ORDENAÇÃO ===" << endl << endl;
    cout << left << setw(25) << "ALGORITMO" << " | " 
         << setw(25) << "ARQUIVO" << " | "
         << setw(12) << "TEMPO (ms)" << " | "
         << setw(15) << "COMPARAÇÕES" << " | "
         << setw(15) << "TROCAS" << endl;
    cout << string(100, '-') << endl;
    
    for (const string& arquivoPath : arquivos) {
        int tamanho;
        vector<int> vetorOriginal = carregarArquivo(arquivoPath, tamanho);
        
        if (vetorOriginal.empty()) {
            cout << "Pulando arquivo " << arquivoPath << endl;
            continue;
        }
        
        // Extrair nome do arquivo sem path
        size_t pos = arquivoPath.find_last_of('/');
        string nomeArquivo = (pos != string::npos) ? arquivoPath.substr(pos + 1) : arquivoPath;
        
        // Selection Sort
        vector<int> vetor = vetorOriginal;
        Metricas m = selectionSort(vetor);
        imprimirMetricas("Selection Sort", nomeArquivo, m);
        resultado << "Selection Sort," << nomeArquivo << "," 
                  << fixed << setprecision(2) << m.tempo_ms << "," 
                  << m.comparacoes << "," << m.trocas << endl;
        
        // Insertion Sort
        vetor = vetorOriginal;
        m = insertionSort(vetor);
        imprimirMetricas("Insertion Sort", nomeArquivo, m);
        resultado << "Insertion Sort," << nomeArquivo << "," 
                  << fixed << setprecision(2) << m.tempo_ms << "," 
                  << m.comparacoes << "," << m.trocas << endl;
        
        // Bubble Sort
        vetor = vetorOriginal;
        m = bubbleSort(vetor);
        imprimirMetricas("Bubble Sort", nomeArquivo, m);
        resultado << "Bubble Sort," << nomeArquivo << "," 
                  << fixed << setprecision(2) << m.tempo_ms << "," 
                  << m.comparacoes << "," << m.trocas << endl;
        
        // Bubble Sort Otimizado
        vetor = vetorOriginal;
        m = bubbleSortOtimizado(vetor);
        imprimirMetricas("Bubble Sort Otimizado", nomeArquivo, m);
        resultado << "Bubble Sort Otimizado," << nomeArquivo << "," 
                  << fixed << setprecision(2) << m.tempo_ms << "," 
                  << m.comparacoes << "," << m.trocas << endl;
        
        cout << endl;
    }
    
    resultado.close();
    cout << "=== ANÁLISE CONCLUÍDA! ===" << endl;
    cout << "Resultados salvos em: resultados_ordenacao.csv" << endl;
    
    return 0;
}