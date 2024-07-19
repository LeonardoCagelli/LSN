#pragma once
#include<iostream>
#include<cmath>
#include<vector>
#include<fstream>
#include<functional>
#include"random.h"

// A simple struct to manage the final position of the random walk 
template<typename T = int>
struct Position{
    T m_x, m_y, m_z; // Coordinates of the position

    // Constructor to initialize the position with given coordinates
    Position(T x, T y, T z) : m_x{x}, m_y{y}, m_z{z} {};

    // Default constructor initializes the position to (0,0,0)
    Position() : m_x{0}, m_y{0}, m_z{0} {};
};

// A general class to create child random walk objects
class RandomWalk{
    protected:
        Random m_rnd; // Random number generator
        size_t m_steps; // Total number of steps in the random walk
        size_t m_iteration; // Current step number
        
    public:
        // Class constructor
        RandomWalk(Random rnd, size_t steps) : m_rnd{rnd}, m_steps{steps}, m_iteration{0} {}

        // Pure virtual function to be implemented by derived classes
        virtual void step() = 0;
};

// Continuous random walk class
class ContinuousRandomWalk3D : public RandomWalk {

    protected:
        double m_x0, m_y0, m_z0; // Initial position coordinates
        double m_x, m_y, m_z; // Current position coordinates
        double m_lattice; // Step size in the lattice

    public:
        // Constructor with initial position and lattice size
        ContinuousRandomWalk3D(Random rnd, size_t steps, double x, double y, double z, double lattice);

        // Constructor with lattice size, initial position defaults to (0,0,0)
        ContinuousRandomWalk3D(Random rnd, size_t steps, double lattice);

        // Override step function to perform one step in the continuous random walk
        void step() override;

        // Function to print information about the random walk
        void info();

        // Function to save the current position as a Position object
        Position<double> savePosition();

        // Function to reset the random walk to the initial position
        void reset();

        // Function to run the random walk simulation
        std::vector<Position<double>> runSimulation(size_t steps = 0, bool saveHistory = true);
};

// Discrete random walk class
class DiscreteRandomWalk3D : public RandomWalk {

    protected:
        int m_x0, m_y0, m_z0; // Initial position coordinates
        int m_x, m_y, m_z; // Current position coordinates
        int m_lattice; // Step size in the lattice

    public:
        // Constructor with initial position and lattice size
        DiscreteRandomWalk3D(Random rnd, size_t steps, int x, int y, int z, int lattice);

        // Constructor with default initial position (0,0,0) and lattice size 1
        DiscreteRandomWalk3D(Random rnd, size_t steps);

        // Override step function to perform one step in the discrete random walk
        void step() override;

        // Function to print information about the random walk
        void info();

        // Function to save the current position as a Position object
        Position<int> savePosition();

        // Function to reset the random walk to the initial position
        void reset();

        // Function to run the random walk simulation
        std::vector<Position<int>> runSimulation(size_t steps = 0, bool saveHistory = true);
};
