#include <iostream>
#include <chrono>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "system.h"
#include "function.h"

using namespace std;

int main() {

    // ===================
    // Solid configuration
    // ===================

    // Initialize temperature for solid configuration
    double temperature = 1.3;
    std::cerr << "Solid equilibration started!\n"; // Log the start of the solid equilibration process
    auto start = std::chrono::high_resolution_clock::now(); // Start the timer for the process

    // Loop over 6 temperature cycles
    for (size_t t{}; t < 6; t++) {
        System SYS; // Create a System object

        // Set input and output paths
        SYS.setInputPath("../ES4/Equilibration/Solid/INPUT/");
        SYS.setOutputPath("../ES4/Equilibration/Solid/OUTPUT/");
        SYS.setTemperaturePath("temperature_" + std::to_string(temperature) + ".dat");

        // Initialize the system and its properties
        SYS.initialize();
        SYS.initialize_properties();
        SYS.block_reset(0); // Reset block measurements

        // Loop over blocks
        for (int i = 0; i < SYS.get_nbl(); i++) {
            // Loop over steps in a block
            for (int j = 0; j < SYS.get_nsteps(); j++) {
                SYS.step(); // Perform a simulation step
                SYS.measure(); // Measure properties
            }
            SYS.averages(i + 1); // Calculate averages for the block
            SYS.block_reset(i + 1); // Reset block for the next set of measurements
        }

        SYS.finalize(); // Finalize the system for the current temperature
        std::cerr << "Cycle with temperature " << temperature << " ended\n"; // Log the end of the current cycle
        temperature += 0.1; // Increment temperature for the next cycle
        modifyProperty("../ES4/Equilibration/Solid/INPUT/input.dat", temperature, "TEMP"); // Update the temperature in the input file
    }

    auto end = std::chrono::high_resolution_clock::now(); // End the timer
    auto duration = std::chrono::duration_cast<std::chrono::seconds>(end - start); // Calculate the duration of the process
    std::cerr << "Solid equilibration ended!\nTime of execution: " << duration.count() << "s\n\n"; // Log the end of the solid equilibration process and its duration


    // ====================
    // Liquid configuration
    // ====================

    // Initialize temperature for liquid configuration
    temperature = 1.6;
    std::cerr << "Liquid equilibration started!\n"; // Log the start of the liquid equilibration process
    start = std::chrono::high_resolution_clock::now(); // Start the timer for the process

    // Loop over 6 temperature cycles
    for (size_t t{}; t < 6; t++) {
        System SYS; // Create a System object

        // Set input and output paths
        SYS.setInputPath("../ES4/Equilibration/Liquid/INPUT/");
        SYS.setOutputPath("../ES4/Equilibration/Liquid/OUTPUT/");
        SYS.setTemperaturePath("temperature_" + std::to_string(temperature) + ".dat");

        // Initialize the system and its properties
        SYS.initialize();
        SYS.initialize_properties();
        SYS.block_reset(0); // Reset block measurements

        // Loop over blocks
        for (int i = 0; i < SYS.get_nbl(); i++) {
            // Loop over steps in a block
            for (int j = 0; j < SYS.get_nsteps(); j++) {
                SYS.step(); // Perform a simulation step
                SYS.measure(); // Measure properties
            }
            SYS.averages(i + 1); // Calculate averages for the block
            SYS.block_reset(i + 1); // Reset block for the next set of measurements
        }

        SYS.finalize(); // Finalize the system for the current temperature
        std::cerr << "Cycle with temperature " << temperature << " ended\n"; // Log the end of the current cycle
        temperature += 0.1; // Increment temperature for the next cycle
        modifyProperty("../ES4/Equilibration/Liquid/INPUT/input.dat", temperature, "TEMP"); // Update the temperature in the input file
    }

    end = std::chrono::high_resolution_clock::now(); // End the timer
    duration = std::chrono::duration_cast<std::chrono::seconds>(end - start); // Calculate the duration of the process
    std::cerr << "Liquid equilibration ended!\nTime of execution: " << duration.count() << "s\n\n"; // Log the end of the liquid equilibration process and its duration


    // =================
    // Gas configuration
    // =================

    // Initialize temperature for gas configuration
    temperature = 0.6;
    std::cerr << "Gas equilibration started!\n"; // Log the start of the gas equilibration process
    start = std::chrono::high_resolution_clock::now(); // Start the timer for the process

    // Loop over 6 temperature cycles
    for (size_t t{}; t < 6; t++) {
        System SYS; // Create a System object

        // Set input and output paths
        SYS.setInputPath("../ES4/Equilibration/Gas/INPUT/");
        SYS.setOutputPath("../ES4/Equilibration/Gas/OUTPUT/");
        SYS.setTemperaturePath("temperature_" + std::to_string(temperature) + ".dat");

        // Initialize the system and its properties
        SYS.initialize();
        SYS.initialize_properties();
        SYS.block_reset(0); // Reset block measurements

        // Loop over blocks
        for (int i = 0; i < SYS.get_nbl(); i++) {
            // Loop over steps in a block
            for (int j = 0; j < SYS.get_nsteps(); j++) {
                SYS.step(); // Perform a simulation step
                SYS.measure(); // Measure properties
            }
            SYS.averages(i + 1); // Calculate averages for the block
            SYS.block_reset(i + 1); // Reset block for the next set of measurements
        }

        SYS.finalize(); // Finalize the system for the current temperature
        std::cerr << "Cycle with temperature " << temperature << " ended\n"; // Log the end of the current cycle
        temperature += 0.1; // Increment temperature for the next cycle
        modifyProperty("../ES4/Equilibration/Gas/INPUT/input.dat", temperature, "TEMP"); // Update the temperature in the input file
    }

    end = std::chrono::high_resolution_clock::now(); // End the timer
    duration = std::chrono::duration_cast<std::chrono::seconds>(end - start); // Calculate the duration of the process
    std::cerr << "Gas equilibration ended!\nTime of execution: " << duration.count() << "s\n\n"; // Log the end of the gas equilibration process and its duration

    return 0; // Return 0 to indicate successful execution
}
