#include <iostream>
#include <cmath>
#include <vector>
#include <string>
#include "class.h"
#include <fstream>
#include <functional>
#include "random.h"
#include <cassert>

#define half_pi (M_PI / 2)

// Function to compute the error
// a: current average, b: current squared average, i: number of iterations
double error(double a, double b, size_t i);

// Function definition to integrate
double MyFunction(double x);

// Special function for importance sampling
double IS_Function(double x);

// Function to print a vector into a file
template<typename T>
void printToFile(const std::string& path, const std::vector<T>& v) {
    std::ofstream out(path);
    
    for (size_t i{}; i < v.size(); i++) {
        out << v[i] << std::endl;
    } 

    out.close();
    return;
}

// Compute integral using the Hit-or-Miss method
// f: function to integrate, a: lower limit, b: upper limit, f_max: max value of f, 
// n_iterations: number of iterations, rnd: random number generator
double computeIntegralHoM(std::function<double(double)>& f, double a, double b, double f_max, size_t n_iterations, Random& rnd);

// Function to compute integral using importance sampling
// f: function to integrate, g: sampling function, a: lower limit, b: upper limit,
// g_max: max value of g, g_integral: integral of g over [a, b], n_iterations: number of iterations, rnd: random number generator
double computeIntegral_IS(std::function<double(double)>& f, std::function<double(double)>& g, 
                          double a, double b, double g_max, double g_integral, size_t n_iterations, Random& rnd);

// Function to print positions to a file
// path: file path, v_p: vector of Position objects
template<typename T>
void printToFile_Positions(const std::string& path, const std::vector<Position<T>>& v_p) {
    std::ofstream out(path);

    for (auto p : v_p) {
        out << p.m_x << " " << p.m_y << " " << p.m_z << "\n";
    }

    out.close();
    return;
}

// Function to perform progressive sum of vectors
// a: input vector, b: output vector (same size as a)
template<typename T>
void ProgSumVector(const std::vector<Position<T>>& a, std::vector<Position<T>>& b) {
    assert((a.size() == b.size()) && "Error - trying to sum vector of different size!");

    for (size_t i{}; i < a.size(); i++) {
        b[i].m_x += a[i].m_x;
        b[i].m_y += a[i].m_y;
        b[i].m_z += a[i].m_z;
    }

    return;
}

// Function to return the norm of the vector
// p: Position object
template<typename T>
double Norm(const Position<T>& p) {
    return pow(pow(p.m_x, 2) + pow(p.m_y, 2) + pow(p.m_z, 2), 0.5);
}

// Normalize a vector by dividing each element by n
// v: input vector, n: normalization factor
void Normalize(std::vector<double>& v, size_t n);

// Print a matrix to a file
// path: file path, mat: matrix (vector of vectors)
void printToFile_Matrix(const std::string& path, const std::vector<std::vector<double>>& mat);

// Compute the average of a vector
// v: input vector
double avgVector(const std::vector<double>& v);
