#include <iostream>
#include <vector>
#include <string>
#include <mpi.h>
#include "class.h"
#include "function.h"
#include "random.h"

// best 66.17 with 1000 elements and 4000 generations (exchanging solutions)
// best 65.94 with 10000 elements and 500 generations (indipendent search)

#define NUM_SEARCHES 4
const int n_generation = 5000; // Number of generations
const int dim_population = 1000; // Population size

// Function to serialize a Country object to a vector of doubles
std::vector<double> serializeCountry(const Country& country) {
    std::vector<double> data;
    for (const auto& city : country.GetCitiesVec()) {
        data.push_back(city.GetID());
        data.push_back(city.GetX());
        data.push_back(city.GetY());
    }
    return data;
}

// Function to deserialize a vector of doubles to a Country object
Country deserializeCountry(const std::vector<double>& data) {
    Country country;
    for (size_t i = 0; i < data.size(); i += 3) {
        City city(data[i], data[i + 1], data[i + 2]);
        country.AddCity(city);
    }
    return country;
}

// Function to run the genetic algorithm search in parallel for a given country shape
void run_search(Country& country, Random& rnd, int world_size, int world_rank, bool exchange) {
    const size_t exchange_interval = 50;

    // double best_fitness = std::numeric_limits<double>::max();
    // Path best_paths;

    Population population(country);
    population.Initialize(dim_population, true, rnd);
    std::vector<double> history_best_fit, history_half_avg;

    for (size_t k = 0; k < n_generation; k++) {
        population.Step(rnd);
        history_best_fit.push_back(std::get<0>(population.GetBestPath()));
        history_half_avg.push_back(population.BestHalfFitness());

        if (exchange && k > 0 && k % exchange_interval == 0) {
            // Exchange solutions among processes
            Path best_path_temp = population.GetBestPath();
            std::vector<int> serialized_path = std::get<1>(best_path_temp);

            for (int i = 0; i < world_size; i++) {
                if (i != world_rank) {
                    MPI_Send(serialized_path.data(), serialized_path.size(), MPI_INT, i, 0, MPI_COMM_WORLD);
                }
            }

            MPI_Status status;
            for (int i = 0; i < world_size; i++) {
                if (i != world_rank) {
                    std::vector<int> received_path(serialized_path.size());
                    MPI_Recv(received_path.data(), received_path.size(), MPI_INT, i, 0, MPI_COMM_WORLD, &status);
                    population.SwapPath(received_path, rnd);
                }
            }
        }
    }

    // Save results for this iteration
    Path best_paths = population.GetBestPath();
    std::string type;
    if(exchange) type = "E";
    else type = "I";
    std::string name_best = "OUTPUT/best_rank_" + std::to_string(world_rank) + "_" + type + ".txt";
    std::string name_history_best = "OUTPUT/history_best_rank_" + std::to_string(world_rank) + "_" + type + ".txt";
    std::string name_history_half_avg = "OUTPUT/history_half_avg_rank_" + std::to_string(world_rank) + "_" + type + ".txt";
    SaveVector(name_history_best, history_best_fit);
    SaveVector(name_history_half_avg, history_half_avg);
    SavePath(name_best, best_paths, country);
    std::cout<<"Fit: "<<std::get<0>(best_paths)<<"\n";
}



int main(int argc, char* argv[]) {

    MPI_Init(&argc, &argv);

    int world_size, world_rank;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    if (world_size < NUM_SEARCHES) {
        if (world_rank == 0) {
            std::cerr << "Error: This program requires at least " << NUM_SEARCHES << " MPI processes." << std::endl;
        }
        MPI_Finalize();
        return 1;
    }

    bool exchange = false;

    for(int iter{};iter<2;iter++){

        Random rnd;
        rnd.Initialization(world_rank);

        Country country;
        if (world_rank == 0) {
            country = readCountryFile("cap_prov_ita.txt");
            //country = GenerateCountry(100, 1, 10, rnd);
            std::vector<double> serialized_country = serializeCountry(country);
            size_t country_size = serialized_country.size();

            // Broadcast the size and data of the country to all ranks
            MPI_Bcast(&country_size, 1, MPI_INT, 0, MPI_COMM_WORLD);
            MPI_Bcast(serialized_country.data(), country_size, MPI_DOUBLE, 0, MPI_COMM_WORLD);
        } else {
            // Receive the size and data of the country from rank 0
            int country_size;
            MPI_Bcast(&country_size, 1, MPI_INT, 0, MPI_COMM_WORLD);
            std::vector<double> serialized_country(country_size);
            MPI_Bcast(serialized_country.data(), country_size, MPI_DOUBLE, 0, MPI_COMM_WORLD);
            // Deserialize the country data
            country = deserializeCountry(serialized_country);
        }

        // Run the genetic algorithm search in parallel for each rank
        if (world_rank < NUM_SEARCHES) {
            run_search(country, rnd, world_size, world_rank, exchange);
        }

        exchange = true;
    }

    MPI_Finalize();
    
    return 0;
}
