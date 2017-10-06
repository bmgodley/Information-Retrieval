#include <string>
#include <iostream> 
#include <vector>
#include <map>
#include <tuple>

#include "knnClassifier/classifier.c"
#include "knnClassifier/classifier.h"

#include "labeledIndex/labeledIndex/labeledIndex.h"
#include "labeledIndex/labeledIndex/labeledIndex.c"
#include "labeledIndex/term/term.h"
#include "labeledIndex/term/term.c"
#include "labeledIndex/doc/doc.h"
#include "labeledIndex/doc/doc.c"

using namespace std;

// labeled index: inverted index for title and body


int main( int argc, char* argv[]){

  if( argc != 4){
    cout << "\nIncorrect number of arguments \nCorrect usage: './create_labeled_index <index dir> <k> <query doc location>'\n";
    
    return 1;
  } 

  // get index directory from the arguments
  string iname;
  iname.append( argv[1]);

  // get k
  int k = atoi( argv[2]);

  // get the query
  string qname;
  qname.append( argv[3]);

  // create and load the index
  labeledIndex Ind;
  if( Ind.input( iname) == 1){
    return 1;
  }

  // read the query document
  if( Ind.readQFile( qname) == 1){
    return 1;
  }

  int t;
  // classify the document
  vector<tuple<int,double>> res = knnClassify( Ind, k);
  
  // print the results
  for( unsigned int i = 0; i < res.size(); i++){

    t = get<0>( res[i]);


    cout << Ind.getClassName(t) << " ";
  }
  cout << endl;


  return 0;
}
