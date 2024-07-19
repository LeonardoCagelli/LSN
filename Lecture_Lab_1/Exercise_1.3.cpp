#include<iostream>
#include<vector>
#include<cmath>
#include"random.h"
#include"function.h"

int main(){

    Random rnd;
    rnd.Initialization();

    size_t N{100000}; // Total number of needle throws
    size_t m{1000}; // Number of throws per block
    size_t n_block{N / m}; // Number of blocks
    double L{10}; // Length of the needle
    double d{15}; // Distance between the lines (d > L)

    std::vector<double> pi_values; // Vector to store π estimates
    std::vector<double> pi_values2; // Vector to store squares of π estimates for variance calculation
    std::vector<double> v_devstd; // Vector to store standard deviations

    for(size_t i{}; i < n_block; i++) {
        size_t N_hit{}; // Counter for the number of hits

        for(size_t j{}; j < m; j++) {
            double theta;
            // Generate a random angle theta uniformly distributed in [0, π/2]
            while(true) {
                double a = rnd.Rannyu();
                double b = rnd.Rannyu();
                double c = pow(pow(a, 2) + pow(b, 2), 0.5);
                if(b == 0) {
                    theta = 0;
                    break;
                } else if(c < 1) {
                    theta = atan(a/b);
                    break;
                }
            }

            double x0 = d * rnd.Rannyu(); // Random distance from the origin to the needle's midpoint
            double x = L * cos(theta); // Horizontal component of the needle's length
            double distance = x + x0; // Distance to the line

            if(distance >= d) N_hit += 1; // Check if the needle intersects a line
        }

        // Estimate π using the formula π = (2 * L * m) / (N_hit * d)
        double pi = (2 * L * m) / (N_hit * d);
        pi_values.push_back(pi);
        pi_values2.push_back(pi * pi);
    }

    std::vector<double> sum_prog; // Vector to store progressive averages of π estimates

    for(size_t i{}; i < n_block; i++) {
        double sum{};
        double sum2{};

        for(size_t j{}; j < i + 1; j++) {
            sum += pi_values[j];
            sum2 += pi_values2[j];
        }

        sum /= (i + 1); // Calculate the progressive average
        sum2 /= (i + 1); // Calculate the progressive squared average

        sum_prog.push_back(sum);
        v_devstd.push_back(error(sum, sum2, i)); // Calculate and store the standard deviation
    }

    // Save the results to files
    printToFile("OUTPUT/es3_PiValues.txt", sum_prog);
    printToFile("OUTPUT/es3_Error.txt", v_devstd);

    std::cerr << " ---> 3 files saved :) \n";
    return 0;
}