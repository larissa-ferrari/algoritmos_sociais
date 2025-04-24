#ifndef PARTICULAS_CARGA_H
#define PARTICULAS_CARGA_H

#include "pso.h"

double pso_particulas_carregadas(
    int n_particulas,
    double (*funcao)(double, double),
    ControleVelocidade tipo_controle,
    double vmax,
    double wmin,
    double wmax,
    int iteracoes,
    double Qi,
    double Dnuc,
    double Drep
);

#endif