#include "editDistanceMemo.h"
#include "editDistanceRecursive.h"
#include "editDistanceDP.h"
#include "editDistanceDPOptimized.h"
#include <iostream>
#include <unordered_map>
#include <functional>

// g++ .\main.cpp .\editDistanceMemo.cpp .\editDistanceRecursive.cpp -o main

/*
int main(){
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

    std::string metodo = "dpopt";
    auto editDistance = funciones[metodo];
    
    std::cout << "Distancia gato y perro: " << (editDistance("gato","perro",4,5)) << std::endl;
    std::cout << "Distancia gato y gallina: " << (editDistance("gato","gallina",4,7)) << std::endl;
    std::cout << "Distancia gato y patito: " << (editDistance("gato","patito",4,6)) << std::endl;
    std::cout << "Distancia perro y gallina: " << (editDistance("perro","gallina",5,7)) << std::endl;
    std::cout << "Distancia perro y patito: " << (editDistance("perro","patito",5,6)) << std::endl;
    std::cout << "Distancia gallina y perro: " << (editDistance("gallina","patito",7,6)) << std::endl;

    return 0;
}

*/