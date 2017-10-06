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


void term:: addBOccurance( int docID , int pos){
// add occurance in the body of the document to the postings list of the term
  // search for doc
  for( vector<doc>::iterator i = postings.begin(); i != postings.end();  i++){
    //cout << 1 << endl;
    if( i->getID() == docID){
      i->addBIndex( pos);
      return;
    }
  }
  

  // doc is not in the term's postings list
  df++;
  doc _doc( docID);
  _doc.addBIndex( pos);
  postings.push_back( _doc);
}

void term:: addTOccurance( int docID , int pos){
// add occurance in the title of the document to the postings list of the term
  // search for doc
  for( vector<doc>::iterator i = postings.begin(); i != postings.end();  i++){
    //cout << 1 << endl;
    if( i->getID() == docID){
      i->addTIndex( pos);
      return;
    }
  }
  

  // doc is not in the term's postings list
  df++;
  doc _doc( docID);
  _doc.addTIndex( pos);
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

// return the actual term value
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

// get the docs for the title occurences
vector<int> term:: getTDocs(){
  vector<int> outpt;
  
  for( vector<doc>::iterator i = postings.begin(); i != postings.end();  i++){
    if( i->hasTitle() == 0){
      continue;
    }  
    outpt.push_back(i->getID());
  }

  return outpt;

}

// get the docs for the body occurences
vector<int> term:: getBDocs(){
  vector<int> outpt;
  
  for( vector<doc>::iterator i = postings.begin(); i != postings.end();  i++){
    if( i->hasBody() == 0){
      continue;
    }  
    outpt.push_back(i->getID());
  }

  return outpt;

}

// get the title indexes of a document for a term
vector<int> term:: getTDocIndexes( int docId){
  for( vector<doc>::iterator i = postings.begin(); i != postings.end();  i++){
    if( i->getID() == docId){
      return i->getTIndexes();
    }
  }

  // return empty vector if document doesn't exist
  vector<int> temp;
  return temp;

}

// get the body indexes of a document for a term
vector<int> term:: getBDocIndexes( int docId){
  for( vector<doc>::iterator i = postings.begin(); i != postings.end();  i++){
    if( i->getID() == docId){
      return i->getBIndexes();
    }
  }

  // return empty vector if document doesn't exist
  vector<int> temp;
  return temp;

}


