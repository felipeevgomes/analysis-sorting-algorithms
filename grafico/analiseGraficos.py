import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns

# Configurar estilo dos gráficos
sns.set_style("whitegrid")
plt.rcParams['figure.figsize'] = (12, 6)
plt.rcParams['font.size'] = 10

# ====================================
# CARREGAR DADOS
# ====================================
print("Carregando dados...")
# Ajuste dos caminhos para rodar a partir da raiz do projeto
df_ord = pd.read_csv('codigo/resultados_ordenacao.csv')
df_busca = pd.read_csv('codigo/resultados_busca.csv')

# Extrair informações do nome do arquivo (ex: pequeno-aleatorios.bin)
df_ord['Tamanho'] = df_ord['Arquivo'].str.extract(r'(pequeno|medio|grande)')
df_ord['Cenario'] = df_ord['Arquivo'].str.extract(r'-(aleatorios|crescente|descresente)')

# Padronizar nomes dos cenários
cenario_map = {
    'aleatorios': 'aleatorio',
    'crescente': 'crescente',
    'descresente': 'decrescente'
}
df_ord['Cenario'] = df_ord['Cenario'].map(cenario_map)

# Mapear tamanhos para valores numéricos
tamanho_map = {'pequeno': 1000, 'medio': 10000, 'grande': 100000}
df_ord['N'] = df_ord['Tamanho'].map(tamanho_map)

print("Dados carregados com sucesso!")
print(f"Total de registros de ordenação: {len(df_ord)}")
print(f"Total de registros de busca: {len(df_busca)}")

# ====================================
# GRÁFICO 1: Tempo x Tamanho (Aleatório)
# ====================================
print("\nGerando Gráfico 1: Tempo x Tamanho (Cenário Aleatório)...")

aleatorio = df_ord[df_ord['Cenario'] == 'aleatorio']

plt.figure(figsize=(12, 7))
for algoritmo in aleatorio['Algoritmo'].unique():
    dados = aleatorio[aleatorio['Algoritmo'] == algoritmo]
    plt.plot(dados['N'], dados['Tempo_ms'], marker='o', linewidth=2, label=algoritmo)

plt.xlabel('Tamanho do Vetor (N)', fontsize=12, fontweight='bold')
plt.ylabel('Tempo de Execução (ms)', fontsize=12, fontweight='bold')
plt.title('Tempo de Execução x Tamanho do Vetor - Cenário Aleatório', 
          fontsize=14, fontweight='bold', pad=20)
plt.legend(fontsize=10, loc='upper left')
plt.grid(True, alpha=0.3)
plt.yscale('log')  # Escala logarítmica para melhor visualização
plt.tight_layout()
plt.savefig('grafico1_tempo_tamanho.png', dpi=300, bbox_inches='tight')
print("✓ Gráfico salvo: grafico1_tempo_tamanho.png")

# ====================================
# GRÁFICO 2: Trocas - Selection vs Bubble (Médio Aleatório)
# ====================================
print("\nGerando Gráfico 2: Comparação de Trocas (Médio Aleatório)...")

medio_aleatorio = df_ord[(df_ord['Tamanho'] == 'medio') & 
                          (df_ord['Cenario'] == 'aleatorio') &
                          (df_ord['Algoritmo'].isin(['Selection Sort', 'Bubble Sort']))]

plt.figure(figsize=(10, 6))
algoritmos = medio_aleatorio['Algoritmo']
trocas = medio_aleatorio['Trocas']
cores = ['#FF6B6B', '#4ECDC4']

bars = plt.bar(algoritmos, trocas, color=cores, edgecolor='black', linewidth=1.5)

# Adicionar valores no topo das barras
for bar in bars:
    height = bar.get_height()
    plt.text(bar.get_x() + bar.get_width()/2., height,
             f'{int(height):,}',
             ha='center', va='bottom', fontsize=11, fontweight='bold')

plt.xlabel('Algoritmo', fontsize=12, fontweight='bold')
plt.ylabel('Número de Trocas (Swaps)', fontsize=12, fontweight='bold')
plt.title('Comparação de Trocas: Selection Sort vs Bubble Sort\n(Tamanho Médio - Cenário Aleatório)', 
          fontsize=14, fontweight='bold', pad=20)
plt.grid(True, axis='y', alpha=0.3)
plt.tight_layout()
plt.savefig('grafico2_trocas_selection_bubble.png', dpi=300, bbox_inches='tight')
print("✓ Gráfico salvo: grafico2_trocas_selection_bubble.png")

