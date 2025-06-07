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
    time_data << "n,str1,str2,str1_len,str2_len,t_mean,t_stdev,t_Q0,t_Q1,t_Q2,t_Q3,t_Q4" << std::endl;

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

    std::vector<std::string> nombres_archivos = {"archivo1.txt", "archivo2.txt", "archivo3.txt", "archivo4.txt"};
    std::vector<std::pair<std::string, std::string>> pares_de_archivos;
    for (size_t idx1 = 0; idx1 < nombres_archivos.size(); ++idx1) {
        for (size_t idx2 = idx1 + 1; idx2 < nombres_archivos.size(); ++idx2) {
            pares_de_archivos.push_back({nombres_archivos[idx1], nombres_archivos[idx2]});
        }
    }

    std::int64_t total_tests_to_run = pares_de_archivos.size() * funciones.size() * runs;

    // Begin testing
    std::cerr << "\033[0;36mRunning tests...\033[0m" << std::endl << std::endl;
    executed_runs = 0;
    for (const auto& par_archivos : pares_de_archivos) {
        mean_time = 0;
        time_stdev = 0;
        const std::string& nombre_archivo_s1 = par_archivos.first;
        const std::string& nombre_archivo_s2 = par_archivos.second;

        std::cout << "Probando con S1: " << nombre_archivo_s1 << " y S2: " << nombre_archivo_s2 << std::endl;

        std::string str1_content, str2_content;

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

        try {
            str1_content = leerArchivo(nombre_archivo_s1);
            str2_content = leerArchivo(nombre_archivo_s2);
        } catch (const std::runtime_error& e) {
            std::cerr << "Error leyendo archivos: " << e.what() << ". Saltando esta combinación." << std::endl;
            // Ajustar executed_runs si se salta un set completo de 'runs' para 'funciones.size()' algoritmos
            executed_runs += funciones.size() * runs; // Asumiendo que display_progress lo maneja bien
            continue;
        }
        
        for (const auto& funcion_entry : funciones) {
            const std::string& nombre_algoritmo = funcion_entry.first;
            auto algoritmo_a_probar = funcion_entry.second;

            // Para la versión recursiva, si es muy lenta con archivos grandes, podrías querer saltarla
            // o usar un número menor de 'runs', o un timeout.
            
            std::cout << "Probando algoritmo: " << nombre_algoritmo << std::endl;
            if (nombre_algoritmo == "recursive") {
                // Si el algoritmo es recursivo, podrías querer saltarlo para archivos grandes
                if (str1_content.length() > 500 || str2_content.length() > 500) {
                    std::cerr << "Saltando algoritmo recursivo para archivos grandes." << std::endl;
                    continue;
                }

            }

            mean_time = 0;
            time_stdev = 0;

            for (i = 0; i < runs; i++) {
                display_progress(++executed_runs, total_tests_to_run);

                begin_time = std::chrono::high_resolution_clock::now();
                /* int result = */ algoritmo_a_probar(str1_content, str2_content, str1_content.length(), str2_content.length());
                end_time = std::chrono::high_resolution_clock::now();

                elapsed_time = end_time - begin_time;
                times[i] = elapsed_time.count(); // En nanosegundos
                mean_time += times[i];
            }

            // Compute statistics
            mean_time /= runs;

            if (runs > 1) {
                for (i = 0; i < runs; i++) {
                    dev = times[i] - mean_time;
                    time_stdev += dev * dev;
                }
                time_stdev /= (runs - 1); // Subtract 1 to get unbiased estimator
                time_stdev = std::sqrt(time_stdev);
            } else {
                time_stdev = 0; // No hay desviación si solo hay una muestra
            }


            quartiles(times, q); // Asumiendo que q se maneja bien (se limpia o se sobrescribe)

            // Escribir nombre del algoritmo, nombres de archivo y sus tamaños
            time_data << nombre_algoritmo << "," << nombre_archivo_s1 << "," << nombre_archivo_s2 << ","
                      << str1_content.length() << "," << str2_content.length() << ","
                      << mean_time << "," << time_stdev << ",";
            time_data << q[0] << "," << q[1] << "," << q[2] << "," << q[3] << "," << q[4] << std::endl;
        }
    }

    // This is to keep loading bar after testing
    std::cerr << std::endl << std::endl;
    std::cerr << "\033[1;32mDone!\033[0m" << std::endl;

    time_data.close();

    return 0;
}