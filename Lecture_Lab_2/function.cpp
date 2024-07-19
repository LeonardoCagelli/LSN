#include "function.h"

// Function to compute the error
// a: current average, b: current squared average, i: number of iterations
double error(double a, double b, size_t i) {
    if (i < 2) return 0; // Error is 0 if less than 2 samples
    else {
        return sqrt((b - pow(a, 2)) / (i - 1)); // Standard deviation of the mean
    }
}

// Function definition to integrate
double MyFunction(double x) {
    return half_pi * cos(half_pi * x);
}

// Special function for importance sampling
double IS_Function(double x) {
    return 2 - x;
}

// Compute integral using the Hit-or-Miss method
// f: function to integrate, a: lower limit, b: upper limit, f_max: max value of f, 
// n_iterations: number of iterations, rnd: random number generator
double computeIntegralHoM(std::function<double(double)>& f, double a, double b, double f_max, size_t n_iterations, Random& rnd) {
    size_t hit{}; // Counter for hits under the curve

    // Perform the Hit-or-Miss method
    for (size_t i{}; i < n_iterations; i++) {
        double x = rnd.Rannyu(a, b); // Generate random x in [a, b]
        double y = f_max * rnd.Rannyu(); // Generate random y in [0, f_max]
        if (y < f(x)) hit++; // Count hits under the curve
    }

    double p = hit / double(n_iterations); // Probability of hitting under the curve
    double tot = (b - a) * f_max; // Total area of the rectangle
    return p * tot; // Estimate of the integral
}

// Function to compute integral using importance sampling
// f: function to integrate, g: sampling function, a: lower limit, b: upper limit,
// g_max: max value of g, g_integral: integral of g over [a, b], n_iterations: number of iterations, rnd: random number generator
double computeIntegral_IS(std::function<double(double)>& f, std::function<double(double)>& g, 
                          double a, double b, double g_max, double g_integral, size_t n_iterations, Random& rnd) {
    double sum{};

    // Perform importance sampling
    for (size_t i{}; i < n_iterations; i++) {
        double x = rnd.GenerateDistribution(g, a, b, g_max); // Generate x according to distribution g
        sum += (f(x) / g(x)); // Accumulate weighted function values
    }

    double avg = sum / double(n_iterations); // Average of weighted function values
    return avg * g_integral; // Estimate of the integral (I have to multiply for g_integral beacuse g isn't normalized)
}

// Normalize a vector by dividing each element by n
void Normalize(std::vector<double>& v, size_t n) {
    for (size_t i{}; i < v.size(); i++) v[i] /= n;
}

// Print a matrix to a file
void printToFile_Matrix(const std::string& path, const std::vector<std::vector<double>>& mat) {
    std::ofstream out(path);

    for (size_t i{}; i < mat[0].size(); i++) {
        for (size_t j{}; j < mat.size(); j++) {
            out << mat[j][i] << " ";
        }
        out << std::endl;
    }

    out.close();
}

// Compute the average of a vector
double avgVector(const std::vector<double>& v) {
    double avg{};
    for (size_t i{}; i < v.size(); i++) {
        avg += v[i];
    }

    avg /= v.size(); // Compute average
    return avg;
}
