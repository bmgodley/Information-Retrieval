
#include <dirent.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>

#include <string>
#include <vector>
#include <tuple>
#include <iostream>
#include <math.h>
#include <algorithm> //find

#include <fstream>
#include <iostream>


#include "../doc/doc.h"


using namespace std; 


// fuction declarations for class term
term:: term( string _token){
  token = _token;
  df = 0;
}


void term:: addOccurance( int docID , int pos){
// add occurance in document to the postings list of the term
  // search for doc
  for( vector<doc>::iterator i = postings.begin(); i != postings.end();  i++){
    //cout << 1 << endl;
    if( i->getID() == docID){
      i->addIndex( pos);
      return;
    }
  }
  

  // doc is not in the term's postings list
  df++;
  doc _doc( docID);
  _doc.addIndex( pos);
  postings.push_back( _doc);
}

void term:: printOccurance(){
// print the postings list of the term
  cout << getToken() << " \t";
  for( vector<doc>::iterator i = postings.begin(); i != postings.end();  i++){
    i->printPostings();
  }
  cout << endl;
}

vector<doc> term:: getPostings(){
  return postings;
}

string term:: getToken(){
  return token;
}

int term:: getDf(){
  return df;
}




string term:: output (){
// output the posing list of the term to a file
  string out = "*term " + getToken() + " ";

  for( vector<doc>::iterator i = postings.begin(); i != postings.end();  i++){
    out = out + i->output ();
  }

  return out;
}

vector<int> term:: getDocs(){
  vector<int> outpt;

  for( vector<doc>::iterator i = postings.begin(); i != postings.end();  i++){
    outpt.push_back(i->getID());
  }

  return outpt;

}

// get the indexes of a document for a term
vector<int> term:: getDocIndexes( int docId){
  for( vector<doc>::iterator i = postings.begin(); i != postings.end();  i++){
    if( i->getID() == docId){
      return i->getIndexes();
    }
  }

  // return empty vector if document doesn't exist
  vector<int> temp;
  return temp;

}


double term:: getLTF( int docId){
  // get the log term frequency for a given doc


  for( vector<doc>::iterator it = postings.begin(); it != postings.end(); it++){
    if( docId == it->getID()){
      return 1 + log10( it->getTf());
    }
  }
  return 0;

}
