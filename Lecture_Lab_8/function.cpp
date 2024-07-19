#include"function.h"


// Compute the error in data blocking 
double error(double a, double b, size_t i){
    if(i < 2) return 0;
    else{
        return sqrt((b - pow(a, 2)) / double(i - 1));
    }
}

// Perform a metropolis step 
double MetropoliStep(const Trial_Function& func, Random& rnd, double x, double delta, size_t& iteration, size_t& accepted){
    double x_new = x + delta * rnd.Rannyu(-1, 1);
    double acceptance = func.Eval_Square(x_new) / func.Eval_Square(x);
    if(rnd.Rannyu() < acceptance){
        accepted++;
        x = x_new;
    }

    iteration++;
    return x;
}

// Save training history to file
void SaveHistory(const std::string& param_path, const std::string& energy_path, const History& history){
    std::ofstream out(param_path);
    std::ofstream out2(energy_path);

    out<<"Parameters:\n";
    out2<<"Energy   Error\n";
    for(const auto line : history){
        // Get parameters
        auto params = std::get<0>(line);
        for(const auto param : params){
            out<<param<< " ";
        }
        out<<"\n";

        auto energy = std::get<1>(line);
        out2<<std::get<0>(energy)<<"         "<<std::get<1>(energy)<<"\n";
    }

    out.close();
    out2.close();
}