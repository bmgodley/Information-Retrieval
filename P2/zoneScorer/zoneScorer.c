#include <algorithm>
#include <vector>
#include <string>
#include <iostream>
#include <tuple>

#include "../dataStructures/zoneIndex/zoneIndex.h"
#include "../query/query.h"

using namespace std;



// score the document
float score( int _t, int _b, float g){
  float t = _t;
  float b = _b; 
  float outpt ;

  outpt = g * t + ( 1 - g) * b;
  return outpt;
}


// using a query get the weighted scores of documents
vector< tuple<int, float>> scoreQuery( zoneIndex Ind, std::string query, int k, float g){
  vector<string> q = parseQuery( query);
  
  vector< tuple<int, float>> outpt;

  vector<int> title = evalT( Ind, q);
  vector<int> body = evalB( Ind, q);

  vector<int> docs = Ind.getDocs();


   // iterator for the body vector


  int t;
  int b;
  float s;
  int a; // kep track if the tuple is added

  for(  vector<int>::iterator it = docs.begin(); it < docs.end(); it++){
    t = 0;
    b = 0;
    if( find( title.begin(), title.end(), *it) != title.end()){
      // if the title vector has the document in it
      t = 1;
    }

    if( find( body.begin(), body.end(), *it) != body.end()){
      // if the title vector has the document in it
      b = 1;
    }
 
    s = score( t, b, g);

    tuple<int,float> tup( *it, s);
    tuple<int,float> temp; 


    a = 0;
    for( vector< tuple< int, float>>::iterator dIt = outpt.begin(); dIt < outpt.end(); dIt++){
      temp = *dIt;
      if( get<1>( temp) < s){
        outpt.insert( dIt, tup);
        a = 1;
        break;
      }

    }

    if( a == 0){
      outpt.push_back( tup);
    }

    

  }

  // for( vector< tuple< int, float>>::iterator dIt = outpt.begin(); dIt < outpt.end(); dIt++){
  //   cout << get<0>( *dIt) << "|" << get<1>( *dIt) << endl;
  // }

  if( (int) outpt.size() > k){
    outpt.erase( outpt.begin() + k, outpt.end());
  }

  return outpt;

}



