#include <string>
#include <string.h>
#include <iostream>
#include <vector>


using namespace std;




int testParseQuery(){
  int pass = 0;
  int testNum = 1;

  // test 1
  string testS = "stemming AND of";
  vector<string> test = parseQuery( testS);
  vector<string> control = { "stemming", "AND", "of"};

  if( test != control){
    cout << "> parseQuery test: " << testNum << " failed" << endl;
    pass = 1; // fail
  }

  // test 2
  testNum++;
  testS = "stemming AND of";
  test = parseQuery( testS);
  control = { "stemming", "ANDa", "of"};

  if( test == control){ // fail
    cout << "> parseQuery test: " << testNum << " failed" << endl;
    pass = 1; // fail
  }

  // test 3
  testNum++;
  testS = "(stemming AND of)";
  test = parseQuery( testS);
  control = { "(stemming", "AND", "of)"};

  if( test != control){
    cout << "> parseQuery test: " << testNum << " failed" << endl;
    pass = 1; // fail
  }

  // test 4
  testNum++;
  testS = "(stemming AND of) AND the";
  test = parseQuery( testS);
  control = { "(stemming", "AND", "of)", "AND", "the"};

  if( test != control){
    cout << "> parseQuery test: " << testNum << " failed" << endl;
    pass = 1; // fail
  }

  // test 5
  testNum++;
  testS = "(stemming AND \"a phrase\")";
  test = parseQuery( testS);
  control = { "(stemming", "AND", "a",  "phrase)"};

  if( test == control){ // fail
    cout << "> parseQuery test: " << testNum << " failed" << endl;
    pass = 1; // fail
  }

  // test 6
  testNum++;
  testS = "(stemming AND \"a phrase\")";
  test = parseQuery( testS);
  control = { "(stemming", "AND", "a phrase)"};

  if( test != control){
    cout << "> parseQuery test: " << testNum << " failed" << endl;
    pass = 1; // fail
  }

  // test 7
  testNum++;
  testS = "(stemming AND \"a phrase\")";
  test = parseQuery( testS);
  control = { "(stemming", "AND", "a phrase )"};

  if( test == control){ // fail
    cout << "> parseQuery test: " << testNum << " failed" << endl;
    pass = 1; // fail
  }

  return pass;

}


int testGetDocs(){
  int pass = 0;
  int testNum = 0;

  string testS;
  vector<int> test;
  vector<int> control;

  invertedIndex Inv;
  Inv.input( "create_index_test.txt");

  // test 1
  testNum++;
  testS = "stemming";
  test = Inv.getKeywordDocs( testS);
  control = { 1, 2, 3, 4};

  if( test != control){ 
    cout << "> getDocs test: " << testNum << " failed" << endl;
    pass = 1; // fail
  }

  // test 2
  testNum++;
  testS = "stemming";
  test = Inv.getKeywordDocs( testS);
  control = { 1, 2, 3};

  if( test == control){ // fail
    cout << "> getDocs test: " << testNum << " failed" << endl;
    pass = 1; // fail
  }

  // test 3
  testNum++;
  testS = "stemming increase";
  test = Inv.getKeywordDocs( testS);
  control = {};

  if( test != control){ 
    cout << "> getDocs test: " << testNum << " failed" << endl;
    pass = 1; // fail
  }

  // test 4
  testNum++;
  testS = "stemming never";
  test = Inv.getKeywordDocs( testS);
  control = { 1, 2};

  if( test != control){ 
    cout << "> getDocs test: " << testNum << " failed" << endl;
    pass = 1; // fail
  }

  // test 5
  testNum++;
  testS = "never stemming";
  test = Inv.getKeywordDocs( testS);
  control = {};

  if( test != control){ 
    cout << "> getDocs test: " << testNum << " failed" << endl;
    pass = 1; // fail
  }

  // test 7
  testNum++;
  testS = "in a Boolean retrieval system stemming never lowers precision";
  test = Inv.getKeywordDocs( testS);
  control = { 1};

  if( test != control){ 
    cout << "> getDocs test: " << testNum << " failed" << endl;
    pass = 1; // fail
  }



  return pass;

}



int testEval(){
  int pass = 0;
  int testNum = 0;

  vector<string> query;
  vector<int> test;
  vector<int> control;

  invertedIndex Inv;
  Inv.input( "create_index_test.txt");

  // test 1
  testNum++;
  query = { "stemming"};
  test = eval( Inv, query);
  control = { 1, 2, 3, 4};

  if( test != control){ 
    cout << "> eval test: " << testNum << " failed" << endl;
    pass = 1; // fail
  }

  // test 2
  testNum++;
  query = { "StEmming"};
  test = eval( Inv, query);
  control = { 1, 2, 3, 4};

  if( test != control){ 
    cout << "> eval test: " << testNum << " failed" << endl;
    pass = 1; // fail
  }

  // test 3
  testNum++;
  query = { "stemming", "AND", "recall"};
  test = eval( Inv, query);
  control = { 2};

  if( test != control){ 
    cout << "> eval test: " << testNum << " failed" << endl;
    pass = 1; // fail
  }

  // test 4
  testNum++;
  query = { "(recall", "OR", "precision)", "AND", "system"};
  test = eval( Inv, query);
  control = { 1, 2};

  if( test != control){ 
    cout << "> eval test: " << testNum << " failed" << endl;
    pass = 1; // fail
  }

  // test 5
  testNum++;
  query = { "system",  "OR", "vocabulary", "OR", "while", "AND", "at", "OR", "should"};
  test = eval( Inv, query);
  control = { 4};

  if( test != control){ 
    cout << "> eval test: " << testNum << " failed" << endl;
    pass = 1; // fail
  }

  // test 6
  testNum++;
  query = { "stemming should", "OR", "stemming increases"};
  test = eval( Inv, query);
  control = { 3, 4};

  if( test != control){ 
    cout << "> eval test: " << testNum << " failed" << endl;
    pass = 1; // fail
  }


  return pass;
}