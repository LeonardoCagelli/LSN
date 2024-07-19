#include"random.h"
#include<iostream>
#include<functional>
#include<vector>
#include"class.h"
#include"function.h"

int main(){
                       
    // Initialize the random number generator
    Random rnd;
    rnd.Initialization();

    // Parameters for the simulation
    size_t n_throws{10000}; // Total number of throws/simulations
    size_t n_blocks{100};   // Number of blocks for averaging
    size_t n_steps{100};    // Number of steps in each random walk
    size_t m{n_throws / n_blocks}; // Number of throws per block

    // Create instances of the random walk classes
    DiscreteRandomWalk3D D_RW(rnd, n_steps, 0, 0, 0, 1); // Discrete random walk starting at origin with lattice 1
    ContinuousRandomWalk3D C_RW(rnd, n_steps, 0.0, 0.0, 0.0, 1.0); // Continuous random walk starting at origin with lattice 1.0

    // Matrices to store results
    std::vector<std::vector<double>> Mat_C_RW; // Matrix for storing results of continuous random walk
    std::vector<std::vector<double>> Mat_D_RW; // Matrix for storing results of discrete random walk

    // Loop over blocks
    for(size_t i{}; i < n_blocks; i++){

        // Vectors to store values for current block
        std::vector<double> v_D_RW(n_steps, 0); // Vector for discrete random walk values
        std::vector<double> v_C_RW(n_steps, 0); // Vector for continuous random walk values

        // Loop over throws in current block
        for(size_t j{}; j < m; j++){

            // Run simulations and save history of positions
            auto d_history = D_RW.runSimulation(n_steps, true);
            auto c_history = C_RW.runSimulation(n_steps, true);

            // Compute norms and accumulate values
            for(size_t k{}; k < d_history.size(); k++){
                double r_c = Norm(c_history[k]); // Norm of position in continuous random walk
                double r_d = Norm(d_history[k]); // Norm of position in discrete random walk
                v_C_RW[k] += r_c; // Accumulate norm in continuous random walk vector
                v_D_RW[k] += r_d; // Accumulate norm in discrete random walk vector
            }
        }

        // Normalize accumulated values for the current block
        Normalize(v_D_RW, m);
        Normalize(v_C_RW, m);

        // Store normalized values in matrices
        Mat_C_RW.push_back(v_C_RW);
        Mat_D_RW.push_back(v_D_RW);
    }

    // Vectors to store averaged values and errors
    std::vector<double> Avg_D_RW; // Vector for averaged values of discrete random walk
    std::vector<double> Avg_C_RW; // Vector for averaged values of continuous random walk
    std::vector<double> Error_D_RW; // Vector for errors of discrete random walk
    std::vector<double> Error_C_RW; // Vector for errors of continuous random walk

    // Loop over steps to compute averages and errors
    for(size_t i{}; i < n_steps; i++){

        double sum_d{}; // Sum of normalized values for discrete random walk
        double sum_d_2{}; // Sum of squared normalized values for discrete random walk

        double sum_c{}; // Sum of normalized values for continuous random walk
        double sum_c_2{}; // Sum of squared normalized values for continuous random walk

        // Loop over blocks to accumulate values for current step
        for(size_t j{}; j < Mat_D_RW.size(); j++){

            sum_d += Mat_D_RW[j][i]; // Accumulate value for discrete random walk
            sum_d_2 += pow(Mat_D_RW[j][i], 2); // Accumulate squared value for discrete random walk

            sum_c += Mat_C_RW[j][i]; // Accumulate value for continuous random walk
            sum_c_2 += pow(Mat_C_RW[j][i], 2); // Accumulate squared value for continuous random walk
        }

        // Compute averages for current step
        sum_d /= n_blocks;
        sum_c /= n_blocks;

        // Compute errors for current step
        sum_d_2 /= n_blocks;
        sum_c_2 /= n_blocks;
        double error_d = sum_d_2 - pow(sum_d, 2); // Error for discrete random walk
        double error_c = sum_c_2 - pow(sum_c, 2); // Error for continuous random walk

        // Store averaged values and errors in vectors
        Avg_D_RW.push_back(sum_d);
        Avg_C_RW.push_back(sum_c);
        Error_D_RW.push_back(error_d);
        Error_C_RW.push_back(error_c);
    }

    // Print averaged values and errors to output files
    printToFile("OUTPUT/es2_Avg_D.txt", Avg_D_RW);
    printToFile("OUTPUT/es2_Avg_C.txt", Avg_C_RW);
    printToFile("OUTPUT/es2_Error_D.txt", Error_D_RW);
    printToFile("OUTPUT/es2_Error_C.txt", Error_C_RW);

    return 0;
}
