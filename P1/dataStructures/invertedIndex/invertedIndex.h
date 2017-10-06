#ifndef INVERTEDINDEX_H
#define INVERTEDINDEX_H

#include "../term/term.h"



int getId( std::string filename);
std::string tokenize( std::string word);
bool charCheck( char c);


class invertedIndex {
// class to handle the inverted index
  private:
    std::vector<term> v;      // vector of terms 
    std::vector<int> docList; // vector to keep track of the documents encountered 
    int invSearch( std::string term);

  public:
    void occurance( std::string term, int doc, int pos);
    int output ( std::string filename);
    int input( std::string filename);
    void printInv();
    void calc();
    int readDir( std::string dirname);
    int readFile( std::string filename);
    std::vector<int> getDocs(); // vector to keep track of the documents encountered 
    std::vector<int> getKeywordDocs( std::string keyword);
    std::vector<int> getPhraseDocs( std::string keyword);
    std::vector<int> getIndexes( int docId, std::string keyword);
    std::vector<int> compareIndexes( std::vector<int> a, std::vector<int> b, int offset);


};

#endif 