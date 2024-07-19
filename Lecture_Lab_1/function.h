#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cmath>

// Compute the error of data blocking
double error(double a, double b, size_t i);

// Save a vector to a file
template<typename T>
void printToFile(const std::string& title, const std::vector<T>& v) {
    std::ofstream out(title);
    for (size_t i = 0; i < v.size(); i++) {
        out << v[i] << "\n";
    }
    out.close();
}

// Function to print a 2D vector to a file
void printToFile_2D(const std::string& path, const std::vector<std::vector<double>>& v);

// Compute the Chi_Square
double ComputeChi2(const std::vector<size_t>& bins, double mean, size_t M);
