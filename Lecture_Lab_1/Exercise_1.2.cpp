#include<iostream>
#include<vector>
#include<cmath>
#include"random.h"
#include"function.h"

int main() {
    Random rnd;
    rnd.Initialization();

    size_t n{10000}; // Number of realizations
    std::vector<size_t> Throws{1, 2, 10, 100}; // Different values of N

    // Vectors to store results for uniform, exponential, and Lorentzian distributions
    std::vector<std::vector<double>> v_Unif(Throws.size());
    std::vector<std::vector<double>> v_Exp(Throws.size());
    std::vector<std::vector<double>> v_Lorentz(Throws.size());

    for(size_t i{}; i < Throws.size(); i++) {
        for(size_t j{}; j < n; j++) {
            double sum_unif{}; // Sum for uniform distribution
            double sum_exp{}; // Sum for exponential distribution
            double sum_lorentz{}; // Sum for Lorentzian distribution

            // Generate Throws[i] random numbers for each distribution and sum them
            for(size_t k{}; k < Throws[i]; k++) {
                sum_unif += rnd.Rannyu(); // Uniform distribution
                sum_exp += rnd.Exp(1); // Exponential distribution (lambda = 1)
                double lor = rnd.Lorentz(0.0, 1.0);
                // sum_lorentz += rnd.Lorentz(0.0, 1.0); // Lorentzian distribution (gamma = 1, mu = 0)
                sum_lorentz += lor; // Lorentzian distribution (gamma = 1, mu = 0)
                if(lor > 200 || lor < -200) std::cout<<lor<<"\n";

            }

            // Calculate the average for each distribution
            sum_unif /= Throws[i];
            sum_exp /= Throws[i];
            sum_lorentz /= Throws[i];

            // Store the results
            v_Unif[i].push_back(sum_unif);
            v_Exp[i].push_back(sum_exp);
            v_Lorentz[i].push_back(sum_lorentz);
        }
    }

    // Save the results to files
    printToFile_2D("OUTPUT/es2_unif.txt", v_Unif);
    printToFile_2D("OUTPUT/es2_exp.txt", v_Exp);
    printToFile_2D("OUTPUT/es2_lorentz.txt", v_Lorentz);

    std::cerr << " ---> 2 files saved :) \n";

    return 0;
}
