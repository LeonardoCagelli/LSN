#pragma once
#include<iostream>
#include<functional>
#include<vector>
#include<string>
#include<tuple>
#include"random.h"

using History = std::vector<std::tuple<std::vector<double>, std::tuple<double, double>>>;

class Trial_Function {

    private:
        double _mu, _sigma;
    
    public:

        double Get_Mu() const;
        double Get_Sigma() const;
        void Set_Mu(double mean);
        void Set_Sigma(double sigma); 
        std::vector<double> GetParams() const;

        Trial_Function();
        Trial_Function(double mean, double sigma);

        // Evaluation of function
        double Eval(double x) const;  

        // Square module of the function
        double Eval_Square(double x) const;

        // Compute first derivative of the function 
        double First_Derivative(double x) const;

        // Compute second derivative of the function 
        double Second_Derivative(double x) const;
};


class Hamiltonian {

    private:    
        double _h = 1;  // Plank constant
        double _m = 1;  // Mass 
        std::function<double(double)> _V;   // Potential energy

    public: 
        Hamiltonian();
        Hamiltonian(const std::function<double(double)>& V);


        double Eval(double x, const Trial_Function& func) const;
};


class Optimizer{

    private:
        
        double _x0;
        // Metropolis delta 
        double _delta;
        // Number of blocks for simulated annealing
        double _blocks;
        // Number of steps for simulated annealing
        double _nstep;
        // Number of quilibration steps
        double _eq_step = 10000;
        // Starting temperature
        double _T0;
        // Temporary temperature
        double _T;
        // Weights for simulated annealing metropolis step
        double _K1 = 2.0, _K2 = 2.0;
        double _best_energy = 1;
        double _best_error = 0;
        double _energy = 1;
        double _error = 0;
        std::vector<double> _best_params;
        // Vector containing history of the training process
        History _history;
        Trial_Function _f;
        Hamiltonian _H;
        size_t _n_iteration = 0;
        size_t _n_accepted = 0;

        // Compute error in data blocking
        double ComputeError(double a, double b, size_t i);

    public:

        Optimizer(double x0, double delta, double _blocks, double step, double T, const Trial_Function& f , const Hamiltonian& H);
        Optimizer(double blocks, double steps, double T, const Trial_Function& f , const Hamiltonian& H);
        double GetTemperature() const;
        void SetTemperature(double T); 
        size_t GetIterations() const;
        double GetAcceptance() const;

        // Return the optimized parameters
        std::vector<double> GetBestParam() const;

        // Return the training history
        History GetHistory() const;

        // Perform metropolis for samlping f trial
        double MetropolisStep(Random& rnd, double x, double delta, size_t& iteration, size_t& accepted);

        // Use metropolis algorithm to explore the parameters space
        bool SimulatedAnnealingMetropolis(Random& rnd);

        // Perform simulated annealing optimization algorithm
        void SimulatedAnnealing(Random& rnd, bool history);

};