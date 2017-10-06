#ifndef KNNCLASSIFIER_H
#define KNNCLASSIFIER_H

#include "../labeledIndex/labeledIndex/labeledIndex.h"

//void printVec( std::vector<auto> a);
std::vector<std::tuple< int, double>> knnClassify( labeledIndex Ind, int k);
double getVecLen( std::vector<double> v);
double cosSim( std::vector<double> a, std::vector<double> b);




#endif 
