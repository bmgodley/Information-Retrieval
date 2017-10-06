#include <vector>
#include <string>
#include <iostream>
#include <tuple>

#include "zoneScorer/zoneScorer.c"
#include "zoneScorer/zoneScorer.h"
#include "query/query.h"
#include "query/query.c"
#include "dataStructures/zoneIndex/zoneIndex.h"
#include "dataStructures/zoneIndex/zoneIndex.c"
#include "dataStructures/term/term.h"
#include "dataStructures/term/term.c"
#include "dataStructures/doc/doc.h"
#include "dataStructures/doc/doc.c"


using namespace std;


int main( int argc, char* argv[]){

  if( argc != 5){
    cout << "\nIncorrect number of arguments \nCorrect usage: './boolean_query <zone index location> <k> <g> <\'query\'>'\n";
    
    if( argc > 5){
      cout << "Enclose the query in single quotes (\'\')" << endl;
      cout << "Enclose phrases in double quotes (\"\")" << endl << endl;
    }
    return 1;
  } 

  // get the index location
  string indName;
  indName.append( argv[1]);

  // created and load index
  zoneIndex Ind;
  if( Ind.input( indName) == 1){
    return 1;
  }

  // get k and g 
  int k = atoi( argv[2]);
  float g = stof( argv[3]);

  //get the query
  string query;
  query.append( argv[4]);

  // score the query
  vector< tuple< int, float>> outpt = scoreQuery( Ind, query, k, g);

  // output the result
  int i = 0;
  for( vector< tuple< int, float>>::iterator dIt = outpt.begin(); dIt < outpt.end(); dIt++){
    cout << get<0>( *dIt) << " " << get<1>( *dIt) << endl;

    if( ++i == k){
      break;
    }
  }
  cout << endl;

  return 0;
}
