#include "editDistanceRecursive.h"

int editDistanceRecursive(std::string str1, std::string str2,int i, int j){

    // Caso base cuando uno de los strings está vacio
    if (i == 0) return j; 
    if (j == 0) return i;

    // Caso cuando los últimos caracteres son iguales
    if (str1[i-1] == str2[j-1]) {
        return editDistanceRecursive(str1, str2, i-1, j-1);
    }

    int costoInsert = editDistanceRecursive(str1, str2, i, j-1);
    int costoDelete = editDistanceRecursive(str1, str2, i-1, j);

    if (costoInsert < costoDelete) {
        return 1 + costoInsert;
    } else {
        return 1 + costoDelete;
    }
}