#include "editDistanceMemo.h"

int editDistanceMemo(const std::string str1, const std::string str2, int i, int j, std::map<std::pair<int, int>, int>& memo){

    // Caso base cuando uno de los strings está vacio
    if (i == 0) return j; 
    if (j == 0) return i;

    // Verificamos si el resultado ya se calculó
    auto key = std::make_pair(i, j);
    if (memo.find(key) != memo.end()) {
        return memo[key];
    }

    // Caso cuando los últimos caracteres son iguales
    if (str1[i-1] == str2[j-1]) {
        memo[key] = editDistanceMemo(str1, str2, i-1, j-1, memo);
    } else {
        int costoInsert = editDistanceMemo(str1, str2, i, j-1, memo);
        int costoDelete = editDistanceMemo(str1, str2, i-1, j, memo);

        if (costoInsert < costoDelete) {
            memo[key] = 1 + costoInsert;
        } else {
            memo[key] = 1 + costoDelete;
        }
    }

    return memo[key];
}