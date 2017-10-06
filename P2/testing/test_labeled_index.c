#include <string>
#include <string.h>
#include <iostream>
#include <vector>
#include <tuple>
#include <map>
#include <math.h>

#include "../labeledIndex/labeledIndex/labeledIndex.h"
#include "../knnClassifier/classifier.h"

using namespace std;




int testLabeledIndex(){
  int pass = 0;
  int testNum = 0;
  string docDir = "../assignment2-data/class_data";
  string indF = "labeled_index_out.txt";
  string qDoc = "testing/documents/queryDoc.txt";
  
  labeledIndex Ind;
  // if( Ind.readDir( docDir) == 1){
  //   pass = 1;
  // }

  // if( Ind.output( indF) == 1){
  //   pass = 1;
  // }

  if( Ind.input( indF) == 1){
    pass = 1;
  }

  if( Ind.readQFile( qDoc) == 1){
    pass = 1;
  }

  vector<tuple<int,double>> outpt = knnClassify( Ind, 3);

  for( unsigned int i = 0; i < outpt.size(); i++){
    cout << get<0>(outpt[i]) << " | " << get<1>(outpt[i]) << endl;
  }


  // test 1
  testNum++;


  // if( test != control){
  //   cout << "> labeledIndex test: " << testNum << " failed" << endl;
  //   pass = 1; // fail
  // }





  return pass;
}