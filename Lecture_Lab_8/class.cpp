#include"class.h"

double Trial_Function::Get_Mu() const { return _mu; }

double Trial_Function::Get_Sigma() const { return _sigma; }

void Trial_Function::Set_Mu(double mean) { _mu = mean; }

void Trial_Function::Set_Sigma(double sigma) { _sigma = sigma; }

// Return a vector containing the function trainable parameters 
std::vector<double> Trial_Function::GetParams() const {
    std::vector<double> params;
    params.push_back(_mu);
    params.push_back(_sigma);
    return params;
}

Trial_Function::Trial_Function() : _mu{0}, _sigma{1} {}

Trial_Function::Trial_Function(double mean, double sigma) : _mu{mean}, _sigma{sigma} {}

double Trial_Function::Eval(double x) const {
    return exp(-pow(x - _mu, 2) / (2 * _sigma * _sigma)) + exp(-pow(x + _mu, 2) / (2 * _sigma * _sigma));
}   

// Square module of the function
double Trial_Function::Eval_Square(double x) const {
    return pow(abs(Eval(x)), 2);
}

// Compute first derivative of the function 
double Trial_Function::First_Derivative(double x) const {
    return -((x - _mu) / (_sigma * _sigma)) * exp(-pow(x - _mu, 2) / (2 * _sigma * _sigma)) - 
                ((x + _mu) / (_sigma * _sigma)) * exp(-pow(x + _mu, 2) / (2 * _sigma * _sigma));
}

// Compute second derivative of the function 
double Trial_Function::Second_Derivative(double x) const {
    double e1 = exp(-pow(x - _mu, 2) / (2 * _sigma * _sigma));
    double e2 = exp(-pow(x + _mu, 2) / (2 * _sigma * _sigma));
    return e1 * (pow(x - _mu, 2) / pow(_sigma, 4) - pow(_sigma, - 2)) + 
            e2 * (pow(x + _mu, 2) / pow(_sigma, 4) - pow(_sigma, - 2));
}

Hamiltonian::Hamiltonian(){
    _V = [](double x){ return pow(x, 4) - (5.0/2.0) * pow(x, 2); }; 
}

Hamiltonian::Hamiltonian(const std::function<double(double)>& V){
    _V = V; 
}

double Hamiltonian::Eval(double x, const Trial_Function& func) const {
    return - ((_h / (2 * _m)) * func.Second_Derivative(x)) / func.Eval(x) + _V(x);
}


double Optimizer::GetTemperature() const {
    return _T;
}
void Optimizer::SetTemperature(double T) {
    _T = T;
}

size_t Optimizer::GetIterations() const {
    return _n_iteration;
}

double Optimizer::GetAcceptance() const {
    return _n_accepted / double(_n_iteration);
}

// Compute error in data blocking
double Optimizer::ComputeError(double a, double b, size_t i){
    if(i < 2) return 0;
    else{
        return sqrt((b - pow(a, 2)) / double(i - 1));
    }
}

// Return the optimized parameters
std::vector<double> Optimizer::GetBestParam() const {
    return _best_params;
}

// Return training history
History Optimizer::GetHistory() const {
    return _history;
}

Optimizer::Optimizer(double x0, double delta, double blocks, double step, double T, const Trial_Function& f , const Hamiltonian& H) : 
        _x0{x0}, _delta{delta}, _nstep{step}, _blocks{blocks}, _T{T}, _T0{T}, _f{f}, _H{H} {}