# ====================================
# GRÁFICO 3: Insertion Sort - Comparação de Cenários
# ====================================
print("\nGerando Gráfico 3: Insertion Sort em Diferentes Cenários...")

insertion = df_ord[df_ord['Algoritmo'] == 'Insertion Sort']

fig, (ax1, ax2) = plt.subplots(1, 2, figsize=(15, 6))

# Tempo
for cenario in ['aleatorio', 'crescente', 'decrescente']:
    dados = insertion[insertion['Cenario'] == cenario]
    ax1.plot(dados['N'], dados['Tempo_ms'], marker='o', linewidth=2, 
             label=cenario.capitalize())

ax1.set_xlabel('Tamanho do Vetor (N)', fontsize=11, fontweight='bold')
ax1.set_ylabel('Tempo de Execução (ms)', fontsize=11, fontweight='bold')
ax1.set_title('Insertion Sort - Tempo por Cenário', fontsize=12, fontweight='bold')
ax1.legend(fontsize=10)
ax1.grid(True, alpha=0.3)
ax1.set_yscale('log')

# Comparações
for cenario in ['aleatorio', 'crescente', 'decrescente']:
    dados = insertion[insertion['Cenario'] == cenario]
    ax2.plot(dados['N'], dados['Comparacoes'], marker='s', linewidth=2, 
             label=cenario.capitalize())

ax2.set_xlabel('Tamanho do Vetor (N)', fontsize=11, fontweight='bold')
ax2.set_ylabel('Número de Comparações', fontsize=11, fontweight='bold')
ax2.set_title('Insertion Sort - Comparações por Cenário', fontsize=12, fontweight='bold')
ax2.legend(fontsize=10)
ax2.grid(True, alpha=0.3)
ax2.set_yscale('log')

plt.suptitle('Análise do Insertion Sort em Diferentes Cenários', 
             fontsize=14, fontweight='bold', y=1.02)
plt.tight_layout()
plt.savefig('grafico3_insertion_cenarios.png', dpi=300, bbox_inches='tight')
print("✓ Gráfico salvo: grafico3_insertion_cenarios.png")

# ====================================
# GRÁFICO EXTRA 1: Bubble Sort vs Otimizado
# ====================================
print("\nGerando Gráfico Extra: Bubble Sort vs Otimizado...")

bubble_comp = df_ord[df_ord['Algoritmo'].isin(['Bubble Sort', 'Bubble Sort Otimizado'])]

fig, axes = plt.subplots(1, 3, figsize=(18, 5))
cenarios = ['aleatorio', 'crescente', 'decrescente']
titulos = ['Aleatório', 'Crescente (Melhor Caso)', 'Decrescente (Pior Caso)']

for idx, (cenario, titulo) in enumerate(zip(cenarios, titulos)):
    dados = bubble_comp[bubble_comp['Cenario'] == cenario]
    
    for algoritmo in ['Bubble Sort', 'Bubble Sort Otimizado']:
        alg_dados = dados[dados['Algoritmo'] == algoritmo]
        label = 'Otimizado' if 'Otimizado' in algoritmo else 'Padrão'
        axes[idx].plot(alg_dados['N'], alg_dados['Tempo_ms'], 
                       marker='o', linewidth=2, label=label)
    
    axes[idx].set_xlabel('Tamanho (N)', fontsize=10, fontweight='bold')
    axes[idx].set_ylabel('Tempo (ms)', fontsize=10, fontweight='bold')
    axes[idx].set_title(titulo, fontsize=11, fontweight='bold')
    axes[idx].legend(fontsize=9)
    axes[idx].grid(True, alpha=0.3)
    axes[idx].set_yscale('log')

plt.suptitle('Bubble Sort Padrão vs Otimizado - Análise por Cenário', 
             fontsize=14, fontweight='bold')
plt.tight_layout()
plt.savefig('grafico_extra_bubble_otimizado.png', dpi=300, bbox_inches='tight')
print("✓ Gráfico salvo: grafico_extra_bubble_otimizado.png")

# ====================================
# GRÁFICO EXTRA 2: Comparação de Busca
# ====================================
print("\nGerando Gráfico Extra: Busca Sequencial vs Binária...")

fig, (ax1, ax2) = plt.subplots(1, 2, figsize=(14, 6))

# Comparações
categorias = ['Valor\nExistente', 'Valor\nInexistente']
seq_comp = [df_busca[(df_busca['TipoBusca'] == 'Sequencial') & 
                      (df_busca['TipoValor'] == 'Existente')]['Comparacoes'].values[0],
            df_busca[(df_busca['TipoBusca'] == 'Sequencial') & 
                      (df_busca['TipoValor'] == 'Inexistente')]['Comparacoes'].values[0]]
