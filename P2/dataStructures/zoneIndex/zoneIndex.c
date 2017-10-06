
#include <dirent.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <vector>
#include <iostream>
#include <math.h>
#include <algorithm> //find

#include <fstream>
#include <iostream>

#include "zoneIndex.h"

#include "../doc/doc.h"
#include "../term/term.h"

using namespace std; 







int getId( string filepath){
  // extract the id of the doc
  // folder/id.txt -> id
  int t;
  string filename = filepath;

  try{
    while(true){
      // get the file name
      t = filename.find("/");
      if( t == -1){
        // break if it is the filename 
        break;
      }
      // update the filename 
      filename = filename.substr( t + 1);
    
    }
  } catch (... ) {
    // fails with directory "." 
    return -1; //will be skipped over
  }

  t = filename.find(".");
  filename = filename.substr( 0, t);

  return atoi( filename.c_str());


}

// tokenize a word and output the value to input into the index
string tokenize( string word){
  string newWord = word; 
// remove punctuation
  int pos = 0;
  for( string::iterator i = word.begin(); i != word.end(); i++){ 
    if( charCheck(*i) == 0){
    //delete invalid character
      newWord.erase(newWord.begin() + pos);
    } else {
    // else increment position
      pos++;
    }
  }
// to lower case
  transform( newWord.begin(), newWord.end(), newWord.begin(), (int (*)(int)) tolower );

  return newWord;

}


bool charCheck( char c){
// return false if the character should be removed from the string
  // doesn't account for the curled "" marks or ... 
  string invalid = "-_=+,.!? `~  @—#$ ;:[]()?{“”''’}| ]\n^&\t/\"\'";
  size_t pos;

  if( (pos = invalid.find( c)) != string::npos ) {
    return 0;
  }
  return 1;

}





int zoneIndex:: invSearch( string token){
// function that finds the index to insert the term into the inverted index
// used to keep every term in order

  int dist = 0;
  for( vector<term>::iterator i = v.begin(); i != v.end();  i++){

    if( i->getToken().compare( token) == 0 ){
    // found the token in the inverted
      
      return dist;

     
    } else if( i->getToken().compare( token)  > 0 ){
    // token should have occured if it is in the inverted index
      if( dist == 0){
        return 0;

      } else {
        return dist;
      }

    } else {
      dist++;
    }
    

  }
  // finished searching list and term did not occur
  return dist;
}

  
void zoneIndex:: bOccurance( string token, int doc, int pos){
// handle occurance of a term in the body

  if( !(find( docList.begin(), docList.end(), doc) != docList.end())) {
  // new document
    docList.push_back( doc);
  }

  int index = invSearch( token);

  vector<term>::iterator a; 
  int size = v.size();

  if( index  == size){
  // case 1: new token needs to be added to the end of the list
    a = v.end();
    term temp( token);
    temp.addBOccurance( doc, pos);
    v.insert( a, temp);

  } else if( index == 0){
    a = v.begin();
    if( a->getToken().compare( token) == 0){
    // case 2: token is first in the index
      a->addBOccurance( doc, pos);
    } else {
    // case 3: create token and place in the front of the list
      term temp( token);
      temp.addBOccurance( doc, pos);
      v.insert( a, temp);
    }

  } else {
    a = v.begin() + index;
    if( a->getToken().compare( token) == 0){
    // case 4: token is in the middle of the index
      a->addBOccurance( doc, pos);
    } else {
    // case 5: create token and place in the middle of the index
      term temp( token);
      temp.addBOccurance( doc, pos);
      v.insert( a, temp);
    }
  }


}


void zoneIndex:: tOccurance( string token, int doc, int pos){
// handle occurance of a term in the title

  if( !(find( docList.begin(), docList.end(), doc) != docList.end())) {
  // new document
    docList.push_back( doc);
  }

  int index = invSearch( token);

  vector<term>::iterator a; 
  int size = v.size();

  if( index  == size){
  // case 1: new token needs to be added to the end of the list
    a = v.end();
    term temp( token);
    temp.addTOccurance( doc, pos);
    v.insert( a, temp);

  } else if( index == 0){
    a = v.begin();
    if( a->getToken().compare( token) == 0){
    // case 2: token is first in the index
      a->addTOccurance( doc, pos);
    } else {
    // case 3: create token and place in the front of the list
      term temp( token);
      temp.addTOccurance( doc, pos);
      v.insert( a, temp);
    }

  } else {
    a = v.begin() + index;
    if( a->getToken().compare( token) == 0){
    // case 4: token is in the middle of the index
      a->addTOccurance( doc, pos);
    } else {
    // case 5: create token and place in the middle of the index
      term temp( token);
      temp.addTOccurance( doc, pos);
      v.insert( a, temp);
    }
  }


}