Optimizer::Optimizer(double blocks, double steps, double T, const Trial_Function& f , const Hamiltonian& H) : 
        _x0{0}, _delta{1}, _T{T}, _T0{T}, _f{f}, _H{H}, _blocks{100}, _nstep{1000} {
        
    std::cout<<"X0: "<<_x0<<"\n";
    std::cout<<"delta: "<<_delta<<"\n";
    std::cout<<"T: "<<_T<<"\n";
    std::cout<<"T0: "<<_T0<<"\n";
    std::cout<<"iterations: "<<_n_iteration<<"\n";
    std::cout<<"accepted: "<<_n_accepted<<"\n";
    std::cout<<"equilibration steps: "<<_eq_step<<"\n";
    std::cout<<"best energy: "<<_best_energy<<"\n";
    std::cout<<"best_error: "<<_best_error<<"\n";
    std::cout<<"energy: "<<_energy<<"\n";
    std::cout<<"error: "<<_error<<"\n";
    std::cout<<"steps: "<<_nstep<<"\n";
    std::cout<<"blocks: "<<_blocks<<"\n";

}

// Perform metropolis for samlping f trial
double Optimizer::MetropolisStep(Random& rnd, double x, double delta, size_t& iteration, size_t& accepted){
    double x_new = x + delta * rnd.Rannyu(-1, 1);
    double acceptance = _f.Eval_Square(x_new) / _f.Eval_Square(x);
    if(rnd.Rannyu() < acceptance){
        accepted++;
        x = x_new;
    }

    iteration++;
    return x;
}

// Metropolis algorithm to explore the parameters space
bool Optimizer::SimulatedAnnealingMetropolis(Random& rnd){
    bool check = false;
    double old_mu = _f.Get_Mu();
    double old_sigma = _f.Get_Sigma();
    // Proposed moves
    double new_mu = abs(_f.Get_Mu() + _delta * rnd.Rannyu(-1, 1) * _K1 * _T);
    double new_sigma = abs(_f.Get_Sigma() + _delta * rnd.Rannyu(-1, 1) * _K2 * _T);

    _f.Set_Mu(new_mu);
    _f.Set_Sigma(new_sigma);

    size_t iterations{};
    size_t accepted{};
    double x = _x0;
    double Energy{};
    double Energy_2{};
    double Error;

    // Equilibration stes
    for(size_t i{};i<_eq_step;i++) x = MetropolisStep(rnd, x, 2.0 * _T, iterations, accepted);

    // Sampling steps
    for(size_t i{};i<_blocks;i++){

        iterations = 0;
        accepted = 0;
        double temp{};

        // Compute hamiltonian mean value
        for(size_t j{};j<_nstep;j++){
            x = MetropolisStep(rnd, x, 2.0, iterations, accepted);
            temp += _H.Eval(x, _f);
        }

        // Data blocking
        temp /= _nstep;
        Energy += temp; //((Energy * i) + temp) / (i+1);
        Energy_2 += pow(temp, 2); //((Energy_2 * i) + pow(Energy, 2)) / (i+1);
    }
    
    Error = ComputeError(Energy / _blocks, Energy_2 / _blocks, _blocks);
    Energy /= _blocks;
    Energy_2 /= _blocks;

    double acceptance = std::min(exp(- (1 / _T) * (Energy - _energy)), 1.0);        //Kb  = 1
    if(rnd.Rannyu() < acceptance){
        check = true;
        _energy = Energy;
        _error = Error;
    } else {
        _f.Set_Mu(old_mu);
        _f.Set_Sigma(old_sigma); 
    }

    if(_energy < _best_energy){
        _best_energy = _energy;
        _best_error = _error;
        _best_params = _f.GetParams();
    }

    return check;
}

// Perform simulated annealing optimization algorithm
void Optimizer::SimulatedAnnealing(Random& rnd, bool history = false) {
    // Prepare the history vector
    if(history) _history.clear();

    _T = _T0;
    _n_iteration = 0;
    _n_accepted = 0;

    _best_energy = _energy;
    _best_params = _f.GetParams();
    while(_T > 0.01){
        bool check = SimulatedAnnealingMetropolis(rnd);
        if(check) _n_accepted++;
        _n_iteration++;
        _T = _T * 0.995;

        if(history){
            auto param = _f.GetParams();
            auto tuple = std::make_tuple(_energy, _error);
            auto element = std::make_tuple(param, tuple);
            _history.push_back(element);
        }
    }
}
