#include "solvers.h"

std::vector<double> solve_bands(int n, double h, const std::vector<double>& x) {
    std::vector<double> A(n + 1), B(n + 1), C(n + 1), psi(n + 1);

    for (int i = 1; i <= n - 1; ++i) {
        A[i] = 12.0 / (h * h);
        C[i] = 24.0 / (h * h) + 5.0;
        B[i] = 12.0 / (h * h);
        psi[i] = 450.0 * x[i] * x[i] - 2110.0;
    }

    std::vector<double> alpha(n + 1), beta(n + 1);
    alpha[1] = 0.0;
    beta[1] = 10.0;

    for (int i = 1; i <= n - 1; ++i) {
        double den = C[i] - alpha[i] * A[i];
        alpha[i + 1] = B[i] / den;
        beta[i + 1] = (psi[i] + A[i] * beta[i]) / den;
    }

    std::vector<double> y(n + 1);
    y[n] = 100.0;
    for (int i = n - 1; i >= 0; --i)
        y[i] = alpha[i + 1] * y[i + 1] + beta[i + 1];

    return y;
}


std::vector<double> solve_nobands(int n, double h, const std::vector<double>& x) {
    double A = 12.0 / (h * h);
    double C = 24.0 / (h * h) + 5.0;
    double B = 12.0 / (h * h);

    std::vector<double> alpha(n + 1), beta(n + 1);
    alpha[1] = 0.0;
    beta[1] = 10.0;

    for (int i = 1; i <= n - 1; ++i) {
        double psi = 450.0 * x[i] * x[i] - 2110.0;
        double den = C - alpha[i] * A;
        alpha[i + 1] = B / den;
        beta[i + 1] = (psi + A * beta[i]) / den;
    }

    std::vector<double> y(n + 1);
    y[n] = 100.0;
    for (int i = n - 1; i >= 0; --i)
        y[i] = alpha[i + 1] * y[i + 1] + beta[i + 1];

    return y;
}