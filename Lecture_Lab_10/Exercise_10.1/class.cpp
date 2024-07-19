#include "class.h"

// Add a city to the country
void Country::AddCity(const City& city) {
    _cities.push_back(city); // Add the city to the _cities vector
    _ids.push_back(city.GetID()); // Add the city ID to the _ids vector
    if (_cities.size() != _ids.size()) { // Check if sizes of _cities and _ids match
        std::cout << "Error - _cities.size() and _ids.size() do not match!" << std::endl;
        exit(-1);
    }
}

// Get a city by its ID
City Country::GetCity(int id) const {
    for (const auto& city : _cities) {
        if (city.GetID() == id) { // Check if current city's ID matches the given ID
            return city; // Return the city if found
        }
    }
    std::cout << "Error - Id does not exists!" << std::endl;
    exit(-1);
}

// Get a city by its index in the list
City Country::GetCity_Index(int id) {
    return _cities[id]; // Return the city at the given index
}

// Get the list of city IDs
std::vector<int> Country::GetIDVec() const {
    return _ids; // Return the vector of city IDs
}

// Get the list of cities
const std::vector<City>& Country::GetCitiesVec() const {
    return _cities;
}

// Get the number of cities
size_t Country::GetSize() const {
    return _cities.size(); // Return the size of the _cities vector
}

// Constructor to initialize a population with a country
Population::Population(const Country& country) {
    _country = country; // Initialize the _country member with the given country
}

// Set probabilities for different mutations
void Population::SetMutationProbabilities(double p, double p1, double p2, double p3, double p4) {
    _pmutation = p;
    _pmut1 = p1;
    _pmut2 = p2;
    _pmut3 = p3;
    _pmut4 = p4;
}

// Set probabilities for selection operators
void Population::SetSelectOperatorProbabiliteis(double p1, double p2) {
    _pselect1 = p1;
    _pselect2 = p2;
}

// Set probability for crossover
void Population::SetCrossoverProbability(double p) {
    _pcross = p;
}

// Set probability for selection
void Population::SetSelectionProbability(double p) {
    _pselection = p;
}

// Select a path based on a probability parameter
size_t Population::SelectPath(double p, Random& rnd) {
    size_t index = size_t(_population.size() * pow(rnd.Rannyu(), p));
    return index; // Return the index of the selected path
}

// Check if a given path is valid
bool Population::CheckPath(const std::vector<int>& path) {
    auto ids = _country.GetIDVec(); // Get the list of city IDs

    for (size_t i{}; i < path.size(); i++) {
        auto it = std::find(ids.begin(), ids.end(), path[i]);
        if (it != ids.end()) ids.erase(it); // Erase the ID from the list if found
        else {
            std::cerr << "ERROR - ID not found during path validation!" << std::endl;
            exit(-1);
        }
    }

    if (ids.size() != 0) return false; // Return false if there are remaining IDs
    return true; // Return true if the path is valid
}

// Calculate the fitness (distance) of a given path
double Population::Fitness(const std::vector<int>& path) {
    double distance = 0;
    size_t size = path.size();
    double d1, d2;

    for (size_t i{ 0 }; i < path.size() - 1; i++) {
        d1 = _country.GetCity_Index(path[i]).GetX() - _country.GetCity_Index(path[i + 1]).GetX();
        d2 = _country.GetCity_Index(path[i]).GetY() - _country.GetCity_Index(path[i + 1]).GetY();
        distance += (d1 * d1 + d2 * d2); // Accumulate the distance
    }

    d1 = _country.GetCity_Index(path[0]).GetX() - _country.GetCity_Index(path[size - 1]).GetX();
    d2 = _country.GetCity_Index(path[0]).GetY() - _country.GetCity_Index(path[size - 1]).GetY();
    distance += (d1 * d1 + d2 * d2); // Add the distance from last city back to the first city
    return distance; // Return the total distance
}

// Sort the population by fitness
void Population::Sort() {
    // Use a lambda function for more compactness
    auto comparator = [](const Path& a, const Path& b) {
        return std::get<0>(a) < std::get<0>(b);
    };
    std::sort(_population.begin(), _population.end(), comparator); // Sort the population
}

// Mutate a path at index i
void Population::Mutate(size_t i, Random& rnd) {

    auto& path = std::get<1>(_population[i]);
    size_t size = path.size();

    // swap mutation
    if (rnd.Rannyu() < _pmut1) {
        size_t j1 = rnd.Rannyu(1, size);
        size_t j2;
        while (true) {
            j2 = rnd.Rannyu(1, size);
            if (j1 != j2) break; // Ensure j1 and j2 are different
        }

        std::swap(path[j1], path[j2]); // Swap two elements in the path
    }

    // shift mutation 
    if (rnd.Rannyu() < _pmut2) {
        size_t size = path.size();

        size_t start = rnd.Rannyu(1, size - 2);
        size_t length = rnd.Rannyu(2, size - start); // Minimum length of 2

        // Extract the subsequence
        std::vector<int> subseq(path.begin() + start, path.begin() + start + length);

        // Erase the subsequence from its original position
        path.erase(path.begin() + start, path.begin() + start + length);

        // Select a new position for the subsequence
        size_t new_position = rnd.Rannyu(1, path.size() + 1); // Ensure the new position is valid

        // Insert the subsequence at the new position
        path.insert(path.begin() + new_position, subseq.begin(), subseq.end());
    }

    // permutation mutation 
    if (rnd.Rannyu() < _pmut3) {
        size_t maxLength = (size - 1) / 2;

        // Select the length of the subsequences (minimum 2)
        size_t length = rnd.Rannyu(2, maxLength + 1);

        // Select the start of the first subsequence
        size_t start1 = rnd.Rannyu(1, size - 2 * length + 1);

        // Select the start of the second subsequence ensuring it does not overlap with the first
        size_t start2 = rnd.Rannyu(start1 + length, size - length + 1);

        // Swap the two subsequences
        for (size_t j{}; j < length; j++) {
            std::swap(path[start1 + j], path[start2 + j]);
        }
    }

    // inversion mutation  
    if (rnd.Rannyu() < _pmut4) {
        size_t end = rnd.Rannyu(2, size);
        size_t start = rnd.Rannyu(1, size - end + 1);
        std::reverse(path.begin() + start, path.begin() + start + end); // Reverse a subsequence in the path
    }
}

