/** uhr: generic time performance tester
 * Author: LELE
 *
 * Things to set up:
 * 0. Includes: include all files to be tested,
 * 1. Time unit: in elapsed_time,
 * 2. What to write on time_data,
 * 3. Data type and distribution of RNG,
 * 4. Additive or multiplicative stepping,
 * 5. The experiments: in outer for loop. */

#include <cstdint>
#include <chrono>
#include <cmath>
#include <fstream>
#include <iostream>
#include <random>
#include <vector>

#include <functional>
#include <unordered_map>
#include <sstream>

#include "utils.cpp"

// Include to be tested files here
#include "editDistanceRecursive.h"
#include "editDistanceMemo.h"
#include "editDistanceDP.h"
#include "editDistanceDPOptimized.h"

int main(int argc, char *argv[])
{
    // Validate and sanitize input
    std::int64_t runs, lower, upper, step;
    validate_input(argc, argv, runs, lower, upper, step);

    // Set up clock variables
    std::int64_t n, i, executed_runs;
    std::int64_t total_runs_additive = runs * (((upper - lower) / step) + 1);
    std::int64_t total_runs_multiplicative = runs * (floor(log(upper / double(lower)) / log(step)) + 1);
    std::vector<double> times(runs);
    std::vector<double> q;
    double mean_time, time_stdev, dev;
    auto begin_time = std::chrono::high_resolution_clock::now();
    auto end_time = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::nano> elapsed_time = end_time - begin_time;

    // Set up random number generation
    std::random_device rd;
    std::mt19937_64 rng(rd());
    std::uniform_int_distribution<std::int64_t> u_distr; // change depending on app

    // File to write time data
    std::ofstream time_data;
    time_data.open(argv[1]);
    time_data << "n,t_mean,t_stdev,t_Q0,t_Q1,t_Q2,t_Q3,t_Q4" << std::endl;

    // Definimos diccionario para funciones 
    std::unordered_map<std::string, std::function<int(std::string, std::string, int, int)>> funciones;
    funciones["memo"] = [](std::string str1, std::string str2, int m, int n) {
        std::map<std::pair<int, int>, int> memo;
        return editDistanceMemo(str1, str2, m, n, memo);
    };
    funciones["recursive"] = editDistanceRecursive;
    funciones["dp"] = [](std::string str1, std::string str2, int m, int n) {
        return editDistanceDP(str1, str2);
    };
    funciones["dpopt"] = [](std::string str1, std::string str2, int m, int n) {
        return editDistanceDPOptimized(str1, str2);
    };


    // Begin testing
    std::cerr << "\033[0;36mRunning tests...\033[0m" << std::endl << std::endl;
    executed_runs = 0;
    for (auto funcion : funciones) {
        mean_time = 0;
        time_stdev = 0;


        std::string archivo1 = "archivo3.txt", archivo2 = "archivo4.txt";
        auto leerArchivo = [](const std::string& nombreArchivo) -> std::string {
            std::ifstream archivo(nombreArchivo);
            if (!archivo) {
                std::cerr << "No se pudo abrir el archivo: " << nombreArchivo << std::endl;
                exit(-1);
            }
            std::stringstream buffer;
            buffer << archivo.rdbuf();
            return buffer.str();
        };

        std::string str1 = leerArchivo(archivo1);
        std::string str2 = leerArchivo(archivo2);     

        // Run to compute elapsed time
        for (i = 0; i < runs; i++) {
            // Remember to change total depending on step type
            display_progress(++executed_runs, total_runs_additive);

            begin_time = std::chrono::high_resolution_clock::now();
            funcion.second(str1, str2, str1.size(), str2.size());
            end_time = std::chrono::high_resolution_clock::now();

            elapsed_time = end_time - begin_time;
            times[i] = elapsed_time.count();

            mean_time += times[i];
        }

        // Compute statistics
        mean_time /= runs;

        for (i = 0; i < runs; i++) {
            dev = times[i] - mean_time;
            time_stdev += dev * dev;
        }

        time_stdev /= runs - 1; // Subtract 1 to get unbiased estimator
        time_stdev = std::sqrt(time_stdev);

        quartiles(times, q);

        time_data << funcion.first << "," << mean_time << "," << time_stdev << ",";
        time_data << q[0] << "," << q[1] << "," << q[2] << "," << q[3] << "," << q[4] << std::endl;
    }

    // This is to keep loading bar after testing
    std::cerr << std::endl << std::endl;
    std::cerr << "\033[1;32mDone!\033[0m" << std::endl;

    time_data.close();

    return 0;
}