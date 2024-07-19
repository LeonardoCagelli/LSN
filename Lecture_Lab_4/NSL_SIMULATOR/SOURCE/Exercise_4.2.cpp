#include <iostream>
#include <chrono>
#include "system.h"
#include "function.h"

using namespace std;

int main (int argc, char *argv[]) {

    System SYS;

    // ===================
    // Solid configuration
    // ===================

    std::cerr << "Solid simulation started!\n";

    // Record the start time of the solid simulation
    auto start = std::chrono::high_resolution_clock::now();

    // Set input and output paths for the solid configuration
    SYS.setInputPath("../ES4/Solid/INPUT/");
    SYS.setOutputPath("../ES4/Solid/OUTPUT/");
    SYS.printPath();
    SYS.initialize();
    SYS.initialize_properties();

    // Steps to reach equilibrium for solid configuration
    for (size_t i{}; i < 5000; i++) SYS.step(); // T0 = 1.55

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

    // ====================
    // Liquid configuration
    // ====================

    std::cerr << "Liquid simulation starts!\n";
    start = std::chrono::high_resolution_clock::now();

    // Set input and output paths for the liquid configuration
    SYS.setInputPath("../ES4/Liquid/INPUT/");
    SYS.setOutputPath("../ES4/Liquid/OUTPUT/");
    SYS.printPath();
    SYS.initialize();
    SYS.initialize_properties();

    // Steps to reach equilibrium for liquid configuration
    for (size_t i{}; i < 30000; i++) SYS.step(); // T0 = 1.99

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

    // Record the end time and calculate the duration of the liquid simulation
    end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::seconds>(end - start);
    std::cerr << "Simulation ended!\nTime of execution: " << duration.count() << "s\n\n";

    // =================
    // Gas configuration
    // =================

    std::cerr << "Gas simulation starts!\n";
    start = std::chrono::high_resolution_clock::now();

    // Set input and output paths for the gas configuration
    SYS.setInputPath("../ES4/Gas/INPUT/");
    SYS.setOutputPath("../ES4/Gas/OUTPUT/");
    SYS.printPath();
    SYS.initialize();
    SYS.initialize_properties();

    // Steps to reach equilibrium for gas configuration
    for (size_t i{}; i < 60000; i++) SYS.step(); // T0 = 0.97

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

    // Record the end time and calculate the duration of the gas simulation
    end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::seconds>(end - start);
    std::cerr << "Simulation ended!\nTime of execution: " << duration.count() << "s\n\n";

    return 0;
}
