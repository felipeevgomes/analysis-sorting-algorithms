# 📊 Análise Experimental de Algoritmos de Ordenação e Busca

Trabalho prático da disciplina de **Algoritmos e Estruturas de Dados** que implementa e analisa empiricamente o desempenho de algoritmos de ordenação O(n²) e algoritmos de busca.

## 🎯 Objetivos

- Implementar algoritmos clássicos de ordenação e busca
- Comparar complexidade teórica vs desempenho real
- Analisar impacto de diferentes cenários (aleatório, crescente, decrescente)
- Medir tempo, comparações e trocas

## 🔧 Algoritmos Implementados

### Ordenação
- Selection Sort
- Insertion Sort
- Bubble Sort (Padrão)
- Bubble Sort Otimizado

### Busca
- Busca Sequencial
- Busca Binária

## 📂 Estrutura do Projeto
```
├── codigo/
│   ├── gerador_dados.cpp    # Gera arquivos de teste
│   ├── ordenacao.cpp         # Análise de ordenação
│   ├── busca.cpp             # Análise de busca
│   └── Makefile
├── dados/                    # Arquivos binários (gerados)
├── graficos/                 # Gráficos da análise
└── relatorio.pdf            # Relatório completo
```

## 🚀 Como Executar

### Pré-requisitos
- g++ com suporte a C++11
- Python 3.x (para gráficos)
- pandas, matplotlib, seaborn

### Compilar e Executar
```bash
# Clonar o repositório
git clone https://github.com/SEU_USUARIO/analise-algoritmos-ordenacao.git
cd analise-algoritmos-ordenacao/codigo

# Compilar e executar tudo
make run

# Gerar gráficos
python3 analise_graficos.py
```

## 📊 Resultados

O projeto gera:
- 9 arquivos binários de teste (3 tamanhos × 3 cenários)
- CSVs com métricas detalhadas
- 5 gráficos comparativos
- Relatório completo em PDF

## 📈 Gráficos Gerados

- Tempo × Tamanho (cenário aleatório)
- Comparação de trocas (Selection vs Bubble)
- Insertion Sort em diferentes cenários
- Bubble Sort padrão vs otimizado
- Busca Sequencial vs Binária

## 🎓 Tecnologias

- **Linguagem:** C++ (C++11)
- **Análise:** Python (pandas, matplotlib, seaborn)
- **Build:** Make

## 📖 Documentação

Consulte o [README.txt](codigo/README.txt) para instruções detalhadas de compilação e uso.

## 📄 Licença

Este projeto é acadêmico e está disponível para fins educacionais.
