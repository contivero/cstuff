#include <float.h>
#include <math.h>

/* Heron's method, a.k.a. Babylonian method.
 * The algorithm is quadratically convergent, i.e. the number of correct digits
 * of the approximation roughly doubles with each iteration */
double
heron_sqrt(double x) {
    double x0 = x/2; /* initial approximation; TODO improve it */
    double xn;

    do {
        double xn = x0;
        x0 = (x0 + x/x0)/2;
    } while (fabs(xn - x0) > DBL_EPSILON);

    return xn;
};
