#include <string>
#include <string.h>
#include <iostream>
#include <vector>



using namespace std;







int main( int argc, char* argv[]){
// get inverted index

  if( argc < 5){
    cout << "\nIncorrect number of arguments \nCorrect usage: './vs_query <inverted index location> <k> <scores (y/n)> <term 1> <term 2> ...'\n";
    

    return 1;
  } 
  // extract index location and query from inputs

  string indexLoc;
  indexLoc.append( argv[1]);

  int k = atoi( argv[2]);

  string scores;
  scores.append( argv[3]);
  int s; 
  if( scores.compare("y") == 1 || scores.compare("Y") == 1){
    s = 0;
  } else if( scores.compare("n") == 1 || scores.compare("N") == 1){
    s = 1;
  } else {
    cout << "invalid score value (y/n)" << endl;
    return 1;
  }

  vector<string> terms;
  for( int i = 4; i < argc; i++){
    string term;
    term.append( argv[i]);
    terms.push_back( term);
  }






  return 0;

}