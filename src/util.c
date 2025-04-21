#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "util.h"

double rand_double(double min, double max) {
    return min + ((double) rand() / RAND_MAX) * (max - min);
}

void salvar_resultado_csv(
    const char *arquivo,
    const char *metodo,
    const char *funcao,
    int particulas,
    int execucao,
    double minimo
) {
    printf("[DEBUG] Salvando resultado: %s | %s | %s | %d | %.10f\n",
           arquivo, metodo, funcao, particulas, minimo);

    FILE *f = fopen(arquivo, "a");
    if (f == NULL) {
        printf("Erro ao abrir o arquivo %s\n", arquivo);
        return;
    }

    fprintf(f, "%s,%s,%d,%d,%.10f\n", metodo, funcao, particulas, execucao, minimo);
    fclose(f);
}


double distancia(double *a, double *b) {
    return sqrt((a[0] - b[0]) * (a[0] - b[0]) + (a[1] - b[1]) * (a[1] - b[1]));
}
