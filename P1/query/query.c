
#include <string>
#include <stack>
#include <queue>
#include <iostream>
#include <tuple>
#include <algorithm>

#include "query.h"
#include "../dataStructures/invertedIndex/invertedIndex.h"



using namespace std;





/*

  boolean query( )
  


*/

void printVec( vector<auto> a){
  for( unsigned int i = 0; i < a.size(); i++){
    cout << a[i] << " ";
  }
  cout << endl;
}








// void Query:: eval( string query){

//   string term;
//   int index;
//   bool loop = true;
//   int lvl = 0;


//   while( loop){
//     // get the next term in the query
//     index = query.find(" "); 

//     if (index == -1){
//     // last term in the query
//       loop = false;
//       term = query;

//     } else {
//       term = query.substr(0, index);
//       query = query.substr( index + 1); // remove term from query

//     }

   
//     if( ( index = term.find("(")) != -1){
//       // term has a ( in it. Add "(" and the term to the queue
//       lvl++;
//       term = term.substr(1);

//     } else if( ( index = term.find( ")")) != -1){
//       // term has a ) in it. Add the term and ")" to the queue
//       Que.push( term.substr( 0, index));
//       Que.push( ")");

//     } else {
//       // only contains a term
//       Que.push( term);

//     }


//   }
// }






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






vector<int> eval( invertedIndex Inv, vector<string> query){
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

    Q.push_back( Inv.getKeywordDocs( *it));
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

/*





  std::vector<int> level;
  std::vector<int> temp;
  temp.push_back( 0);

  int lvl = 0;

  string term;
  string phrase;
  int index;
  queue<string> Que;
  bool loop = true;



  // check query


  int max = 0;
  for( unsigned int d = 0; d < level.size(); d++){
    if( level[d] > max){
      max = level[d];
    }
  }

  // << max << endl;

  for( int m = max; m >= 0; m--){

    for(unsigned int i = 0; i < level.size(); i++){
      if( level[i] == m){
        temp = Q[i];


        if( !temp.empty() && temp[0] < 0){

          if( temp[0] == -1){
            // AND
            temp = this->AND( Q[i-1], Q[i+1]);
            Q[i] = temp;
            level[i]--;

            Q.erase( Q.begin() + i + 1);
            Q.erase( Q.begin() + i - 1);

            level.erase( level.begin() + i + 1);
            level.erase( level.begin() + i - 1);

            i = i - 2;

          } else if( temp[0] == -2){
            // AND
            temp = this->OR( Q[i-1], Q[i+1]);
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


  

  
  cout <<"output" << endl;
  printVec( Q[0]);
  cout << endl;
  return 0;
}

*/

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

vector<int> OR( vector<int> a, vector<int> b){
  int len = a.size() + b.size();
  vector<int> outpt(len);
  vector<int>::iterator it;

  it = set_union( a.begin(), a.end(), b.begin(), b.end(), outpt.begin());
  outpt.resize( it - outpt.begin());

  return outpt;

}
