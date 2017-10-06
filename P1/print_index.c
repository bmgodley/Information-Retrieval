#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <vector>


#include "dataStructures/invertedIndex/invertedIndex.h"
#include "dataStructures/invertedIndex/invertedIndex.c"
#include "dataStructures/term/term.h"
#include "dataStructures/term/term.c"
#include "dataStructures/doc/doc.h"
#include "dataStructures/doc/doc.c"

using namespace std;


int main( int argc, char* argv[]){

  // check for correct arguments
  if( argc != 2){
    cout << "\nIncorrect number of arguments \nCorrect usage: './create_index <inverted index location>'\n\n";
    return 1;
  }

  // copy dir name
  int len = strlen(argv[1]);
  string dName;
  dName.assign( argv[1], len);

  
  invertedIndex Inv; 


  if( Inv.input(dName) == 1){
    return 1;
  }

  Inv.printInv();


  return 0;
}