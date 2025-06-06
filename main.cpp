#include "editDistanceMemo.h"
#include "editDistanceRecursive.h"
#include "editDistanceDP.h"
#include "editDistanceDPOptimized.h"
#include <iostream>
#include <unordered_map>
#include <functional>
#include <fstream>
#include <sstream>
#include <cstring>

// g++ .\main.cpp .\editDistanceMemo.cpp .\editDistanceRecursive.cpp -o main
int main(int argc, char const *argv[]){
    if(argc != 7) {
        std::cerr << "Uso: <ejecutable> -a <algoritmo(recursive, memo, dp, dpopt)> -s1 <archivo.txt> -s2 <archivo2.txt>" << std::endl;
        return -1;
    }
    std::string metodo;
    std::string archivo1, archivo2;
    for (int i = 1; i < argc; i++) {
        if(strcmp(argv[i], "-a") == 0)
            metodo = argv[++i];
        else if(strcmp(argv[i], "-s1") == 0)
            archivo1 = argv[++i];
        else if(strcmp(argv[i], "-s2") == 0)
            archivo2 = argv[++i];
        else {
            std::cerr << "Argumento incorrecto: " << argv[i] << std::endl;
            return -1;
        }
    }

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

    auto editDistance = funciones[metodo];
    std::cout << str1 << " " << str2 << std::endl;
    
    std::cout << editDistance(str1, str2, str1.length(), str2.length()) << std::endl;
    //std::cout << "Distancia gato y perro: " << (editDistance("gato","perro",4,5)) << std::endl;
    //std::cout << "Distancia gato y gallina: " << (editDistance("gato","gallina",4,7)) << std::endl;
    //std::cout << "Distancia gato y patito: " << (editDistance("gato","patito",4,6)) << std::endl;
    //std::cout << "Distancia perro y gallina: " << (editDistance("perro","gallina",5,7)) << std::endl;
    //std::cout << "Distancia perro y patito: " << (editDistance("perro","patito",5,6)) << std::endl;
    //std::cout << "Distancia gallina y perro: " << (editDistance("gallina","patito",7,6)) << std::endl;
    return 0;
}

