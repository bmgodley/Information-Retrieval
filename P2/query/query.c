
#include <string>
#include <stack>
#include <queue>
#include <iostream>
#include <tuple>
#include <algorithm>

#include "query.h"
#include "../dataStructures/zoneIndex/zoneIndex.h"



using namespace std;





/*

  boolean query( )
  


*/

/*
void printVec( vector<auto> a){
  for( int i = 0; i < (int) a.size(); i++){
    cout << a[i] << " ";
  }
  cout << endl;
}
*/





vector<string> parseQuery( string query){
// parse boolean queries 
  /*        
    input: "(stemming AND off) AND of"
    output: { "(stemming", "AND", "off)", "AND", "of"}
  */

  vector<string> outpt;
  string term;
  string phrase;
  int index;
  queue<string> Que;
  bool loop = true;
  //std::vector<int> level;
  //int lvl = 0;


  // build vector from the string
  while( loop){

    // get the next term in the query
    index = query.find(" "); 

    if (index == -1){
      // last term in the query
      loop = false;
      term = query;

    } else {
      term = query.substr(0, index);
      query = query.substr( index + 1); // remove term from query

    }


    // check if the term is in a phrase
    if( ( index = term.find("\"")) != -1){
      phrase = term.substr( 1);
      
      while(true){
        index = query.find(" "); 

        if (index == -1){
        // last term in the query
          loop = false;
          term = query;

        } else {
          term = query.substr(0, index);
          query = query.substr( index + 1); // remove term from query

        }

        // if a " is found then the term is a phrase. put the phrase in a single string
        if( ( index = term.find("\"")) != -1){

          if( (index + 2) == (int) term.size()){
            // term has a ")" at the end of the phrase. re-add it
            term.insert( index, ")");
            index++;
          }

          term = term.substr( 0, index);
          phrase.append(" ");
          phrase.append( term);
          term = phrase;
          break;

        } else {
          phrase.append(" ");
          phrase.append( term);
        }

      }

    }



    outpt.push_back( term);


  }

  return outpt;
}




// evaluate the query on the titles of documents
// return the document ids that are true
vector<int> evalT( zoneIndex Ind, vector<string> query){
  vector<int> outpt; 
  vector< vector<int>> Q; // vector of the postings for terms
  vector<int> level;  // vector to hold the depth of terms in the query
  int lvl = 0;      // current depth in query
  int index;
  vector<int> opVec; // vector for operator value to put in Q
  opVec.push_back( -1); // -1 for and, -2 for or

  string tstring;
  vector<int> temp;


  // read the query
  vector<string>::iterator it;
  for( it = query.begin(); it < query.end(); it++){
    // opretator check
    tstring = *it;

    // if the current turm is an operator, then add the corresponding value to the vector
    if( tstring.compare( "AND") == 0){
      // and operator
      opVec[0] = -1;
      Q.push_back( opVec);
      level.push_back( lvl);

      continue;
    } else if( tstring.compare( "OR") == 0){
      // or operator
      opVec[0] = -2;
      Q.push_back( opVec);
      level.push_back( lvl);

      continue;
    }



    // parenthesis check
    if( ( index = tstring.find( "(")) != -1){
      // has a ( at the start of the term, remove it and increase the depth
      tstring = tstring.substr( 1); 
      lvl++;
    } else if( (index = tstring.find( ")")) != -1){
      // has a ) at the end of the term, remove it and decrease the depth
      tstring = tstring.substr( 0, index);
      lvl--;
    }

    // get Doc list for the term and add it to Q

    Q.push_back( Ind.getTKeywordDocs( tstring));
    level.push_back( lvl);

  }

  // find deepest part of query
  int max = 0;
  for( unsigned int d = 0; d < level.size(); d++){
    if( level[d] > max){
      max = level[d];
    }
  }

  // starting with the deepest terms in the query. evaluate the query
  for( int m = max; m >= 0; m--){

    for(unsigned int i = 0; i < level.size(); i++){
      if( level[i] == m){
        temp = Q[i];

        // if the term is an operator
        if( !temp.empty() && temp[0] < 0){

          if( temp[0] == -1){
            // AND
            // combine the list before and after the term
            temp = AND( Q[i-1], Q[i+1]);
            Q[i] = temp;
            level[i]--;

            // delete the list before and after this term
            Q.erase( Q.begin() + i + 1);
            Q.erase( Q.begin() + i - 1);

            level.erase( level.begin() + i + 1);
            level.erase( level.begin() + i - 1);

            i = i - 2;

          } else if( temp[0] == -2){
            // OR
            // get the intersection of the list before and after the term
            temp = OR( Q[i-1], Q[i+1]);
            Q[i] = temp;
            level[i]--;

            // delete the lists before and after the term
            Q.erase( Q.begin() + i + 1);
            Q.erase( Q.begin() + i - 1);

            level.erase( level.begin() + i + 1);
            level.erase( level.begin() + i - 1);

            i = i - 2;

          }
        }
      }


    }

  
  }
  // return the first element in the postings vector
  // after the evaluation assume only one posting list in the vector 

  outpt = Q[0];
  return outpt;

}