void zoneIndex::printInv(){
// print the inverted index to the command line
  for( vector<term>::iterator i = v.begin(); i != v.end();  i++){
    i->printOccurance();
  }

}


int zoneIndex:: output ( string filename){
// output the inverted index to file
  ofstream f; 
  f.open( filename.c_str());
  if( !f.is_open()){ 
  //Check if  file is open
    cout << "ERROR reading file: " << filename << endl;
    return(1);
  }
  for( vector<term>::iterator i = v.begin(); i != v.end();  i++){
    f << i->output();
  }
  f.close();

  cout << "\nsuccessfully wrote zone index to: " << filename << endl;

  return 0;
}


int zoneIndex:: input( string filename){
// input an inverted index from file
  // assume that an empty inverted Index is given
  ifstream f; 
  string word;

  f.open( filename.c_str());
  if( !f.is_open()){ 
  //Check if  file is open
    cout << "ERROR reading file: " << filename << endl;
    return(1);
  }

  string term;
  int docId = 0;
  int title = 0; // 0 for a title, 1 for body


  while( f >> word){
    if( word.compare("*term") == 0){
    // next term will be the term
      f >> word;
      term = word;
      title = 0; // next occurrences will be in the title

    } else if( word.compare("*doc") == 0){
    // next term will be the docId
      f >> word;
      docId = atoi( word.c_str());

    } else if( word.compare( "*body") == 0){
      title = 1;  // next occurrences will be in the body

    } else {
      if( title == 0){
        tOccurance( term, docId, atoi( word.c_str()));
      } else {
        bOccurance( term, docId, atoi( word.c_str()));
      }   

    }
 
  }
  f.close();
  return 0;

}

// read a directory and load the terms into the index
int zoneIndex:: readDir( string dirname){
 
// initialize for navigating directory 
  DIR *dir;            // pointer to directory
  struct dirent *file; // directory files (assuming that there are only files in the directory, and all files are valid)
  string filepath;     // relative filepath to file
  string docName;

// open directory
  dir = opendir( dirname.c_str());
  if( !dir){                 
  // check if directory is open
    cout << "ERROR: Directory does not exist" << endl;
    return 1;
  }


// read directory
  while( (file = readdir( dir)) != NULL ){
    if(strlen( file->d_name) < 3){
      continue; // skip for dir . and ..
    }

    filepath = dirname + "/" + file->d_name;
    docName = file->d_name;
    
    readFile( filepath);


    


  }


// close directory
  closedir( dir);
  return 0;

}

// read a file and load the terms into the index
int zoneIndex:: readFile( string filepath){
// initialize for reading files
  string word;         // placeholder for words
  string temp;
  ifstream f;          // object to read files
  int index;
  int docId = getId( filepath);
  int t;


  //cout << filepath << endl;
// open file
  f.open( filepath.c_str());
  if( !f.is_open()){ 
  //Check if  file is open
    cout << "ERROR reading file: " << filepath << endl;
    return 1;
  }


  index = 0;

  // get title of the document
  getline( f, word);
  bool loop = true;
  while( loop){
    t = word.find(" ");
    if( t == -1){
      loop = false;
      temp = word;
    } else{
      temp = word.substr( 0, t);
      word = word.substr(t + 1);

     
    }
    temp = tokenize( temp);
    tOccurance( temp, docId, index);
    index++;



  }





  index = 0;
  // read body of file
  while( f >> word){
    // tokenize the word
    word = tokenize( word);

    if ( word.length() == 0){
      continue;
    }
  // preprocess the token
    //word = preprocess( word);

  // Index the token
    //if(word == NULL){
      bOccurance( word, docId, index);
    //}
    index++;
    
    
  }
  f.close();
  return 0;
}


vector<int> zoneIndex:: getDocs(){
  return docList;
}  


// given a keyword, return the documents where the word occurs in the title
vector<int> zoneIndex:: getTKeywordDocs( string keyword){
  vector<int> outpt;
  int index;


  if( ( index = keyword.find(" ")) != -1){
    // keyword is a phrase
    return getTPhraseDocs( keyword);
  }

  keyword = tokenize( keyword);
  for( vector<term>::iterator i = v.begin(); i != v.end();  i++){
    if( keyword.compare( i->getToken()) == 0){
      return i->getTDocs();

    }
  }

  return outpt;
  
}

