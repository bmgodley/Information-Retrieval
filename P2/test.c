#include <string>
#include <string.h>
#include <iostream>
#include <vector>
#include <map>


#include "labeledIndex/labeledIndex/labeledIndex.c"
#include "labeledIndex/labeledIndex/labeledIndex.h"
#include "labeledIndex/term/term.c"
#include "labeledIndex/term/term.h"
#include "labeledIndex/doc/doc.c"
#include "labeledIndex/doc/doc.h"


#include "cluster/cluster.c"
#include "cluster/cluster.h"

#include "testing/test_cluster.c"

using namespace std;

int main(){
  int pass = 0;
  if( testCluster() == 1){
    pass = 1;
  }

 



  if( pass == 1){
    cout << "tests failed" << endl;
  } else {
    cout << "Tests passed" << endl;
  }
  return 0;
  
}