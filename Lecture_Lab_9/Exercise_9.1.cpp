#include<iostream>
#include<vector>
#include"class.h" 
#include"function.h"
#include"random.h"

int main() {
    int n_cities = 34; // Number of cities
    double length = 10.0; // Length of the country
    int n_generation = 200; // Number of generations
    int dim_population = 1000; // Population size

    Random rnd; // Random number generator
    rnd.Initialization(); // Initialize random number generator

    // ========================
    //      Circle Country
    // ========================
    int country_type = 0; // Circle type country

    Country circle_country = GenerateCountry(n_cities, country_type, length, rnd); // Generate circle country
    Population circle_population(circle_country); // Create population for circle country
    circle_population.Initialize(dim_population, true, rnd); // Initialize population
    circle_population.SetMutationProbabilities(1.0, 0.04, 0.05, 0.22, 0.1); // Set mutation probabilities

    std::vector<double> best_fit; // Vector to store best fitness values
    std::vector<double> best_half_fit; // Vector to store best half fitness values

    // Evolve the population for a specified number of generations
    for (size_t i{}; i < n_generation; i++) {
        circle_population.Step(rnd); // Perform one step of evolution
        best_fit.push_back(std::get<0>(circle_population.GetBestPath())); // Record best fitness
        best_half_fit.push_back(circle_population.BestHalfFitness()); // Record best half fitness
    }

    Path circle_best_path = circle_population.GetBestPath(); // Get the best path for circle country

    SavePath("OUTPUT/Best_Circle.txt", circle_best_path, circle_country); // Save the best path to a file
    SaveVector("OUTPUT/Circle_Avg_Fitness.txt", best_half_fit); // Save average fitness to a file
    SaveVector("OUTPUT/Circle_Best_Fitness.txt", best_fit); // Save best fitness to a file

    // ========================
    //      Square Country
    // ========================
    country_type = 1; // Square type country

    Country square_country = GenerateCountry(n_cities, country_type, length, rnd); // Generate square country
    Population square_population(square_country); // Create population for square country
    square_population.Initialize(dim_population, true, rnd); // Initialize population
    square_population.SetMutationProbabilities(1.0, 0.04, 0.05, 0.22, 0.1); // Set mutation probabilities

    best_fit.clear(); // Clear best fitness vector
    best_half_fit.clear(); // Clear best half fitness vector

    // Evolve the population for a specified number of generations
    for (size_t i{}; i < n_generation; i++) {
        square_population.Step(rnd); // Perform one step of evolution
        best_fit.push_back(std::get<0>(square_population.GetBestPath())); // Record best fitness
        best_half_fit.push_back(square_population.BestHalfFitness()); // Record best half fitness
    }

    Path square_best_path = square_population.GetBestPath(); // Get the best path for square country

    SavePath("OUTPUT/Best_Square.txt", square_best_path, square_country); // Save the best path to a file
    SaveVector("OUTPUT/Square_Avg_Fitness.txt", best_half_fit); // Save average fitness to a file
    SaveVector("OUTPUT/Square_Best_Fitness.txt", best_fit); // Save best fitness to a file

    // Print the best fitness values for both circle and square countries
    puts("======================================");
    std::cout << "Best Square Fitness Value: " << std::get<0>(square_best_path) << "\n";
    std::cout << "Best Circle Fitness Value: " << std::get<0>(circle_best_path) << "\n";
    puts("======================================");

    return 0; // End of the program
}
