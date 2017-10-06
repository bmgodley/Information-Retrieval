#include <string>
#include <string.h>
#include <iostream>
#include <vector>
#include <tuple>
#include <map>
#include <math.h>

#include "classifier.h"


using namespace std;

/*
void printVec( vector<auto> a){
  for( unsigned int i = 0; i < a.size(); i++){
    cout << a[i] << " ";
  }
  cout << endl;
}
*/

double getVecLen( vector<double> v){
  double sum = 0;
  for( vector<double>::iterator it = v.begin(); it != v.end(); it++){
    sum += (*it) * (*it);
  }
  sum = sqrt( sum);
  return sum;
}

// function to calculate the cosine similarity of two vectors
double cosSim( vector<double> a, vector<double> b){
  double dotProd = 0;
  for( unsigned int i = 0; i < a.size(); i++){
    dotProd += a[i] * b[i];
  }

  double aLen = getVecLen(a);
  double bLen = getVecLen(b);

  return dotProd / ( aLen * bLen);
}


// get the k closest neigbors of the query document
vector<tuple< int, double>> knnClassify( labeledIndex Ind, int k){
  int qDoc = -1; // index of the input doc

  vector<int> docList = Ind.getDocs();
  // last element in this list is the input doc, delete it
  docList.erase( docList.end() -1);

  vector<double> sim; // hold the cosine similarity of the docs to the input doc


  vector<double> qDocVec = Ind.getVector( qDoc);
  vector<double> lDocVec;

  // loop through the document list and calculate the cosSim of each document compared to the query doc
  for( vector<int>::iterator it = docList.begin(); it != docList.end(); it++){

    lDocVec = Ind.getVector( *it);
    sim.push_back( cosSim( qDocVec, lDocVec));
  }

  vector<tuple< int, double>> outpt;

  int maxId;
  double maxCS;
  int maxI;


  // loop k times to get the k higest values
  for( int i = 0; i < k; i++){
    maxId = 0;
    maxCS = 0;
    // loop through the sim vector to find the highest CS score
    for( unsigned int j = 0; j < sim.size(); j++){
      if( sim[j] > maxCS){
        maxId = docList[j];
        maxCS = sim[j];
        maxI = j;
      }
    }
    outpt.push_back( make_tuple( maxId, maxCS));
    sim.erase( sim.begin() + maxI);
    docList.erase( docList.begin() + maxI);
  }

  return outpt;
}







