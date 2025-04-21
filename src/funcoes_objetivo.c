#include <math.h>
#include "funcoes_objetivo.h"

double rastrigin(double x, double y) {
    return 20 + x*x + y*y - 10 * (cos(2 * M_PI * x) + cos(2 * M_PI * y));
}

double rosenbrock(double x, double y) {
    return 100 * pow((y - x*x), 2) + pow((1 - x), 2);
}
