#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <vector>
#include <map>


#include "labeledIndex/labeledIndex/labeledIndex.h"
#include "labeledIndex/labeledIndex/labeledIndex.c"
#include "labeledIndex/term/term.h"
#include "labeledIndex/term/term.c"
#include "labeledIndex/doc/doc.h"
#include "labeledIndex/doc/doc.c"

#include "cluster/cluster.c"
#include "cluster/cluster.h"


using namespace std;


int main( int argc, char* argv[]){

  // check for correct arguments
  if( argc != 3 && argc < 4){
    cout << "\nIncorrect number of arguments \nCorrect usage: './k_means_clusterer <index location> <k> <(optional) index>'\n\n";
    return 1;
  } 


  // get the index location
  string indLoc;
  indLoc.append( argv[1]);

  // create and load index 
  labeledIndex Ind;
  Ind.input( indLoc);

  // get k
  int k = atoi( argv[2]);

  // load the vectors
  vector<tuple<int,vector<double>>> V;
  if( argc == 3){
    V = Ind.getVectors();
  } else {
    // if docId parameters were given load the specific docs
    vector<int> indexes;
    for( int i = 3; i < argc; i++){
      indexes.push_back( atoi( argv[i]));
    }
    V = Ind.getVectors( indexes);
  }

  // cluster the documents
  vector<vector<int>> res = cluster( V, k);

  // print the result
  for( int i = 0; i < k; i++){
    cout << i + 1 << "\t";
    for( unsigned int j = 0; j < res[i].size(); j++){
      cout << res[i][j] <<",";
    }
    cout << endl;
  }

  


  return 0;
}