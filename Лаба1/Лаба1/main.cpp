#include <iostream>
#include <vector>
#include <chrono>
#include "solvers.h"
#include "io.h"
#include <locale.h>


int main() {
    setlocale(LC_ALL, "Russian");

    int n, k;
    std::cout << "n = ";
    std::cin >> n;

    double h = 1.0 / n;
    std::vector<double> x(n + 1), u(n + 1);
    for (int i = 0; i <= n; ++i) {
        x[i] = i * h;
        u[i] = 10.0 + 90.0 * x[i] * x[i];
    }

    auto t1 = std::chrono::high_resolution_clock::now();
    auto y1 = solve_bands(n, h, x);
    auto t2 = std::chrono::high_resolution_clock::now();
    double ms1 = std::chrono::duration<double, std::milli>(t2 - t1).count();

    auto t3 = std::chrono::high_resolution_clock::now();
    auto y2 = solve_nobands(n, h, x);
    auto t4 = std::chrono::high_resolution_clock::now();
    double ms2 = std::chrono::duration<double, std::milli>(t4 - t3).count();

    print_table(n, h, x, u, y1, "Implementation 1 (with bands)", ms1);
    print_table(n, h, x, u, y2, "Implementation 2 (no bands)", ms2);

    int k1;
    std::cout << "k1 = ";
    std::cin >> k1;

    if (k1 < 1) {
        std::cout << "k должно быть >= 1\n";
        return 1;
    }

    std::vector<int> ns1;
    int  val1 = 10;
    for (int s = 0; s < k1; ++s) {
        ns1.push_back(static_cast<int>(val1));
        val1 *= 10;
    }

    run_experiment(ns1);

    int k2;
    std::cout << "\nk2 = ";
    std::cin >> k2;

    if (k2 < 1) {
        std::cout << "k должно быть >= 1\n";
        return 1;
    }

    std::vector<int> ns2;
    int  val2 = 2;
    for (int s = 0; s < k2; ++s) {
        ns2.push_back(static_cast<int>(val2));
        val2 *= 2;
    }

    run_experiment(ns2);
    return 0;
}