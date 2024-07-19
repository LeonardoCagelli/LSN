#include "function.h"

// Function to generate a country with a specified number of cities, type, and length
Country GenerateCountry(int dim, int type, double length, Random& rnd) {
    Country country; // Create an instance of Country
    for (size_t i{}; i < dim; i++) {
        double x, y; // Variables to store coordinates of the city
        // Circle
        if (type == 0) {
            double theta = 2 * M_PI * rnd.Rannyu(); // Generate random angle
            x = (length / 2) * std::cos(theta); // Calculate x-coordinate
            y = (length / 2) * std::sin(theta); // Calculate y-coordinate
        } else if (type == 1) { // Square
            x = length * rnd.Rannyu(); // Generate random x-coordinate
            y = length * rnd.Rannyu(); // Generate random y-coordinate
        } else {
            std::cerr << "Error - Invalid country type!" << std::endl; // Error message for invalid type
            exit(-1); // Exit the program with an error code
        }

        country.AddCity(City(i, x, y)); // Add the generated city to the country
    }
    return country; // Return the generated country
}

// Function to save the path to a file
void SavePath(const std::string& filename, const Path& complete_path, const Country& country) {
    std::ofstream out(filename); // Open file for writing
    auto path = std::get<1>(complete_path); // Get the path from the tuple
    for (const auto& id : path) { // Iterate through the city IDs in the path
        auto city = country.GetCity(id); // Get the city corresponding to the ID
        out << city.GetX() << " " << city.GetY() << "\n"; // Write the city's coordinates to the file
    }
    out.close(); // Close the file
}

// Function to save a vector of doubles to a file
void SaveVector(const std::string& filename, const std::vector<double>& vec) {
    std::ofstream out(filename); // Open file for writing
    for (size_t i{}; i < vec.size(); i++) { // Iterate through the vector
        out << i << " " << vec[i] << "\n"; // Write the index and value to the file
    }
    out.close(); // Close the file
}

// Create a country from a coordinates input file
Country readCountryFile(const std::string& filename){
    std::ifstream in(filename);
    Country country;

    double x, y;
    size_t i{};
    while (in >> x >> y) {
        City city(i, x, y);
        country.AddCity(city);
        i++;
    }
    in.close();
    return country;
}