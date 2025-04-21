#ifndef PSO_H
#define PSO_H

#define DIM 2 // 2D: x e y
#define MAX_ITER 1000

typedef struct {
    double pos[DIM];
    double vel[DIM];
    double best_pos[DIM];
    double best_val;
} Particula;

// Tipos de controle de velocidade
typedef enum {
    SEM_CONTROLE,
    LIMITADO,
    INERCIA
} ControleVelocidade;

// Função para rodar o PSO base
double pso_base(
    int n_particulas,
    double (*funcao)(double, double),
    ControleVelocidade tipo_controle,
    double vmax,
    double wmin,
    double wmax,
    int iteracoes
);

#endif
