#pragma once
#include<iostream>
#include<vector>
#include<fstream>
#include<string>
#include"random.h"
#include"class.h"

using History = std::vector<std::tuple<std::vector<double>, std::tuple<double, double>>>;

// Compute the error in data blocking 
double error(double a, double b, size_t i);

// Perform a metropolis step 
double MetropoliStep(const Trial_Function& func, Random& rnd, double x, double delta, size_t& iteration, size_t& accepted);

// Save training history to file
void SaveHistory(const std::string& param_path, const std::string& energy_path, const History& history);
