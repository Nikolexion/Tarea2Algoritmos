#ifndef EDIT_DISTANCE_MEMO_H
#define EDIT_DISTANCE_MEMO_H
#include <string>
#include <map>
#include <utility> // para usar el std::pair

int editDistanceMemo(std::string str1, std::string str2, int i, int j, std::map<std::pair<int, int>, int>& memo);

#endif