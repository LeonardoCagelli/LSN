#include<iostream>
#include <cmath> 
#include <fstream> 
#include "class.h"

// Function to generate a country with cities
Country GenerateCountry(int dim, int type, double length, Random& rnd);

// Function to save a path to a file
void SavePath(const std::string& filename, const Path& complete_path, const Country& country);

// Function to save a vector of doubles to a file
void SaveVector(const std::string& filename, const std::vector<double>& vec);