// evaluate the query on the body of documents
// same a evalT but with calls to the body instead of the title
vector<int> evalB( zoneIndex Ind, vector<string> query){
  vector<int> outpt; 
  vector< vector<int>> Q; // vector of the postings for terms
  vector<int> level;  // vector to hold the depth of terms in the query
  int lvl = 0;      // current depth in query
  int index;
  vector<int> opVec; // vector for operator value to put in Q
  opVec.push_back( -1); // -1 for and, -2 for or

  string tstring;
  vector<int> temp;



  vector<string>::iterator it;
  for( it = query.begin(); it < query.end(); it++){
    // opretator check
    tstring = *it;
    if( tstring.compare( "AND") == 0){
      // and operator
      opVec[0] = -1;
      Q.push_back( opVec);
      level.push_back( lvl);

      continue;
    } else if( tstring.compare( "OR") == 0){
      // or operator
      opVec[0] = -2;
      Q.push_back( opVec);
      level.push_back( lvl);

      continue;
    }



    // parenthesis check
    if( ( index = tstring.find( "(")) != -1){
      // has a ( at the start of the term, remove it and increase the depth
      tstring = tstring.substr( 1); 
      lvl++;
    } else if( (index = tstring.find( ")")) != -1){
      // has a ) at the end of the term, remove it and decrease the depth
      tstring = tstring.substr( 0, index);
      lvl--;
    }

    // get Doc list for the term and add it to Q

    Q.push_back( Ind.getBKeywordDocs( *it));
    level.push_back( lvl);

  }

  // find deepest part of query
  int max = 0;
  for( unsigned int d = 0; d < level.size(); d++){
    if( level[d] > max){
      max = level[d];
    }
  }

  // starting with the deepest terms in the query. evaluate the query
  for( int m = max; m >= 0; m--){

    for(unsigned int i = 0; i < level.size(); i++){
      if( level[i] == m){
        temp = Q[i];


        if( !temp.empty() && temp[0] < 0){

          if( temp[0] == -1){
            // AND
            temp = AND( Q[i-1], Q[i+1]);
            Q[i] = temp;
            level[i]--;

            Q.erase( Q.begin() + i + 1);
            Q.erase( Q.begin() + i - 1);

            level.erase( level.begin() + i + 1);
            level.erase( level.begin() + i - 1);

            i = i - 2;

          } else if( temp[0] == -2){
            // AND
            temp = OR( Q[i-1], Q[i+1]);
            Q[i] = temp;
            level[i]--;

            Q.erase( Q.begin() + i + 1);
            Q.erase( Q.begin() + i - 1);

            level.erase( level.begin() + i + 1);
            level.erase( level.begin() + i - 1);

            i = i - 2;

          }
        }
      }


    }

  
  }
  outpt = Q[0];
  return outpt;

}


// get the union of two vectors
vector<int> AND( vector<int> a, vector<int> b){
  vector<int> outpt;

  if( a.empty() || b.empty()){
    return outpt;
  }

  for( unsigned int i = 0; i < a.size(); i++){

    if( find( b.begin(), b.end(), a[i]) != b.end()){
      outpt.push_back( a[i]);
    }
  }
  return outpt;
}

// get the intersect of two vectors
vector<int> OR( vector<int> a, vector<int> b){
  int len = a.size() + b.size();
  vector<int> outpt(len);
  vector<int>::iterator it;

  it = set_union( a.begin(), a.end(), b.begin(), b.end(), outpt.begin());
  outpt.resize( it - outpt.begin());

  return outpt;

}
