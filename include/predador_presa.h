#ifndef PREDADOR_PRESA_H
#define PREDADOR_PRESA_H

#include "pso.h"

double pso_predador_presa(
    int n_particulas,
    double (*funcao)(double, double),
    ControleVelocidade tipo_controle,
    double vmax,
    double wmin,
    double wmax,
    int iteracoes,
    double alpha,  // intensidade do movimento do predador
    double A,      // força de repulsão
    double lambda  // fator de decaimento da repulsão
);

#endif
