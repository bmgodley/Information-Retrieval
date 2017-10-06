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

  if( argc != 3){
    cout << "\nIncorrect number of arguments \nCorrect usage: './create_labeled_index <Document dir> <index dir>'\n";
    
    return 1;
  } 

  // get directory name from the arguments
  string dname;
  dname.append( argv[1]);

  // get index directory from the arguments
  string iname;
  iname.append( argv[2]);

  // create index and read directory
  labeledIndex Ind;
  if( Ind.readDir( dname) == 1){
    return 1;
  }
  // write index to file
  Ind.output( iname);

  return 0;
}