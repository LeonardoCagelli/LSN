#include "class.h"

// Constructor for ContinuousRandomWalk3D with initial position and lattice size
ContinuousRandomWalk3D::ContinuousRandomWalk3D(Random rnd, size_t steps, double x, double y, double z, double lattice) :
                    RandomWalk(rnd, steps), m_x0{x}, m_y0{y}, m_z0{z}, m_x{0}, m_y{0}, m_z{0}, m_lattice{lattice} {}

// Constructor for ContinuousRandomWalk3D with lattice size, initial position defaults to (0,0,0)
ContinuousRandomWalk3D::ContinuousRandomWalk3D(Random rnd, size_t steps, double lattice) :
            RandomWalk(rnd, steps), m_x0{0}, m_y0{0}, m_z0{0}, m_x{0}, m_y{0}, m_z{0}, m_lattice{lattice} {}

// Function to perform one step in the continuous random walk
void ContinuousRandomWalk3D::step() {
    // Generate random angles theta and phi for spherical coordinates
    double m_theta = m_rnd.Rannyu() * M_PI;
    double m_phi = m_rnd.Rannyu() * (2 * M_PI);

    // Update the position based on the random angles
    m_x += m_lattice * sin(m_theta) * cos(m_phi);
    m_y += m_lattice * sin(m_theta) * sin(m_phi);
    m_z += m_lattice * cos(m_theta); 

    // Increment the iteration counter
    m_iteration += 1;
}

// Function to print the current state of the random walk
void ContinuousRandomWalk3D::info(){
    std::cout << "##### RandomWalk:\n";
    std::cout << "    Lattice: " << m_lattice << "\n";
    std::cout << "    Initial position: " << m_x0 << " " << m_y0 << " " << m_z0 << "\n";
    std::cout << "    Current position: " << m_x << " " << m_y << " " << m_z << "\n";
    std::cout << "################\n\n";
}

// Function to save the current position as a Position object
Position<double> ContinuousRandomWalk3D::savePosition(){
    return Position<double>(m_x, m_y, m_z);
}

// Function to reset the random walk to the initial position
void ContinuousRandomWalk3D::reset(){
    m_x = m_x0;
    m_y = m_y0;
    m_z = m_z0;
    m_iteration = 0;
}

// Function to run the random walk simulation
std::vector<Position<double>> ContinuousRandomWalk3D::runSimulation(size_t steps, bool saveHistory){

    reset(); // Reset the walk before starting

    size_t temp_steps = m_steps;
    if (steps != 0) temp_steps = steps;
    
    if (saveHistory){
        std::vector<Position<double>> history;

        // Perform the random walk and save each position
        while (m_iteration < temp_steps){
            step();
            history.push_back(savePosition());
        }

        return history;
    } else {
        // Perform the random walk without saving each position
        while (m_iteration < temp_steps) step();

        return std::vector<Position<double>>{savePosition()};
    }
}

// Constructor for DiscreteRandomWalk3D with initial position and lattice size
DiscreteRandomWalk3D::DiscreteRandomWalk3D(Random rnd, size_t steps, int x, int y, int z, int lattice) :
            RandomWalk(rnd, steps), m_x0{x}, m_y0{y}, m_z0{z}, m_x{0}, m_y{0}, m_z{0}, m_lattice{lattice} {}

// Constructor for DiscreteRandomWalk3D with default initial position (0,0,0) and lattice size 1
DiscreteRandomWalk3D::DiscreteRandomWalk3D(Random rnd, size_t steps) :
            RandomWalk(rnd, steps), m_x0{0}, m_y0{0}, m_z0{0}, m_x{0}, m_y{0}, m_z{0}, m_lattice{1} {}

// Function to perform one step in the discrete random walk
void DiscreteRandomWalk3D::step() {
    double choice = m_rnd.Rannyu(); // Random choice for direction
    double r = m_rnd.Rannyu(); // Random choice for sign

    int sign = 1;
    if (r < 0.5) sign = -1;

    // Update the position based on random choice
    if (choice < 1/3.) m_x += m_lattice * sign;
    else if (choice < 2/3.) m_y += m_lattice * sign;
    else m_z += m_lattice * sign;

    // Increment the iteration counter
    m_iteration += 1;
}

// Function to print the current state of the random walk
void DiscreteRandomWalk3D::info(){
    std::cout << "##### RandomWalk:\n";
    std::cout << "    Lattice: " << m_lattice << "\n";
    std::cout << "    Initial position: " << m_x0 << " " << m_y0 << " " << m_z0 << "\n";
    std::cout << "    Current position: " << m_x << " " << m_y << " " << m_z << "\n";
    std::cout << "################\n\n";
}

// Function to save the current position as a Position object
Position<int> DiscreteRandomWalk3D::savePosition(){
    return Position<int>(m_x, m_y, m_z);
}

// Function to reset the random walk to the initial position
void DiscreteRandomWalk3D::reset(){
    m_x = m_x0;
    m_y = m_y0;
    m_z = m_z0;
    m_iteration = 0;
}

// Function to run the random walk simulation
std::vector<Position<int>> DiscreteRandomWalk3D::runSimulation(size_t steps, bool saveHistory){

    reset(); // Reset the walk before starting

    size_t temp_steps = m_steps;
    if (steps != 0) temp_steps = steps;

    if (saveHistory){
        std::vector<Position<int>> history;

        // Perform the random walk and save each position
        while (m_iteration < temp_steps){
            step();
            history.push_back(savePosition());
        }

        return history;
    } else {
        // Perform the random walk without saving each position
        while (m_iteration < temp_steps) step();

        return std::vector<Position<int>>{savePosition()};
    }
}
