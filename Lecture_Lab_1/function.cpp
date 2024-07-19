#include "function.h"

// Compute the error of data blocking
double error(double a, double b, size_t i) {
    if (i < 2) return 0;
    else {
        return sqrt((b - pow(a, 2)) / (i - 1));
    }
}

// Function to print a 2D vector to a file
void printToFile_2D(const std::string& path, const std::vector<std::vector<double>>& v) {
    std::ofstream out(path);
    for (size_t i = 0; i < v[0].size(); i++) {
        for (size_t j = 0; j < v.size(); j++) {
            out << v[j][i] << " ";
        }
        out << std::endl;
    }
    out.close();
}

// Compute the Chi_Square
double ComputeChi2(const std::vector<size_t>& bins, double mean, size_t M){
    double chi2{};
    for(size_t i{};i<M;i++){
        chi2 += pow(bins[i] - mean, 2) / mean;
    }
    return chi2;
}
