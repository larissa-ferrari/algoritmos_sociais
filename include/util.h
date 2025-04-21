#ifndef UTIL_H
#define UTIL_H

#include <stdio.h>

// Geração de número aleatório entre dois valores
double rand_double(double min, double max);

// Escrita de resultados no CSV
void salvar_resultado_csv(
    const char *arquivo,
    const char *metodo,
    const char *funcao,
    int particulas,
    int execucao,
    double minimo
);

// Cálculo de norma euclidiana (distância entre dois vetores 2D)
double distancia(double *a, double *b);

#endif
