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


using namespace std;

// evaluate boolean queries
    /*
    INPUT: tuple representing tree node:
       ('KEYWORD', keyword)
       ('PHARSE', "keyword_1 ... keyword_n")
       ('AND'/'OR', operand_1, operand_2)
    */



/** 
 *
 */





// Evaluate
// void boolean_queary( vector<int> docList, string query){
//     //split query into a list
//     //vector<string> Query = split(query);  // 
//     int i= 0;
//     string q; // placeholder for the current query term

//     // read the query
//     while(true){
//       // get currunt term
//       q = Query[i];
      

      



//     }

// }




/*        
  input: "(stemming AND off) AND of"
*/


int main( int argc, char* argv[]){
// get inverted index

  if( argc != 3){
    cout << "\nIncorrect number of arguments \nCorrect usage: './boolean_query <inverted index location> <\'query\'>'\n";
    
    if( argc > 3){
      cout << "Enclose the query in single quotes (\'\')" << endl;
      cout << "Enclose phrases in double quotes (\"\")" <<endl << endl;
    }
    return 1;
  } 
  // extract index location and query from inputs
  int len = strlen(argv[1]);
  string invLocation;
  invLocation.assign( argv[1], len);

  string inQuery;
  inQuery.append( argv[2]);


  // create and load inverted index
  invertedIndex Inv;
  Inv.input( invLocation);


  vector<string> q = parseQuery( inQuery);

  vector<int> docs = eval( Inv, q);

  cout << "Output: ";
  printVec( docs);


  


  //string query = "(stemming AND off) AND of";
  //parseQuery( query);

/*

  raw_query = "(stemming AND off) AND of"
// parse query
  query = parse(raw_query)

// optimize query
  optimized_query = optimize(query)


*/
  return 0;

}