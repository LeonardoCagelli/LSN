#pragma once
#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<tuple>
#include"random.h"
#include<cassert>

using Path = std::tuple<double, std::vector<int>>; // Path is a tuple consisting of a double (fitness) and a vector of integers (city IDs)

class City {
    private:
        int _id;      // Unique identifier for the city
        double _x, _y; // Coordinates of the city

    public:
        City(int id, double x, double y) : _id{id}, _x{x}, _y{y} {}; // Constructor to initialize a city with an ID and coordinates
        double GetX() const { return _x; } // Getter for the x-coordinate
        double GetY() const { return _y; } // Getter for the y-coordinate
        void SetX(int x) { _x = x; } // Setter for the x-coordinate
        void SetY(int y) { _y = y; } // Setter for the y-coordinate
        int GetID() const { return _id; } // Getter for the city ID
        void SetID(int id) { _id = id; } // Setter for the city ID
};

class Country {
    private:
        std::vector<City> _cities; // List of cities in the country
        std::vector<int> _ids;     // List of city IDs

    public:
        Country() {} // Default constructor

        void AddCity(const City& city); // Add a city to the country
        City GetCity(int id) const; // Get a city by its ID
        City GetCity_Index(int id); // Get a city by its index in the list
        std::vector<int> GetIDVec() const; // Get the list of city IDs
        const std::vector<City>& GetCitiesVec() const;    // Get the list of cities
        size_t GetSize() const; // Get the number of cities
};

class Population {
    private:
        Country _country;          // The country which this population is solving for
        std::vector<Path> _population; // The list of paths (solutions) in the population
        Path _best_path;           // The best path found so far
        double _pmutation = 1.0;   // Probability of mutation
        double _pmut1 = 0.04;      // Probability of swap mutation
        double _pmut2 = 0.05;      // Probability of shift mutation
        double _pmut3 = 0.22;       // Probability of permutation mutation
        double _pmut4 = 0.1;       // Probability of inversion mutation
        double _pcross = 1.0;      // Probability of crossover
        double _pselect1 = 4.0;    // Probability parameter for selecting the first parent
        double _pselect2 = 4.0;    // Probability parameter for selecting the second parent
        double _pselection = 2.0;  // Probability parameter for selection
        int _nstep;                // Number of steps (generations) performed

    public:
        Population(const Country& country); // Constructor to initialize a population with a country
        void SetMutationProbabilities(double p, double p1, double p2, double p3, double p4); // Set probabilities for different mutations
        void SetSelectOperatorProbabiliteis(double p1, double p2); // Set probabilities for selection operators
        void SetCrossoverProbability(double p); // Set probability for crossover
        void SetSelectionProbability(double p); // Set probability for selection
        size_t SelectPath(double p, Random& rnd); // Select a path based on a probability parameter
        bool CheckPath(const std::vector<int>& path); // Check if a given path is valid
        double Fitness(const std::vector<int>& path); // Calculate the fitness (distance) of a given path
        void Sort(); // Sort the population by fitness
        void Mutate(size_t i, Random& rnd); // Mutate a path at index i
        void Crossover(size_t i1, size_t i2, Random& rnd); // Perform crossover between two paths
        void Selection(Random& rnd); // Perform selection to generate the next generation
        void Mutation(Random& rnd); // Perform mutation on the population
        void Step(Random& rnd); // Perform one step (generation) of the genetic algorithm
        void Initialize(int dim, bool random, Random& rnd); // Initialize the population
        Path GetBestPath() const; // Get the best path found so far
        double BestHalfFitness(); // Get the average fitness of the best half of the population
        void print(bool order); // Print the population
        void SwapPath(const std::vector<int>& path, Random& rnd);

};



//        assert((CheckPath(path)) && "Error - Trying to initialize the population with an unvalid path!");
