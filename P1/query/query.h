#ifndef QUERY_H
#define QUERY_H

#include "../dataStructures/invertedIndex/invertedIndex.h"




std::vector<int> eval( invertedIndex Inv, std::vector<std::string> query);
void printVec( std::vector<auto> a);
std::vector<std::string> parseQuery( std:: string);
std::vector<int> AND( std::vector<int> a, std::vector<int> b);
std::vector<int> OR( std::vector<int> a, std::vector<int> b);





#endif 


