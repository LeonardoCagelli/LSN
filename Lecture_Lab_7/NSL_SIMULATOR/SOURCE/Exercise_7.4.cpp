#include <iostream>
#include <chrono>
#include "system.h"
#include "function.h"

using namespace std;

int main (int argc, char *argv[]) {

    System SYS;

    std::vector<std::string> types{"MC", "MD"};
    std::vector<std::string> phases{"Gas", "Liquid", "Solid"};

    for(const auto& type : types){
        for(const auto& phase : phases){

            auto input_path = "../Exercise_7.4/" + type + "/" + phase + "/INPUT/";
            auto output_path = "../Exercise_7.4/" + type + "/" + phase + "/OUTPUT/";

            std::cerr << type << " " << phase << " simulation started!\n";

            auto start = std::chrono::high_resolution_clock::now();

            // Set input and output paths
            SYS.setInputPath(input_path);
            SYS.setOutputPath(output_path);
            SYS.initialize();
            SYS.initialize_properties();

            // Steps to reach equilibrium
            if(type == "MC"){
                for (size_t i{}; i < 10000; i++) SYS.step();
            } else { // MD
                if(phase == "Gas"){
                    for (size_t i{}; i < 60000; i++) SYS.step();
                } else if(phase == "Liquid"){
                    for (size_t i{}; i < 30000; i++) SYS.step();
                } else { // Solid
                    for (size_t i{}; i < 5000; i++) SYS.step();
                }
            }
            
            SYS.block_reset(0);

            // Loop over blocks and steps for measurement
            for (int i = 0; i < SYS.get_nbl(); i++) { // loop over blocks
                for (int j = 0; j < SYS.get_nsteps(); j++) { // loop over steps in a block
                    SYS.step();
                    SYS.measure();
                }
                SYS.averages(i + 1);
                SYS.block_reset(i + 1);
            }

            SYS.finalize();

            auto end = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::seconds>(end - start);
            std::cerr << "Simulation ended!\nTime of execution: " << duration.count() << "s\n\n";

        }
    }

    return 0;
}
