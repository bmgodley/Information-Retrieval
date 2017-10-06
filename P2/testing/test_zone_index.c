#include <string>
#include <string.h>
#include <iostream>
#include <vector>
#include <tuple>

#include "../dataStructures/zoneIndex/zoneIndex.h"
#include "../zoneScorer/zoneScorer.h"

using namespace std;




int testZoneIndex(){
  int pass = 0;
  int testNum = 0;
  int k = 3;

  string dir = "testing/documents";
  string outf = "zone_index_out.txt";
  string tquery;
  zoneIndex Ind;
  vector< tuple< int, float>> res;
  vector< int> test;
  vector< int> control;

  if( Ind.input( outf) == 1){
    pass = 1;
  }

  //Ind.printInv();


  // test 1
  test.clear();
  testNum++;
  tquery = "interstellar OR DNA";
  control = { 0, 1, 25};
  res = scoreQuery( Ind, tquery, k, 0.5);

  for( vector< tuple< int, float>>::iterator dIt = res.begin(); dIt < res.end(); dIt++){
    test.push_back( get<0>(*dIt));
  }
  
  if( test != control){
    cout << "> zoneIndex test: " << testNum << " failed" << endl;
    pass = 1; // fail
  }


  // test 2
  test.clear(); 
  testNum++;
  tquery = "\"Fight club\" OR the";
  control = { 2, 0, 25};
  res = scoreQuery( Ind, tquery, 3, 0.5);
  
  for( vector< tuple< int, float>>::iterator dIt = res.begin(); dIt < res.end(); dIt++){
    test.push_back( get<0>(*dIt));
  }
  
  if( test != control){
    cout << "> zoneIndex test: " << testNum << " failed" << endl;
    pass = 1; // fail
  }

  // test 2
  test.clear(); 
  testNum++;
  tquery = "\"we see the\"";
  control = { 1, 0};
  res = scoreQuery( Ind, tquery, 2, 0.5);
  
  for( vector< tuple< int, float>>::iterator dIt = res.begin(); dIt < res.end(); dIt++){
    test.push_back( get<0>(*dIt));
  }
  
  if( test != control){
    cout << "> zoneIndex test: " << testNum << " failed" << endl;
    pass = 1; // fail
  }


  return pass;
}