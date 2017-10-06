#include <string>
#include <string.h>
#include <iostream>
#include <vector>
#include <tuple>
#include <map>
#include <math.h>

#include "cluster.h"


using namespace std;


/* algorithm
1 select k random seeds
2 create K vectors with the random seeds
3 while( the vectors change in the iteration)
4 for each vector 
    create an empty vector 
        
*/

vector<double> vecSub( vector<double> a, vector<double> b){
  // subtract 2 vectors, assume same length
  vector<double> c = a;
  for( unsigned int i = 0; i < a.size(); i++){
    c[i] = a[i] - b[i];
  }
  return c;
}

// normalize a vector
vector<double> normalizeVec( vector<double> a){
  vector<double> outpt;
  for( vector<double>::iterator it = a.begin(); it != a.end(); it++){
    outpt.push_back( *it);
  }
  double len = getVecLen( outpt);
  for( vector<double>::iterator it = outpt.begin(); it != outpt.end(); it++){
    *it = *it/len;
  }
  return outpt;
}

// get the legth of the vector
double getVecLen( vector<double> v){
  double sum = 0;
  for( vector<double>::iterator it = v.begin(); it != v.end(); it++){
    sum += (*it) * (*it);
  }
  sum = sqrt( sum);
  return sum;
}

// given a vector a and centroid matrix. return which centroid changes the least 
// when the vector is subtracted
int argMin( vector<double> a, vector< vector<double>> cents){
  double minLen = getVecLen( vecSub( a, cents[0])); 
  int ind = 0;
  vector<double> temp;

  for( unsigned int i = 1; i < cents.size(); i++){
    temp = vecSub( a, cents[i]);
    if( minLen > getVecLen( temp)){
      minLen = getVecLen( temp);
      ind = i;
    }
  }
  return ind;
}

// given a doc id and a list of docId, vector pairs, return the coresponding vector
vector<double> getVec( vector< tuple< int, vector<double>>> V, int docId){
  // given the document id return the vector of the document
  // assume that the doc is in the set
  for( vector< tuple< int, vector<double>>>::iterator it = V.begin(); it != V.end(); it++){
    if( get<0>(*it) == docId){
      return get<1>(*it);
    }
  }
  vector<double> outpt;
  return outpt;
}

/*
void printVec( vector<auto> a){
  for( unsigned int i = 0; i < a.size(); i++){
    cout << a[i] << " ";
  }
  cout << endl;
}


void printMatrix( vector<vector<auto>> a){
  for( unsigned int i = 0; i < a.size(); i++){
    printVec( a[i]);
  }
  cout << endl;
}
*/


// given a list of vectors calculate the centeroid 
vector<double> calcCent( vector<int> v, vector<tuple<int,vector<double>>> dic){
  vector<double> outpt = getVec( dic, v[0]);
  vector<double> temp;

  for( vector<int>::iterator it = v.begin() + 1; it != v.end(); it++){
    temp = getVec( dic, *it);
    for( unsigned int j = 0; j < outpt.size(); j++){
      outpt[j] += temp[j];
    }
  }

  return normalizeVec( outpt);

}




// cluster documents together in k groups
vector< vector <int>> cluster( vector< tuple< int, vector<double>>> V, int k){
  vector<int> temp; // empty vector used to create the clusters vector
  vector<double> tmp; // empty vector used to create the centroids vector
  vector< vector<int>> outpt; // k length vector containing a vector for the documents that are in its class
  vector< vector<int>> empty; // k length vector used for clearing outpt in the loop
  vector< vector<double>> cents; // vector of the centroids
  vector<int> docs;

  // create docs list
  for( vector< tuple<int,vector<double>>>::iterator it = V.begin(); it != V.end(); it++){
    docs.push_back( get<0>( *it));
  }

  // build the vector of vectors to hold the clusters
  // bulid the centroids vector
  // build the initial W vector
  for( int i = 0; i < k; i++){
    outpt.push_back( temp);
    empty.push_back( temp);
    cents.push_back( tmp);

  }


  int j = 0;
  // "randomly" build the vectors
  for( vector<int>::iterator it = docs.begin(); it != docs.end(); it++){
    if( j == k){
      j = 0;
    }
    outpt[j].push_back( *it);
    j++;
  }


  // initialize the centroids
  for( int i = 0; i < k; i++){
    cents[i] = calcCent( outpt[i], V);
 
  }


  int I;
  vector< vector<int>> old; // the old cluster values before they change in the loop iteration
  while( true){
    // 
    old = outpt; // copy outpt into old 
    outpt = empty;// clear contents of the k vectors


    //reassignment of vectors
    for( vector<int>::iterator it = docs.begin(); it != docs.end(); it++){
      I = argMin( getVec( V,*it), cents);
      outpt[I].push_back( *it);
    }

    // recomputation of centroids
    for( int i = 0; i < k; i++){
      cents[i] = calcCent( outpt[i], V);
    }


    // if the old vector is the same as the new vector then break
    if( old == outpt){
      break;
    }

  }

  return outpt;

}
