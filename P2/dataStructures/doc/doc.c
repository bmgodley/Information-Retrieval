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

void doc:: addBIndex( int pos){
// update body doc posting list
  tf++;
  bIndex.push_back( pos);

}

void doc:: addTIndex( int pos){
// update title doc posting list
  tf++;
  tIndex.push_back( pos);
  
}

int doc:: getID(){
  return docID;
}

void doc:: printPostings(){
  cout << docID << ":";

  // print title occurrences
  if( !tIndex.empty()){
    cout << " Title: " ;
    for( vector<int>::iterator i = tIndex.begin(); i != tIndex.end() - 1;  i++){
      cout << *i << "," ;
    }
    cout << *(tIndex.end()-1);
    cout << "| ";
  }

  if( !bIndex.empty()){
    // print body occurrences 
    cout << " Body: " ;
    for( vector<int>::iterator i = bIndex.begin(); i != bIndex.end() - 1;  i++){
      cout << *i << "," ;
    }
    cout << *(bIndex.end()-1);
    cout << "; ";
  }
}


void doc:: setTfIdf( int ndoc, int df){

  tf_idf = log( (double)ndoc / (double)df);

}

int doc:: getTf(){
  return tf;
}


string doc:: output (){
  // return a string to write to a file
  string out = "*doc " + to_string(getID()) + " ";

  // print title occurrences
  for( vector<int>::iterator i = tIndex.begin(); i != tIndex.end();  i++){
    out = out + to_string( *i) + " ";
  }

  out = out + "*body" + " ";
  // print body occurrences
  for( vector<int>::iterator i = bIndex.begin(); i != bIndex.end();  i++){
    out = out + to_string( *i) + " ";
  }

  return out;
}

// get title indexes
vector<int> doc:: getTIndexes(){
  return tIndex;
}

// get body indexes
vector<int> doc:: getBIndexes(){
  return bIndex;
}


int doc:: hasTitle(){
  // return 0 if empty, i if not
  if( tIndex.empty()){
    return 0;
  } else { 
    return 1;
  }
}

int doc:: hasBody(){
  // return 0 if empty, i if not
  if( bIndex.empty()){
    return 0;
  } else { 
    return 1;
  }
}