bin_comp = [df_busca[(df_busca['TipoBusca'] == 'Binaria') & 
                      (df_busca['TipoValor'] == 'Existente')]['Comparacoes'].values[0],
            df_busca[(df_busca['TipoBusca'] == 'Binaria') & 
                      (df_busca['TipoValor'] == 'Inexistente')]['Comparacoes'].values[0]]

x = range(len(categorias))
width = 0.35

ax1.bar([i - width/2 for i in x], seq_comp, width, label='Sequencial', color='#FF6B6B')
ax1.bar([i + width/2 for i in x], bin_comp, width, label='Binária', color='#4ECDC4')
ax1.set_ylabel('Número de Comparações', fontsize=11, fontweight='bold')
ax1.set_title('Comparações: Sequencial vs Binária', fontsize=12, fontweight='bold')
ax1.set_xticks(x)
ax1.set_xticklabels(categorias)
ax1.legend(fontsize=10)
ax1.grid(True, axis='y', alpha=0.3)
ax1.set_yscale('log')

# Tempo (incluindo ordenação para binária)
seq_tempo = [df_busca[(df_busca['TipoBusca'] == 'Sequencial') & 
                       (df_busca['TipoValor'] == 'Existente')]['Tempo_ms'].values[0],
             df_busca[(df_busca['TipoBusca'] == 'Sequencial') & 
                       (df_busca['TipoValor'] == 'Inexistente')]['Tempo_ms'].values[0]]

bin_tempo_ord = df_busca[df_busca['TipoBusca'] == 'Binaria']['TempoOrdenacao_ms'].values[0]
bin_tempo = [df_busca[(df_busca['TipoBusca'] == 'Binaria') & 
                       (df_busca['TipoValor'] == 'Existente')]['Tempo_ms'].values[0] + bin_tempo_ord,
             df_busca[(df_busca['TipoBusca'] == 'Binaria') & 
                       (df_busca['TipoValor'] == 'Inexistente')]['Tempo_ms'].values[0] + bin_tempo_ord]

ax2.bar([i - width/2 for i in x], seq_tempo, width, label='Sequencial', color='#FF6B6B')
ax2.bar([i + width/2 for i in x], bin_tempo, width, label='Binária (com ordenação)', color='#4ECDC4')
ax2.set_ylabel('Tempo Total (ms)', fontsize=11, fontweight='bold')
ax2.set_title('Tempo Total: Sequencial vs Binária', fontsize=12, fontweight='bold')
ax2.set_xticks(x)
ax2.set_xticklabels(categorias)
ax2.legend(fontsize=10)
ax2.grid(True, axis='y', alpha=0.3)

plt.suptitle('Análise Comparativa: Busca Sequencial vs Binária\n(Arquivo Grande - 100.000 elementos)', 
             fontsize=14, fontweight='bold')
plt.tight_layout()
plt.savefig('grafico_extra_busca.png', dpi=300, bbox_inches='tight')
print("✓ Gráfico salvo: grafico_extra_busca.png")

# ====================================
# TABELA RESUMO
# ====================================
print("\n" + "="*70)
print("RESUMO DOS DADOS - CENÁRIO ALEATÓRIO (MÉDIO)")
print("="*70)

medio_alea = df_ord[(df_ord['Tamanho'] == 'medio') & (df_ord['Cenario'] == 'aleatorio')]
print(f"\n{'Algoritmo':<25} {'Tempo (ms)':<15} {'Comparações':<15} {'Trocas':<15}")
print("-" * 70)
for _, row in medio_alea.iterrows():
    print(f"{row['Algoritmo']:<25} {row['Tempo_ms']:<15.2f} {int(row['Comparacoes']):<15} {int(row['Trocas']):<15}")

print("\n" + "="*70)
print("RESUMO - BUSCA")
print("="*70)
print(df_busca.to_string(index=False))

print("\n" + "="*70)
print("✓ TODOS OS GRÁFICOS FORAM GERADOS COM SUCESSO!")
print("="*70)
print("\nArquivos criados:")
print("  1. grafico1_tempo_tamanho.png")
print("  2. grafico2_trocas_selection_bubble.png")
print("  3. grafico3_insertion_cenarios.png")
print("  4. grafico_extra_bubble_otimizado.png")
print("  5. grafico_extra_busca.png")
print("\nUse esses gráficos no seu relatório!")