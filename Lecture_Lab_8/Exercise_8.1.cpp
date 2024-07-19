#include<iostream>
#include<vector>
#include<fstream>
#include"random.h"
#include"class.h"
#include"function.h"



int main(){

    Random rnd;
    rnd.Initialization();

    size_t N = 100000;
    size_t n_blocks = 100;
    size_t steps = (N / n_blocks);
    size_t n_eq = 10000;

    // Define the trial function with mu and sigma values
    Trial_Function f_trial(0, 1);
    Hamiltonian H;

    std::vector<double> H_vec(n_blocks);
    std::vector<double> Err_vec(n_blocks);
    std::vector<double> Accept_vec(n_blocks);
    std::vector<double> x_vec;

    double sum{};
    double sum_2{};

    size_t n_iterations{};
    size_t n_accepted{};
    double x = 0;

    // Equilibration steps
    for(size_t i{};i<n_eq;i++) x = MetropoliStep(f_trial, rnd, x, 2.0, n_iterations, n_accepted);

    // Sampling loops
    for(size_t i{};i<n_blocks;i++){

        n_iterations = 0;
        n_accepted = 0;
        double temp{};

        for(size_t j{};j<steps;j++){
            x = MetropoliStep(f_trial, rnd, x, 2.0, n_iterations, n_accepted);
            temp += H.Eval(x, f_trial);
            x_vec.push_back(x);
        }

        temp /= steps;
        sum += temp;
        sum_2 += pow(temp, 2);
        H_vec[i] = (sum / (i+1));
        Err_vec[i] = error(sum / (i+1), sum_2 / (i+1), i+1);
        Accept_vec[i] = n_accepted / double(n_iterations);
    }

    // Save to file 
    std::ofstream out("OUTPUT/8.1/History.txt");
    out << "Energy" << std::setw(20) << "Error" << std::setw(20) << "Acceptance" << "\n";
    for(size_t i{};i<n_blocks;i++){
        out << H_vec[i] << std::setw(20) << Err_vec[i] << std::setw(20) << Accept_vec[i] << "\n";
    }
    out.close();

    out.open("OUTPUT/8.1/Points.txt");
    for(size_t i{};i<x_vec.size();i++) out << x_vec[i] << "\n";
    out.close();

    return 0;
}

