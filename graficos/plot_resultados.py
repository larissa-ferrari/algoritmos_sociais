import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns
import os

sns.set(style="whitegrid")

# Diretório de saída
PASTA_SAIDA = "graficos"

# Garante que o diretório existe
os.makedirs(PASTA_SAIDA, exist_ok=True)

# Caminho para os CSVs
arquivos = {
    "Base": "dados_saida/resultados_base.csv",
    "Predador-Presa": "dados_saida/resultados_predador.csv",
    "Partículas Carregadas": "dados_saida/resultados_carga.csv",
}


def carregar_dados(nome_modelo, caminho):
    if not os.path.exists(caminho):
        print(f"Arquivo não encontrado: {caminho}")
        return pd.DataFrame()
    df = pd.read_csv(caminho, header=None)
    df.columns = ["metodo", "funcao", "particulas", "execucao", "minimo"]
    df["modelo"] = nome_modelo
    return df


# Carrega todos os dados
df_total = pd.concat([carregar_dados(nome, path) for nome, path in arquivos.items()])
if df_total.empty:
    print("Nenhum dado foi carregado. Verifique os arquivos CSV.")
    exit()

# Agrupamento por média/desvio padrão
resumo = (
    df_total.groupby(["modelo", "metodo", "funcao", "particulas"])
    .agg(media_minimo=("minimo", "mean"), desvio_minimo=("minimo", "std"))
    .reset_index()
)


# Gráfico de barras geral por função
def plot_geral(funcao):
    plt.figure(figsize=(12, 6))
    filtro = resumo[resumo["funcao"] == funcao].copy()

    # Transforma eixo x em categórico (evita sobreposição)
    filtro["particulas"] = filtro["particulas"].astype(str)

    # Ordena métodos para consistência visual
    filtro = filtro.sort_values(by=["particulas", "metodo"])

    sns.barplot(
        data=filtro,
        x="particulas",
        y="media_minimo",
        hue="metodo",
        dodge=True,
        capsize=0.1,
        errorbar=None,
    )

    # Adiciona barras de erro manuais
    for i, row in filtro.iterrows():
        plt.errorbar(
            x=row["particulas"],
            y=row["media_minimo"],
            yerr=row["desvio_minimo"],
            fmt="none",
            capsize=5,
            color="black",
        )

    plt.title(f"Mínimo médio por método - {funcao}")
    plt.xlabel("Nº de partículas")
    plt.ylabel("Mínimo médio")
    plt.legend(title="método", loc="upper right")
    plt.tight_layout()
    plt.savefig(f"{PASTA_SAIDA}/grafico_{funcao.lower()}.png")
    plt.close()


# Gráfico separado por modelo
def plot_por_modelo():
    for modelo in df_total["modelo"].unique():
        plt.figure(figsize=(10, 6))
        df = df_total[df_total["modelo"] == modelo]
        sns.barplot(
            data=df,
            x="particulas",
            y="minimo",
            hue="metodo",
            errorbar="sd",
            capsize=0.1,
        )
        plt.title(f"Mínimos por método - Modelo: {modelo}")
        plt.ylabel("Mínimo encontrado")
        plt.tight_layout()
        plt.savefig(f"{PASTA_SAIDA}/modelo_{modelo.lower().replace(' ', '_')}.png")
        plt.close()


# Boxplot por função e método
def plot_boxplot_funcoes():
    for func in df_total["funcao"].unique():
        plt.figure(figsize=(10, 6))
        filtro = df_total[df_total["funcao"] == func]
        sns.boxplot(data=filtro, x="metodo", y="minimo", hue="modelo")
        plt.title(f"Boxplot - Função {func}")
        plt.xticks(rotation=45)
        plt.tight_layout()
        plt.savefig(f"{PASTA_SAIDA}/boxplot_{func.lower()}.png")
        plt.close()


# Geração dos gráficos
for func in df_total["funcao"].unique():
    plot_geral(func)

plot_por_modelo()
plot_boxplot_funcoes()

print("Gráficos salvos na pasta /graficos")
