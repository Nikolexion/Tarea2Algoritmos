#include "editDistanceDPOptimized.h"

int editDistanceDPOptimized(std::string str1, std::string str2){
    int l1 = str1.length();
    int l2 = str2.length();

    // Vectores para simular la tabla completa, previo guarda la fila (i - 1) y actual la fila i
    std::vector<int> previo(l1 + 1, 0), actual(l2 + 1, 0);

    // LLenamos la fila 0
    for (int i = 0; i < l2 + 1; i++) {
        previo[i] = i;
    }
    
    // Llenar el resto de la tabla
    for(int i = 1; i <= l1; i++) {
        actual[0] = i;
        for(int j = 1; j <= l2; j++) {
            if(str1[i-1] == str2[j-1])
                actual[j] = previo[j - 1];
            else
                actual[j] = 1 + std::min({actual[j - 1], previo[j], previo[j - 1]});
        }
        previo = actual;
    }

    return actual[l1];
}
