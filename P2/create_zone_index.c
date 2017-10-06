#include <string>
#include <iostream> 
#include <vector>

#include "dataStructures/zoneIndex/zoneIndex.h"
#include "dataStructures/zoneIndex/zoneIndex.c"
#include "dataStructures/term/term.h"
#include "dataStructures/term/term.c"
#include "dataStructures/doc/doc.h"
#include "dataStructures/doc/doc.c"

using namespace std;

// zone index: inverted index for title and body



int main( int argc, char* argv[]){

  if( argc != 3){
    cout << "\nIncorrect number of arguments \nCorrect usage: './create_zone_index <Document dir> <index dir>'\n";
    
    return 1;
  } 

  // get directory name from the arguments
  string dname;
  dname.append( argv[1]);

  // get index directory from the arguments
  string iname;
  iname.append( argv[2]);

  // create index 
  zoneIndex Ind;
  // read directory
  if( Ind.readDir( dname) == 1){
    return 1;
  }

  // write index to file
  Ind.output( iname);

  return 0;
}