// Perform crossover between two paths
void Population::Crossover(size_t i1, size_t i2, Random& rnd) {

    if (rnd.Rannyu() < _pcross) {
        auto father = std::get<1>(_population[i1]);
        auto mother = std::get<1>(_population[i2]);

        size_t size = father.size();

        // Define the cutting point (at least from the index 1)
        size_t cut = size_t(rnd.Rannyu(2, size - 1));

        std::vector<int> first_son(size);
        std::vector<int> second_son(size);

        // Copy the unchanged portion of path
        for (size_t j{}; j < cut; j++) {
            first_son[j] = std::get<1>(_population[i1])[j];
            second_son[j] = std::get<1>(_population[i2])[j];

            // Remove from the copy vector the elements that have already been assigned
            auto it1 = std::find(mother.begin(), mother.end(), std::get<1>(_population[i1])[j]);
            auto it2 = std::find(father.begin(), father.end(), std::get<1>(_population[i2])[j]);

            if (it1 == mother.end() or it2 == father.end()) {
                std::cerr << "ERROR - Iterators out of range - elements not found in the path!" << std::endl;
                exit(-1);
            } else {
                mother.erase(it1);
                father.erase(it2);
            }
        }

        // Apply cross over between genes
        for (size_t j{ cut }; j < size; j++) {
            first_son[j] = mother[j - cut];
            second_son[j] = father[j - cut];
        }

        assert(CheckPath(first_son) && CheckPath(second_son) && "Error - Crossover has produced invalid path!");
        _population.push_back(Path(Fitness(first_son), first_son));
        _population.push_back(Path(Fitness(second_son), second_son));
    }
}

// Perform selection to generate the next generation
void Population::Selection(Random& rnd) {
    Sort(); // Sort the population by fitness
    std::vector<Path> new_population(_population.size() / 2);
    for (size_t i{}; i < _population.size() / 2; i++) {
        size_t index = SelectPath(_pselection, rnd);
        new_population[i] = _population[index]; // Select paths based on probability and add to new population
    }
    _population = std::move(new_population); // Replace old population with new population
}

// Perform mutation on the population
void Population::Mutation(Random& rnd) {
    for (size_t i{}; i < _population.size() / 2; i++) {
        size_t index = SelectPath(_pmutation, rnd); // Select paths for mutation
        Mutate(index, rnd); // Mutate the selected paths
    }
}

// Perform one step (generation) of the genetic algorithm
void Population::Step(Random& rnd) {
    _nstep++;
    Selection(rnd); // Perform selection
    Mutation(rnd); // Perform mutation
    size_t size = _population.size();
    for (size_t i{}; i < size / 2; i++) {
        size_t first_index = SelectPath(_pselect1, rnd);
        size_t second_index = SelectPath(_pselect2, rnd);
        Crossover(first_index, second_index, rnd); // Perform crossover
    }
    Sort(); // Sort the population

    if (std::get<0>(_population[0]) < std::get<0>(_best_path)) {
        _best_path = _population[0]; // Update the best path if a better one is found
    }
}

// Initialize the population
void Population::Initialize(int dim, bool random, Random& rnd) {
    _nstep = 0;
    auto size = _country.GetSize();
    _population.resize(dim);
    auto ids = _country.GetIDVec();
    for (size_t i{}; i < dim; i++) {

        std::vector<int> path(size);
        for (int j{}; j < size; j++) path[j] = ids[j];

        if (random) {
            int permutations = 6 * size;
            for (size_t k{}; k < permutations; k++) {
                size_t first = rnd.Rannyu(1, size);
                size_t second = rnd.Rannyu(1, size);
                std::swap(path[first], path[second]); // Randomly shuffle the path
            }
        }
        assert((CheckPath(path)) && "Error - Trying to initialize the population with an unvalid path!");
        _population[i] = Path(Fitness(path), path); // Add the path to the population
    }
    Sort(); // Sort the population
    _best_path = _population[0]; // Set the best path
}

// Get the best path found so far
Path Population::GetBestPath() const {
    return _best_path;
}

// Get the average fitness of the best half of the population
double Population::BestHalfFitness() {
    Sort();
    size_t size = _population.size() / 2;
    double distance{};
    for (size_t i{}; i < size; i++) {
        distance += std::get<0>(_population[i]); // Sum the fitness of the best half
    }
    return distance /= size; // Return the average fitness
}

// Print the population
void Population::print(bool order = false) {
    if (order) Sort(); // Sort the population if order is true
    for (const auto& gen : _population) {
        double fit = std::get<0>(gen);
        const std::vector<int>& path = std::get<1>(gen);
        std::cout << "Fit: " << fit << "  | ";
        std::cout << "1 ";
        for (auto id : path) {
            std::cout << id << " "; // Print each city's ID in the path
        }
        std::cout << std::endl;
    }
}

void Population::SwapPath(const std::vector<int>& path, Random& rnd){
    Sort();
    // size_t index = rnd.Rannyu(0, _population.size());
    _population[0] = Path(Fitness(path), path);
    return;
}