// given a phrase, return the documents where the phrase occurs in the title
vector<int> zoneIndex:: getTPhraseDocs( string phrase){
  // split the phrase into a list of strings
  vector<string> keywords;
  string temp;
  int b;

  while( ( b = phrase.find(" ")) != -1){
    temp = phrase.substr(0, b);
    keywords.push_back( temp);
    phrase = phrase.substr( b + 1);
  }
  keywords.push_back( phrase);


  vector<int> docs = getTKeywordDocs( keywords[0]);

  vector<int> tempList;



  // loop through keywords and make a list of documents that they all occur in
  for( unsigned int i = 1; i < keywords.size(); i++){
    // loop through docs list
    tempList = getTKeywordDocs( keywords[i]);
    for( unsigned int j = 0; j < docs.size(); ){
      if( find( tempList.begin(), tempList.end(), docs[j]) != tempList.end()){
        j++;
      } else {
        // delete documents that arent common between the words
        docs.erase( docs.begin() + j);
      }
    }
  } 


  vector<int> outpt;
  vector<int> tempPos;
  vector<int> pos;


  // loop through common doc list
  for( unsigned int d = 0; d < docs.size(); d++){

    pos = getTIndexes( docs[d], keywords[0]);
    // loop through keyword list
    for( unsigned int f = 1; f < keywords.size(); f++){
      tempPos = getTIndexes( docs[d], keywords[f]);

      pos = compareIndexes( pos, tempPos, f);


    }

    if( !pos.empty()){
      outpt.push_back(  docs[d]);
    }

  }
  return outpt;

}

// given a keyword, return the documents where the word occurs in the body
vector<int> zoneIndex:: getBKeywordDocs( string keyword){
  vector<int> outpt;
  int index;


  if( ( index = keyword.find(" ")) != -1){
    // keyword is a phrase
    return getBPhraseDocs( keyword);
  }

  keyword = tokenize( keyword);
  for( vector<term>::iterator i = v.begin(); i != v.end();  i++){
    if( keyword.compare( i->getToken()) == 0){
      return i->getBDocs();

    }
  }

  return outpt;
  
}


// given a phrase, return the documents where the phrase occurs in the body
vector<int> zoneIndex:: getBPhraseDocs( string phrase){
  // split the phrase into a list of strings
  vector<string> keywords;
  string temp;
  int b;

  while( ( b = phrase.find(" ")) != -1){
    temp = phrase.substr(0, b);
    keywords.push_back( temp);
    phrase = phrase.substr( b + 1);
  }
  keywords.push_back( phrase);


  vector<int> docs = getBKeywordDocs( keywords[0]);
  vector<int> tempList;



  // loop through keywords and make a list of documents that they all occur in
  for( unsigned int i = 1; i < keywords.size(); i++){
    // loop through docs list
    tempList = getBKeywordDocs( keywords[i]);
    for( unsigned int j = 0; j < docs.size(); ){
      if( find( tempList.begin(), tempList.end(), docs[j]) != tempList.end()){
        j++;
      } else {
        // delete documents that arent common between the words
        docs.erase( docs.begin() + j);
      }
    }
  } 



  vector<int> outpt;
  vector<int> tempPos;
  vector<int> pos;


  // loop through common doc list
  for( unsigned int d = 0; d < docs.size(); d++){

    pos = getBIndexes( docs[d], keywords[0]);
    // loop through keyword list
    for( unsigned int f = 1; f < keywords.size(); f++){
      tempPos = getBIndexes( docs[d], keywords[f]);

      pos = compareIndexes( pos, tempPos, f);


    }

    if( !pos.empty()){
      outpt.push_back(  docs[d]);
    }

  }
  return outpt;

}


// given a docId and keyword, return the indexes where the keyword appears in the title
vector<int> zoneIndex:: getTIndexes( int docId, string keyword){
  vector<int> outpt;
  keyword = tokenize( keyword);

  for( vector<term>::iterator i = v.begin(); i != v.end();  i++){
    if( keyword.compare( i->getToken()) == 0){
      return i->getTDocIndexes( docId);

    }
  }

  return outpt;
}


// given a docId and keyword, return the indexes where the keyword appears in the body
vector<int> zoneIndex:: getBIndexes( int docId, string keyword){
  vector<int> outpt;
  keyword = tokenize( keyword);

  for( vector<term>::iterator i = v.begin(); i != v.end();  i++){
    if( keyword.compare( i->getToken()) == 0){
      return i->getBDocIndexes( docId);

    }
  }

  return outpt;
}



// function used to check if two terms are adjacent in the document
vector<int> zoneIndex:: compareIndexes( std::vector<int> a, std::vector<int> b, int offset){

  // decrement b vector by offset
  for( unsigned int i = 0; i < b.size(); i++){
    b[i] = b[i] - offset;
  }
  
  // loop through a, if an element in b appears in a keep it, else delete it
  for( unsigned int j = 0; j < a.size(); ){
              
    if( find( b.begin(), b.end(), a[j]) != b.end()){
      j++;
    } else {
      a.erase( a.begin() + j);
    }

  }



  return a;
}


