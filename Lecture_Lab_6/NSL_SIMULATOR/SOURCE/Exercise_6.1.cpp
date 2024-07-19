#include <iostream>
#include<chrono>
#include<cstdio>
#include<filesystem>
#include "system.h"
#include"function.h"

int main(){

    // Print the start message for the simulation
    std::cerr << "Ising model simulation started!\n";
    
    // Record the start time of the simulation
    auto start = std::chrono::high_resolution_clock::now();

    // Define vectors for temperatures, simulation types, and magnetic field values
    std::vector<double> v_temp{0.5, 0.75, 1.0, 1.25, 1.5, 1.75, 2.0};
    std::vector<int> sim_type{2, 3};
    std::vector<double> v_h{0.0, 0.02};

    // Initialize the system and set input/output paths
    System SYS;
    SYS.setInputPath("../INPUT/");
    SYS.setOutputPath("../OUTPUT/");

    // Loop over different magnetic field values
    for(auto h : v_h){

        // Modify the simulation type property in the input file
        modifyProperty("../INPUT/input.dat", h, "SIMULATION_TYPE", 3);

        // Loop over different simulation types
        for(auto type : sim_type){
            std::string sim_name = (type == 2 ? "MRT2_" : "GIBBS_");
            
            // Modify the simulation type in the input file
            modifyProperty("../INPUT/input.dat", type, "SIMULATION_TYPE", 1);

            // Loop over different temperatures
            for(double temp : v_temp){
                modifyProperty("../INPUT/input.dat", temp, "TEMP");

                // Initialize the system and properties
                SYS.initialize();
                SYS.initialize_properties();
                SYS.block_reset(0);

                // Perform equilibration steps
                for(size_t eq{}; eq < 100000; eq++) SYS.step();

                // Perform measurements
                for(int i = 0; i < SYS.get_nbl(); i++){ // Loop over blocks
                    for(int j = 0; j < SYS.get_nsteps(); j++){ // Loop over steps in a block
                        SYS.step();
                        SYS.measure();
                    }

                    // Compute averages and reset blocks
                    SYS.averages(i + 1);
                    SYS.block_reset(i + 1);
                }

                // Finalize the system
                SYS.finalize();

                // Rename output files based on the magnetic field value
                if(h == 0.02){
                    renameFile("../OUTPUT", "magnetization.dat", "magnetization_" + sim_name + std::to_string(temp) + ".dat");
                } else {
                    renameFile("../OUTPUT", "specific_heat.dat", "specific_heat_" + sim_name + std::to_string(temp) + ".dat");
                    renameFile("../OUTPUT", "total_energy.dat", "total_energy_" + sim_name + std::to_string(temp) + ".dat");
                    renameFile("../OUTPUT", "susceptibility.dat", "susceptibility_" + sim_name + std::to_string(temp) + ".dat");
                }
            }
        }

        // Swap the names of the properties files
        swapFileNames("../INPUT/properties.dat", "../INPUT/properties2.dat");
    }

    // Record the end time of the simulation
    auto end = std::chrono::high_resolution_clock::now();
    
    // Calculate and print the duration of the simulation
    auto duration = std::chrono::duration_cast<std::chrono::seconds>(end - start);
    std::cerr << "Simulation ended!\nTime of execution: " << duration.count() << "s\n\n";

    return 0;
}
