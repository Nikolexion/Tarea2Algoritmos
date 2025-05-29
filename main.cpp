#include "editDistanceMemo.h"
#include "editDistanceRecursive.h"
#include <iostream>

// g++ .\main.cpp .\editDistanceMemo.cpp .\editDistanceRecursive.cpp -o main
int main(){
    std::cout << "Distancia gato y perro: " << (editDistanceRecursive("gato","perro",4,5)) << std::endl;
    std::cout << "Distancia gato y gallina: " << (editDistanceRecursive("gato","gallina",4,7)) << std::endl;;
    std::cout << "Distancia gato y patito: " << (editDistanceRecursive("gato","patito",4,6)) << std::endl;;
    std::cout << "Distancia perro y gallina: " << (editDistanceRecursive("perro","gallina",5,7)) << std::endl;;
    std::cout << "Distancia perro y patito: " << (editDistanceRecursive("perro","patito",5,6)) << std::endl;;
    std::cout << "Distancia gallina y perro: " << (editDistanceRecursive("gallina","patito",7,6)) << std::endl;;
    return 0;
}

