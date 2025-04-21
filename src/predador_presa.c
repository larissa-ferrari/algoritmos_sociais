#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <math.h>
#include "pso.h"
#include "util.h"
#include "predador_presa.h"

#define DIM 2
#define MIN -5.12
#define MAX 5.12
#define C1 1.5
#define C2 1.5

double pso_predador_presa(
    int n_particulas,
    double (*funcao)(double, double),
    ControleVelocidade tipo_controle,
    double vmax,
    double wmin,
    double wmax,
    int iteracoes,
    double alpha,
    double A,
    double lambda
) {
    Particula p[n_particulas];
    double g_best[DIM];
    double g_val = DBL_MAX;

    double predador[DIM] = {
        rand_double(MIN, MAX),
        rand_double(MIN, MAX)
    };

    for (int i = 0; i < n_particulas; i++) {
        for (int d = 0; d < DIM; d++) {
            p[i].pos[d] = rand_double(MIN, MAX);
            p[i].vel[d] = rand_double(-1, 1);
            p[i].best_pos[d] = p[i].pos[d];
        }
        p[i].best_val = funcao(p[i].pos[0], p[i].pos[1]);

        if (p[i].best_val < g_val) {
            g_val = p[i].best_val;
            g_best[0] = p[i].pos[0];
            g_best[1] = p[i].pos[1];
        }
    }

    for (int t = 0; t < iteracoes; t++) {
        double W = (tipo_controle == INERCIA)
                   ? wmax - ((wmax - wmin) / iteracoes) * t
                   : 1.0;

        // Atualiza posição do predador em direção ao g_best
        for (int d = 0; d < DIM; d++) {
            double v_pred = alpha * (g_best[d] - predador[d]);
            predador[d] += v_pred;
        }

        for (int i = 0; i < n_particulas; i++) {
            double d_pred = distancia(p[i].pos, predador);
            double fuga = A * exp(-lambda * d_pred);

            for (int d = 0; d < DIM; d++) {
                double r1 = rand_double(0, 1);
                double r2 = rand_double(0, 1);

                // PSO padrão + repulsão do predador
                p[i].vel[d] = W * p[i].vel[d]
                    + C1 * r1 * (p[i].best_pos[d] - p[i].pos[d])
                    + C2 * r2 * (g_best[d] - p[i].pos[d])
                    + fuga;

                // Controle de velocidade
                if (tipo_controle == LIMITADO) {
                    if (p[i].vel[d] > vmax) p[i].vel[d] = vmax;
                    if (p[i].vel[d] < -vmax) p[i].vel[d] = -vmax;
                }

                p[i].pos[d] += p[i].vel[d];

                // Limites de posição
                if (p[i].pos[d] < MIN) p[i].pos[d] = MIN;
                if (p[i].pos[d] > MAX) p[i].pos[d] = MAX;
            }

            double val = funcao(p[i].pos[0], p[i].pos[1]);

            if (val < p[i].best_val) {
                p[i].best_val = val;
                p[i].best_pos[0] = p[i].pos[0];
                p[i].best_pos[1] = p[i].pos[1];
            }

            if (val < g_val) {
                g_val = val;
                g_best[0] = p[i].pos[0];
                g_best[1] = p[i].pos[1];
            }
        }
    }

    return g_val;
}
