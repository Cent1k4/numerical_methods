#pragma once
#include <vector>

std::vector<double> solve_bands(int n, double h, const std::vector<double>& x);
std::vector<double> solve_nobands(int n, double h, const std::vector<double>& x);