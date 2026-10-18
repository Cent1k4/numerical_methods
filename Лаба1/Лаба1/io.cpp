#include "io.h"
#include "solvers.h"
#include <iostream>
#include <iomanip>
#include <cmath>
#include <chrono>
#include <algorithm>

void print_table(int n, double h, const std::vector<double>& x, const std::vector<double>& u, const std::vector<double>& y, const std::string& title, double ms) {

    std::cout << "\n" << title << ", n = " << n << "\n";
    std::cout << std::setw(6) << "i" << std::setw(12) << "xi" << std::setw(20) << "ui" << std::setw(22) << "vi" << std::setw(18) << "ui - vi" << std::setw(28) << "ri" << "\n";
    std::cout << std::string(120, '-') << "\n";

    double A = 12.0 / (h * h);
    double C = 24.0 / (h * h) + 5.0;
    double B = 12.0 / (h * h);


    for (int i = 0; i <= n; ++i) {
        double diff = u[i] - y[i];

        double res = 0.0;
        bool hasRes = (i >= 1 && i <= n - 1);
        if (hasRes) {
            double psi = 450.0 * x[i] * x[i] - 2110.0;
            res = A * y[i - 1] - C * y[i] + B * y[i + 1] + psi;
        }

        std::cout << std::setw(6) << i
            << std::setw(12) << std::setprecision(4) << std::fixed << x[i]
            << std::setw(20) << std::setprecision(6) << u[i]
            << std::setw(22) << y[i]
            << std::setw(18) << std::scientific << std::setprecision(3) << diff;

        if (hasRes)
            std::cout << std::setw(28) << std::scientific << std::setprecision(3) << res;
        else
            std::cout << std::setw(28) << "-";

        std::cout << "\n";
    }

    std::cout << std::string(120, '-') << "\n";
}

void run_experiment(const std::vector<int>& ns) {
    std::cout << std::string(120, '-') << "\n";
    std::cout << std::setw(10) << "n"<< std::setw(20) << "max|u-v| (bands)"<< std::setw(20) << "max|r| (bands)"<< std::setw(16) << "time1, ms"<< std::setw(16) << "time2, ms" << "\n";
    std::cout << std::string(120, '-') << "\n";

    for (int n : ns) {
        double h = 1.0 / n;
        std::vector<double> x(n + 1), u(n + 1);
        for (int i = 0; i <= n; ++i) {
            x[i] = i * h;
            u[i] = 10.0 + 90.0 * x[i] * x[i];
        }

        auto t1 = std::chrono::high_resolution_clock::now();
        auto v1 = solve_bands(n, h, x);

        auto t2 = std::chrono::high_resolution_clock::now();
        auto v2 = solve_nobands(n, h, x);

        auto t3 = std::chrono::high_resolution_clock::now();

        double ms1 = std::chrono::duration<double, std::milli>(t2 - t1).count();
        double ms2 = std::chrono::duration<double, std::milli>(t3 - t2).count();

        double maxDiff = 0.0, maxRes = 0.0;
        double A = 12.0 / (h * h);
        double C = 24.0 / (h * h) + 5.0;
        double B = 12.0 / (h * h);

        for (int i = 0; i <= n; ++i)
            maxDiff = std::max(maxDiff, std::fabs(u[i] - v1[i]));

        for (int i = 1; i <= n - 1; ++i) {
            double psi = 450.0 * x[i] * x[i] - 2110.0;
            double r = A * v1[i - 1] - C * v1[i] + B * v1[i + 1] + psi;
            maxRes = std::max(maxRes, std::fabs(r));
        }

        std::cout << std::setw(10) << n<< std::setw(20) << std::scientific << std::setprecision(3) << maxDiff << std::setw(20) << maxRes<< std::setw(16) << std::fixed << std::setprecision(3) << ms1<< std::setw(16) << ms2 << "\n";
    }
    std::cout << std::defaultfloat;
}