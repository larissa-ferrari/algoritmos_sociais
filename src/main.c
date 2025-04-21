#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>  // Necessário para strcmp
#include "funcoes_objetivo.h"
#include "util.h"
#include "pso.h"
#include "particulas_carga.h"
#include "predador_presa.h"

#define MAX_ITER 1000
#define EXECUCOES 10

int tamanhos_particulas[] = {10, 30, 50};

void rodar_modelo_base(const char *func_nome, double (*func)(double, double)) {
    for (int i = 0; i < 3; i++) {
        int n = tamanhos_particulas[i];
        for (int exec = 1; exec <= EXECUCOES; exec++) {

            double minimo = pso_base(n, func, SEM_CONTROLE, 2.0, 0.4, 0.9, MAX_ITER);
            printf("[DEBUG] SEM_CONTROLE - %s | n=%d | exec=%d | minimo=%.6f\n", func_nome, n, exec, minimo);
            salvar_resultado_csv("dados_saida/resultados_base.csv", "pso_base", func_nome, n, exec, minimo);

            minimo = pso_base(n, func, LIMITADO, 2.0, 0.4, 0.9, MAX_ITER);
            printf("[DEBUG] LIMITADO - %s | n=%d | exec=%d | minimo=%.6f\n", func_nome, n, exec, minimo);
            salvar_resultado_csv("dados_saida/resultados_base.csv", "pso_limitado", func_nome, n, exec, minimo);

            minimo = pso_base(n, func, INERCIA, 2.0, 0.4, 0.9, MAX_ITER);
            printf("[DEBUG] INERCIA - %s | n=%d | exec=%d | minimo=%.6f\n", func_nome, n, exec, minimo);
            salvar_resultado_csv("dados_saida/resultados_base.csv", "pso_inercia", func_nome, n, exec, minimo);
        }
    }
}

void rodar_predador_presa(const char *func_nome, double (*func)(double, double)) {
    for (int i = 0; i < 3; i++) {
        int n = tamanhos_particulas[i];
        for (int exec = 1; exec <= EXECUCOES; exec++) {

            double minimo = pso_predador_presa(n, func, LIMITADO, 2.0, 0.4, 0.9, MAX_ITER, 0.05, 1.0, 1.0);
            printf("[DEBUG] PREDADOR_LIMITADO - %s | n=%d | exec=%d | minimo=%.6f\n", func_nome, n, exec, minimo);
            salvar_resultado_csv("dados_saida/resultados_predador.csv", "predador_presa_limitado", func_nome, n, exec, minimo);

            minimo = pso_predador_presa(n, func, INERCIA, 2.0, 0.4, 0.9, MAX_ITER, 0.05, 1.0, 1.0);
            printf("[DEBUG] PREDADOR_INERCIA - %s | n=%d | exec=%d | minimo=%.6f\n", func_nome, n, exec, minimo);
            salvar_resultado_csv("dados_saida/resultados_predador.csv", "predador_presa_inercia", func_nome, n, exec, minimo);
        }
    }
}

void rodar_particulas_carregadas(const char *func_nome, double (*func)(double, double)) {
    for (int i = 0; i < 3; i++) {
        int n = tamanhos_particulas[i];
        for (int exec = 1; exec <= EXECUCOES; exec++) {

            double minimo = pso_particulas_carregadas(n, func, LIMITADO, 2.0, 0.4, 0.9, MAX_ITER, 0.1, 0.1, 2.0);
            printf("[DEBUG] CARGA_LIMITADO - %s | n=%d | exec=%d | minimo=%.6f\n", func_nome, n, exec, minimo);
            salvar_resultado_csv("dados_saida/resultados_carga.csv", "carga_limitado", func_nome, n, exec, minimo);

            minimo = pso_particulas_carregadas(n, func, INERCIA, 2.0, 0.4, 0.9, MAX_ITER, 0.1, 0.1, 2.0);
            printf("[DEBUG] CARGA_INERCIA - %s | n=%d | exec=%d | minimo=%.6f\n", func_nome, n, exec, minimo);
            salvar_resultado_csv("dados_saida/resultados_carga.csv", "carga_inercia", func_nome, n, exec, minimo);
        }
    }
}

int main() {
    srand(time(NULL));

    remove("dados_saida/resultados_base.csv");
    remove("dados_saida/resultados_predador.csv");
    remove("dados_saida/resultados_carga.csv");

    printf("Executando para função Rastrigin...\n");
    rodar_modelo_base("rastrigin", rastrigin);
    rodar_predador_presa("rastrigin", rastrigin);
    rodar_particulas_carregadas("rastrigin", rastrigin);

    printf("Executando para função Rosenbrock...\n");
    rodar_modelo_base("rosenbrock", rosenbrock);
    rodar_predador_presa("rosenbrock", rosenbrock);
    rodar_particulas_carregadas("rosenbrock", rosenbrock);

    printf("Experimentos finalizados. Resultados salvos em dados_saida/.\n");
    return 0;
}
