#include "editDistanceMemo.h"
#include "editDistanceRecursive.h"
#include <iostream>

// g++ .\main.cpp .\editDistanceMemo.cpp .\editDistanceRecursive.cpp -o main
int main(){
    bool usarMemoization = false;
    if (usarMemoization){
        std::cout << "Distancia gato y perro: " << (editDistanceRecursive("gato","perro",4,5)) << std::endl;
        std::cout << "Distancia gato y gallina: " << (editDistanceRecursive("gato","gallina",4,7)) << std::endl;;
        std::cout << "Distancia gato y patito: " << (editDistanceRecursive("gato","patito",4,6)) << std::endl;;
        std::cout << "Distancia perro y gallina: " << (editDistanceRecursive("perro","gallina",5,7)) << std::endl;;
        std::cout << "Distancia perro y patito: " << (editDistanceRecursive("perro","patito",5,6)) << std::endl;;
        std::cout << "Distancia gallina y perro: " << (editDistanceRecursive("gallina","patito",7,6)) << std::endl;;
    } else {
        std::map<std::pair<int, int>, int> memo;
        std::cout << "Distancia gato y perro: " << (editDistanceMemo("gato","perro",4,5,memo)) << std::endl;
        memo.clear(); // Limpiar para la siguiente llamada

        std::cout << "Distancia gato y gallina: " << (editDistanceMemo("gato","gallina",4,7,memo)) << std::endl;
        memo.clear(); 

        std::cout << "Distancia gato y patito: " << (editDistanceMemo("gato","patito",4,6,memo)) << std::endl;
        memo.clear();

        std::cout << "Distancia perro y gallina: " << (editDistanceMemo("perro","gallina",5,7,memo)) << std::endl;
        memo.clear(); 

        std::cout << "Distancia perro y patito: " << (editDistanceMemo("perro","patito",5,6,memo)) << std::endl;
        memo.clear();

        std::cout << "Distancia gallina y patito: " << (editDistanceMemo("gallina","patito",7,6,memo)) << std::endl;
    }
    return 0;
}

