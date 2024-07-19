#include<iostream>
#include<functional>
#include<cmath>
#include"random.h"
#include<vector>
#include<fstream>
#include"function.h"

int main(){

    // Initialize random number generator
    Random rnd;
    rnd.Initialization();

    // Number of blocks and total number of random points
    size_t n_blocks{1000};
    size_t N{100000};
    size_t m{N / n_blocks}; // Points per block

    // Function to integrate
    std::function<double(double)> f = MyFunction;

    // Function used in importance sampling method
    std::function<double(double)> g = IS_Function;

    // Vectors to store results
    std::vector<double> v_HoM;
    std::vector<double> v_HoM2;
    std::vector<double> v_IS;
    std::vector<double> v_IS2;

    // Integration limits and constants
    double x_min = 0;
    double x_max = 1;
    double f_max = half_pi; // Maximum value of f(x) in the interval
    double g_max = 2; // Maximum value of g(x) in the interval
    double g_integral = 3/2.0; // Integral of g(x) over the interval

    // Perform integration over blocks
    for(size_t i{}; i < n_blocks; i++){

        // Compute integral using hit-or-miss method
        double pi_HoM = computeIntegralHoM(f, x_min, x_max, f_max, m, rnd);
        // Compute integral using importance sampling method
        double pi_IS = computeIntegral_IS(f, g, x_min, x_max, g_max, g_integral, m, rnd);

        // Store results
        v_HoM.push_back(pi_HoM);
        v_IS.push_back(pi_IS);
        v_HoM2.push_back(pi_HoM * pi_HoM);
        v_IS2.push_back(pi_IS * pi_IS);
    }

    // Vectors to store progressive sums and errors
    std::vector<double> sum_prog_HoM;
    std::vector<double> sum_prog_IS;
    std::vector<double> error_HoM;
    std::vector<double> error_IS;

    // Compute progressive sums and errors
    for(size_t i{}; i < n_blocks; i++){

        double sum_HoM{};
        double sum_IS{};
        double sum_HoM2{};
        double sum_IS2{};

        // Accumulate sums up to the i-th block
        for(size_t j{}; j < i+1; j++){
            sum_HoM += v_HoM[j];
            sum_IS += v_IS[j];
            sum_HoM2 += v_HoM2[j];
            sum_IS2 += v_IS2[j];
        }

        // Compute average values
        sum_HoM /= (i+1);
        sum_IS /= (i+1);
        sum_HoM2 /= (i+1);
        sum_IS2 /= (i+1);

        // Store progressive sums and errors
        sum_prog_HoM.push_back(sum_HoM);
        sum_prog_IS.push_back(sum_IS);
        error_HoM.push_back(error(sum_HoM, sum_HoM2, i));
        error_IS.push_back(error(sum_IS, sum_IS2, i));
    }

    // Write results to files
    printToFile("OUTPUT/es1_pi_HoM.txt", sum_prog_HoM);
    printToFile("OUTPUT/es1_pi_IS.txt", sum_prog_IS);
    printToFile("OUTPUT/es1_error_HoM.txt", error_HoM);
    printToFile("OUTPUT/es1_error_IS.txt", error_IS);

    // Indicate completion
    puts("\nEverything is done   :) \n");

    return 0;
}
