#include <iostream>
#include <vector>
#include "random.h"
#include <string>
#include <fstream>
#include <cmath>

// Function to calculate the error (standard deviation of the mean)
double error(double a, double b, size_t i) {
    if (i < 2) return 0;
    else {
        return sqrt((b - pow(a, 2)) / double(i - 1));
    }
}

// Function to save data to a file
void saveToFile(const std::vector<double>& v, std::string path) {
    std::ofstream out(path);
    for (const auto& p : v) {
        out << p << "\n";
    }
    out.close();
}

int main() {

    // Create a random number generator
    Random rnd;
    rnd.Initialization();

    // Simulation parameters
    size_t n_blocks{1000}; // Number of blocks for data blocking
    size_t N{100000}; // Total number of samples
    size_t m{N / n_blocks}; // Samples per block

    // Option parameters
    double S_0{100}; // Initial stock price
    double T{1}; // Time to maturity
    double K{100}; // Strike price
    double r{0.1}; // Risk-free interest rate
    double sigma{0.25}; // Volatility

    // =============================
    //       DIRECT SAMPLING
    // =============================

    // Vectors to store the results and errors
    std::vector<double> p_avg;
    std::vector<double> c_avg;
    std::vector<double> p_err;
    std::vector<double> c_err;

    // Variables for cumulative sums needed for data blocking
    double P_cum{};
    double C_cum{};
    double P_cum2{};
    double C_cum2{};

    // Iterate over each block
    for (size_t i{}; i < n_blocks; i++) {
        double C{}; // Call option payoff
        double P{}; // Put option payoff
        
        for (size_t j{}; j < m; j++) {
            // Generate a random number from a Gaussian distribution
            double z_i = rnd.Gauss(0, T);
            // Simulate the stock price at time T
            double S_i = S_0 * exp((r - (pow(sigma, 2) / 2)) * T + sigma * z_i * pow(T, 0.5));
            // Calculate the payoff for call and put options
            C += exp(-r * T) * std::max(0., S_i - K);
            P += exp(-r * T) * std::max(0., K - S_i);
        }

        // Calculate average payoffs for this block
        P /= m;
        C /= m;

        // Update cumulative sums
        P_cum += P;
        C_cum += C;
    
        P_cum2 += pow(P, 2);
        C_cum2 += pow(C, 2);

        // Store the average payoffs and their errors
        p_avg.push_back(P_cum / (i + 1));
        c_avg.push_back(C_cum / (i + 1));
        p_err.push_back(error(P_cum / (i + 1), P_cum2 / (i + 1), (i + 1)));
        c_err.push_back(error(C_cum / (i + 1), C_cum2 / (i + 1), (i + 1)));
    }

    // Save the results to files
    saveToFile(p_avg, "OUTPUT/p_avg_dir.txt");
    saveToFile(c_avg, "OUTPUT/c_avg_dir.txt");
    saveToFile(p_err, "OUTPUT/p_err_dir.txt");
    saveToFile(c_err, "OUTPUT/c_err_dir.txt");

    // =============================
    //     DISCRETIZED SAMPLING
    // =============================

    // Define the time increment for discretization
    double increment{0.01};
    size_t steps = static_cast<size_t>(T / increment);

    // Clear the vectors to store the new results and errors
    p_avg.clear();
    c_avg.clear();
    p_err.clear();
    c_err.clear();

    // Reset cumulative sums
    P_cum = 0;
    C_cum = 0;
    P_cum2 = 0;
    C_cum2 = 0;

    // Iterate over each block
    for (size_t i{}; i < n_blocks; i++) {
        double C{}; // Call option payoff
        double P{}; // Put option payoff

        for (size_t j{}; j < m; j++) {
            double S_i = S_0;

            // Iterate over each step
            for (size_t k{}; k < steps; k++) {
                // Generate a random number from a Gaussian distribution
                double z_i = rnd.Gauss(0, T);
                // Update the stock price incrementally
                S_i *= exp((r - (pow(sigma, 2) / 2)) * increment + sigma * z_i * sqrt(increment));
            }

            // Calculate the payoff for call and put options
            C += exp(-r * T) * std::max(0., S_i - K);
            P += exp(-r * T) * std::max(0., K - S_i);
        }

        // Calculate average payoffs for this block
        P /= m;
        C /= m;

        // Update cumulative sums
        P_cum += P;
        C_cum += C;
    
        P_cum2 += pow(P, 2);
        C_cum2 += pow(C, 2);

        // Store the average payoffs and their errors
        p_avg.push_back(P_cum / (i + 1));
        c_avg.push_back(C_cum / (i + 1));
        p_err.push_back(error(P_cum / (i + 1), P_cum2 / (i + 1), (i + 1)));
        c_err.push_back(error(C_cum / (i + 1), C_cum2 / (i + 1), (i + 1)));
    }

    // Save the results to files
    saveToFile(p_avg, "OUTPUT/p_avg_disc.txt");
    saveToFile(c_avg, "OUTPUT/c_avg_disc.txt");
    saveToFile(p_err, "OUTPUT/p_err_disc.txt");
    saveToFile(c_err, "OUTPUT/c_err_disc.txt");

    return 0;
}
