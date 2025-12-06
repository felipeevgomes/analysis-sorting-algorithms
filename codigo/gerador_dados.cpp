#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <ctime>

using namespace std;

const int PEQUENO = 1000;
const int MEDIO = 10000;
const int GRANDE = 100000;

void gerarAleatorio(vector<int>& vetor, int tamanho){
  for (int i = 0; i < tamanho; i++)
  {
    vetor[i] = rand() %100000;
  }
}

void gerarCrescente(vector<int>& vetor, int tamanho){
  for (int i = 0; i < tamanho; i++)
  {
    vetor[i] = i;
  }
}

void gerarDescrescente(vector<int>& vetor, int tamanho){
  for (int i = 0; i < tamanho; i++)
  {
    vetor[i] = tamanho - i;
  }
}

void salvarArquivo(const string& nomeArquivo, const vector<int>& vetor, int tamanho){
    ofstream arquivo(nomeArquivo, ios::binary);
    if(!arquivo){
      cerr << "Erro ao criar o arquivo " << nomeArquivo << endl;
      return;
    }
    arquivo.write(reinterpret_cast<const char*> (vetor.data()), tamanho * sizeof(int) );
    arquivo.close();
    cout <<"Arquivo " << nomeArquivo <<"criado com sucesso!! ("<< tamanho<< " elementos)" << endl;
}

int main(){
  srand(static_cast<unsigned>(time(0)));

  vector<int> tamanhos = {PEQUENO, MEDIO, GRANDE};
  vector<string> nomeTamanhos = {"pequeno", "medio", "grande"};
  vector<string> cenarios = {"aleatorios", "crescente", "descresente"};

  for(size_t t = 0; t<tamanhos.size(); t++){
    int tamanho = tamanhos[t];
    vector<int> vetor(tamanho);
    for (size_t c = 0; c < cenarios.size(); c++){
      string nameArquivo = "../dados/" + nomeTamanhos[t] + "-" + cenarios[c] + ".bin";
      if(c==0){
        gerarAleatorio(vetor,tamanho);
      }else if(c==1){
        gerarCrescente(vetor,tamanho);
      } else{
        gerarDescrescente(vetor,tamanho);
      }
      salvarArquivo(nameArquivo, vetor, tamanho);
    }
  }

  cout<<"Total: 9 arquivos gereados na pasta 'dados/'" << endl;
  return 0;
}