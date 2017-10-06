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


using namespace std;


int main( int argc, char* argv[]){

  // check for correct arguments

  if( argc != 3){
    cout << "\nIncorrect number of arguments \nCorrect usage: './create_index <dir> <index location>'\n\n";
    return 1;
  }


  // copy dir name
  int len = strlen(argv[1]);
  string dName;
  dName.assign( argv[1], len);

  // get index location
  string indLoc;
  indLoc.append( argv[2]);
  
  // create and load the index
  labeledIndex Inv;
  if( Inv.readDir( dName) == 1){
    return 1;
  }

  // write index to file
  Inv.output(indLoc);



  return 0;
}