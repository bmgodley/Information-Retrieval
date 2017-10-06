#include <string>
#include <string.h>
#include <iostream>
#include <vector>
#include <tuple>

#include "../cluster/cluster.h"

using namespace std;



int testCluster(){
  int pass = 0;

  vector<double> a = { 1, 2, 3 ,5};
  vector<double> b = {  1, 2, 3 ,5};
  vector<double> c = {  1, 2, 3 ,5};
  vector<double> d = {  1, 2, 3 ,5};
  vector<double> e = { 6, 1, 1, 1};
  vector<double> f = { 62, 239, 1, 0};
  vector<double> g = { 23, 52, 11, 9};
  vector<double> h = { 33, 11, 10, 3};
  vector<double> i = { 1, 1, 1, 1};

  vector<vector<double>> test;
  test.push_back( b);
  test.push_back( d);
  test.push_back( e);
  test.push_back( f);
  test.push_back( g);
  test.push_back( c);
  test.push_back( h);
  test.push_back( i);
  test.push_back( a);

  vector<double> docs = { 1, 2, 3, 4, 5, 6, 7, 8, 9};
  vector< tuple<int,vector<double>>> V;

  for( unsigned int j = 0; j < docs.size(); j++){
    V.push_back( make_tuple( docs[j], test[j]));
  }

  int k = 3;
  vector<vector<int>> res = cluster( V, k);


  for( int i = 0; i < k; i++){
    cout << i + 1 << "\t";
    for( unsigned int j = 0; j < res[i].size(); j++){
      cout << res[i][j] <<",";
    }
    cout << endl;
  }

  

  return pass;
}