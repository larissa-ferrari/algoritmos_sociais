# Algoritmos Sociais de Busca em C

Este projeto implementa e compara variações do algoritmo PSO (Particle Swarm Optimization) utilizando os modelos:

- PSO Base (com e sem controle de velocidade)
- PSO com Inércia
- Modelo Predador-Presa
- Modelo de Partículas Carregadas

As otimizações são feitas sobre duas funções conhecidas:
- Rastrigin
- Rosenbrock

Os dados são exportados e analisados com gráficos em Python.

---

## Estrutura do projeto

```
algoritmos_sociais/
├── src/                       # Código-fonte em C
├── include/                   # Arquivos de cabeçalho (.h)
├── dados_saida/              # Resultados gerados (CSVs)
├── graficos/
│   └── plot_resultados.py    # Script Python para gerar gráficos
├── Makefile                  # Compilação automatizada
└── main                      # Executável (gerado após `make`)
```

---

## Como rodar o projeto

### 1. Requisitos

- Compilador C (ex: `gcc`)
- Python 3 com bibliotecas:
  - `matplotlib`
  - `seaborn`
  - `pandas`

Para instalar:
```bash
pip install matplotlib seaborn pandas
```

### 2. Compilar e executar os algoritmos

No terminal, rode:

```bash
make
./main
```

Isso vai:
- Executar todas as simulações com diferentes métodos e parâmetros
- Gerar arquivos CSV com os resultados em `dados_saida/`

### 3. Gerar gráficos a partir dos dados

```bash
cd graficos
python3 plot_resultados.py
```

Os gráficos serão salvos automaticamente na pasta `graficos/`.

---

## Gráficos gerados

- **Boxplots por função (rastrigin, rosenbrock)**
- **Barras com médias e desvios por método**
- **Comparativos por modelo (Base, Predador-Presa, Carga)**

---

## Observações

- O arquivo `main.c` limpa os arquivos CSV a cada nova execução.
- Todos os resultados são baseados em **10 execuções por cenário**.
- Use `make clean` para remover o executável.

---

## Autores

- Caio Bohlhalter de Souza | RA: 221152041
- Jeferson Patrick Dietrich Filho | RA: 221154231
- Larissa Rodrigues Ferrari | RA: 221151214
- Lucas Quintas Honorato | RA: 231150016
- Murilo Augusto Venturato | RA: 221152601

