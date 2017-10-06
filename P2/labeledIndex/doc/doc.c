#include <string>
#include <vector>
#include <tuple>
#include <iostream>
#include <math.h>
#include <algorithm> //find

#include <fstream>
#include <iostream>

#include "doc.h"

using namespace std; 



doc::doc( int id){
  docID = id;
  tf = 0;
  tf_idf = 1;
}

void doc:: addIndex( int pos){
// update doc posting list
  tf++;
  index.push_back( pos);

}



int doc:: getID(){
  return docID;
}

void doc:: printPostings(){
  cout << docID << ": " ;

  // print title occurrences
  for( vector<int>::iterator i = index.begin(); i != index.end() - 1;  i++){
    cout << *i << "," ;
  }

  cout << *(index.end()-1);
  cout << "; ";

}


void doc:: setTfIdf( int ndoc, int df){

  tf_idf = log( (double)ndoc / (double)df);

}

int doc:: getTf(){
  return tf;
}


string doc:: output (){
  string out = "*doc " + to_string( getID()) + " ";

  // print title occurrences
  for( vector<int>::iterator i = index.begin(); i != index.end();  i++){
    out = out + to_string( *i) + " ";
  }


  return out;
}

vector<int> doc:: getIndexes(){
  return index;
}


