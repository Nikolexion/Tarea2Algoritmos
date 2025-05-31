#include "editDistanceDP.h"

int editDistanceDP(std::string str1, std::string str2){
    int l1 = str1.length();
    int l2 = str2.length();

    // Tabla para guardar los resultados de los subproblemas
    std::vector<std::vector<int>> dp(l1 + 1, std::vector<int>(l2 + 1));

    // Llenar las entradas conocidas de la tabla
    for (int i = 0; i < l1 + 1; i++) {
        dp[i][0] = i;
    }
    for (int i = 0; i < l2 + 1; i++) {
        dp[0][i] = i;
    }
    
    // Llenar el resto de la tabla
    for(int i = 1; i <= l1; i++) {
        for(int j = 1; j <= l2; j++) {
            if(str1[i-1] == str2[j-1])
                dp[i][j] = dp[i-1][j-1];
            else
                dp[i][j] = 1 + std::min({dp[i][j - 1], dp[i - 1][j], dp[i - 1][j - 1]});
        }
    }

    return dp[l1][l2];
}
