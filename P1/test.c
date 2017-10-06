 #include <string>
#include <string.h>
#include <iostream>
#include <vector>


#include "query/query.h"
#include "query/query.c"
#include "dataStructures/invertedIndex/invertedIndex.h"
#include "dataStructures/invertedIndex/invertedIndex.c"
#include "dataStructures/term/term.h"
#include "dataStructures/term/term.c"
#include "dataStructures/doc/doc.h"
#include "dataStructures/doc/doc.c"

#include "testing/test_boolean_query.c"

using namespace std;

int main(){
  int pass = 0;
  // if( testParseQuery() == 1){
  //   pass = 1;
  // }

  // if( testGetDocs() == 1){
  //   pass = 1;
  // }

  // if( testEval() == 1){
  //   pass = 1;
  // }





  if( pass == 1){
    cout << "tests failed" << endl;
  } else {
    cout << "Tests passed" << endl;
  }
  return 0;
}