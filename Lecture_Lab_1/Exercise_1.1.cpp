#include<iostream>
#include<vector>
#include<cmath>
#include"random.h"
#include"function.h"

int main(){
    Random rnd;
    rnd.Initialization();

    size_t N{100000}; // Total number of random numbers to generate
    size_t m{500}; // Number of random numbers per block
    size_t n_Blocks{N / m}; // Number of blocks

    std::vector<double> v_avg; // Vector to store average of each block
    std::vector<double> v_avg2; // Vector to store squared average of each block
    std::vector<double> v_devstd; // Vector to store standard deviation of each block

    for(size_t i{}; i < n_Blocks; i++) {
        double sum{}; // Sum of random numbers in the current block

        for(size_t j{}; j < m; j++) sum += rnd.Rannyu(); // Generate m random numbers and sum them

        v_avg.push_back(sum / m); // Calculate the average for the current block and store it
        v_avg2.push_back(pow(sum / m, 2)); // Store the square of the average for variance calculation
    }

    std::vector<double> sum_prog; // Vector to store progressive sum of averages

    for(size_t i{}; i < n_Blocks; i++) {
        double sum{}; // Sum of averages up to the i-th block
        double sum2{}; // Sum of squared averages up to the i-th block

        for(size_t j{}; j < i + 1; j++) {
            sum += v_avg[j]; // Sum of averages up to the current block
            sum2 += v_avg2[j]; // Sum of squared averages up to the current block
        }

        sum /= (i + 1); // Calculate the progressive average
        sum2 /= (i + 1); // Calculate the progressive squared average

        sum_prog.push_back(sum); // Store the progressive average
        v_devstd.push_back(error(sum, sum2, i+1)); // Calculate and store the standard deviation
    }

    // Save the results to files
    printToFile("OUTPUT/es1_1_mean.txt", sum_prog);
    printToFile("OUTPUT/es1_1_devstd.txt", v_devstd);

    // Chi2 Test

    N = 10000; // Number of throws
    size_t M{100}; // Number of intervals
    size_t n{10000}; // Measurements
    std::vector<double> v_chi2(n);

    for(size_t i{};i<n;i++){
        std::vector<size_t> v_bins(M, 0);
        for(size_t j{};j<N;j++){
            double r = rnd.Rannyu();
            size_t index = static_cast<size_t>(r * M);
            v_bins[index]++;
        }
        double chi2 = ComputeChi2(v_bins, N/double(M), M);
        v_chi2[i] = chi2;
    }

    printToFile("OUTPUT/es1_Chi2.txt", v_chi2);
    std::cerr << " ---> 1.1 files saved :) \n";

    return 0;
}
