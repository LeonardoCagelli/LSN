#include <iostream>
#include <chrono>
#include "system.h"
#include "function.h"

using namespace std;

int main (int argc, char *argv[]) {
    // It takes about 25 min
    System SYS;

    std::vector<std::string> phases{"Gas", "Liquid", "Solid"};
    for(const auto& phase : phases){

        std::cerr << phase << " simulation started!\n";

        // Record the start time of the solid simulation
        auto start = std::chrono::high_resolution_clock::now();

        auto input_path = "../Exercise_7.2/" + phase + "/INPUT/";
        auto output_path = "../Exercise_7.2/" + phase + "/OUTPUT/";

        // Set input and output paths for the solid configuration
        SYS.setInputPath(input_path);
        SYS.setOutputPath(output_path);
        SYS.initialize();
        SYS.initialize_properties();

        // Steps to reach equilibrium for solid configuration
        for (size_t i{}; i < 10000; i++) SYS.step();
        
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

        // Record the end time and calculate the duration of the solid simulation
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::seconds>(end - start);
        std::cerr << "Simulation ended!\nTime of execution: " << duration.count() << "s\n\n";

    }



    // // ===================
    // // Solid configuration
    // // ===================

    // std::cerr << "Solid simulation started!\n";

    // // Record the start time of the solid simulation
    // auto start = std::chrono::high_resolution_clock::now();

    // // Set input and output paths for the solid configuration
    // SYS.setInputPath("../Exercise_7.2/Solid/INPUT/");
    // SYS.setOutputPath("../Exercise_7.2/Solid/OUTPUT/");
    // SYS.initialize();
    // SYS.initialize_properties();

    // // Steps to reach equilibrium for solid configuration
    // for (size_t i{}; i < 10000; i++) SYS.step();
    
    // SYS.block_reset(0);

    // // Loop over blocks and steps for measurement
    // for (int i = 0; i < SYS.get_nbl(); i++) { // loop over blocks
    //     for (int j = 0; j < SYS.get_nsteps(); j++) { // loop over steps in a block
    //         SYS.step();
    //         SYS.measure();
    //     }
    //     SYS.averages(i + 1);
    //     SYS.block_reset(i + 1);
    // }

    // SYS.finalize();
    // renameFile("../Exercise_7.2/Solid/OUTPUT/", "potential_energy.dat", "potential_energy_500000.dat");

    // // Record the end time and calculate the duration of the solid simulation
    // auto end = std::chrono::high_resolution_clock::now();
    // auto duration = std::chrono::duration_cast<std::chrono::seconds>(end - start);
    // std::cerr << "Simulation ended!\nTime of execution: " << duration.count() << "s\n\n";

    // // ====================
    // // Liquid configuration
    // // ====================

    // std::cerr << "Liquid simulation started!\n";
    // start = std::chrono::high_resolution_clock::now();

    // // Set input and output paths for the liquid configuration
    // SYS.setInputPath("../Exercise_7.2/Liquid/INPUT/");
    // SYS.setOutputPath("../Exercise_7.2/Liquid/OUTPUT/");
    // SYS.initialize();
    // SYS.initialize_properties();

    // // Steps to reach equilibrium for liquid configuration
    // for (size_t i{}; i < 10000; i++) SYS.step();

    // SYS.block_reset(0);

    // // Loop over blocks and steps for measurement
    // for (int i = 0; i < SYS.get_nbl(); i++) { // loop over blocks
    //     for (int j = 0; j < SYS.get_nsteps(); j++) { // loop over steps in a block
    //         SYS.step();
    //         SYS.measure();
    //     }
    //     SYS.averages(i + 1);
    //     SYS.block_reset(i + 1);
    // }

    // SYS.finalize();
    // renameFile("../Exercise_7.2/Liquid/OUTPUT/", "potential_energy.dat", "potential_energy_500000.dat");

    // // Record the end time and calculate the duration of the liquid simulation
    // end = std::chrono::high_resolution_clock::now();
    // duration = std::chrono::duration_cast<std::chrono::seconds>(end - start);
    // std::cerr << "Simulation ended!\nTime of execution: " << duration.count() << "s\n\n";

    // // =================
    // // Gas configuration
    // // =================

    // std::cerr << "Gas simulation started!\n";
    // start = std::chrono::high_resolution_clock::now();

    // // Set input and output paths for the gas configuration
    // SYS.setInputPath("../Exercise_7.2/Gas/INPUT/");
    // SYS.setOutputPath("../Exercise_7.2/Gas/OUTPUT/");
    // SYS.initialize();
    // SYS.initialize_properties();

    // // Steps to reach equilibrium for gas configuration
    // for (size_t i{}; i < 10000; i++) SYS.step();

    // SYS.block_reset(0);

    // // Loop over blocks and steps for measurement
    // for (int i = 0; i < SYS.get_nbl(); i++) { // loop over blocks
    //     for (int j = 0; j < SYS.get_nsteps(); j++) { // loop over steps in a block
    //         SYS.step();
    //         SYS.measure();
    //     }
    //     SYS.averages(i + 1);
    //     SYS.block_reset(i + 1);
    // }

    // SYS.finalize();
    // renameFile("../Exercise_7.2/Gas/OUTPUT/", "potential_energy.dat", "potential_energy_500000.dat");

    // // Record the end time and calculate the duration of the gas simulation
    // end = std::chrono::high_resolution_clock::now();
    // duration = std::chrono::duration_cast<std::chrono::seconds>(end - start);
    // std::cerr << "Simulation ended!\nTime of execution: " << duration.count() << "s\n\n";

    return 0;
}
