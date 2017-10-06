#ifndef CLUSTER_H
#define CLUSTER_H


std::vector<double> normalizeVec( std::vector<int> a);
double getVecLen( std::vector<double> v);
vector<int> getVec( vector< tuple< int, vector<int>>> V, int docId);
std::vector< std::vector<int>> cluster( std::vector<std::tuple<int,std::vector<int>>>, int k);
vector<double> calcCent( vector<int> v, vector<tuple<int,vector<int>>> dic);



#endif 
