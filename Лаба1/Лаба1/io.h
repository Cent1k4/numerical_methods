#pragma once
#include <vector>
#include <string>

void print_table(int n, double h, const std::vector<double>& x, const std::vector<double>& u, const std::vector<double>& y, const std::string& title, double ms);

void run_experiment(const std::vector<int>& ns);

double max_abs_diff(const std::vector<double>& a, const std::vector<double>& b);