#ifndef ZONEINDEX_H
#define ZONEINDEX_H

#include "../term/term.h"



int getId( std::string filename);
std::string tokenize( std::string word);
bool charCheck( char c);


class zoneIndex {
// class to handle the zone index
  private:
    std::vector<term> v;      // vector of terms 
    std::vector<int> docList; // vector to keep track of the documents encountered 
    int invSearch( std::string term);

  public:
    void bOccurance( std::string term, int doc, int pos);
    void tOccurance( std::string term, int doc, int pos);
    int output ( std::string filename);
    int input( std::string filename);
    void printInv();
    int readDir( std::string dirname);
    int readFile( std::string filename);

    std::vector<int> getDocs(); // vector to keep track of the documents encountered 
    std::vector<int> getTKeywordDocs( std::string keyword);
    std::vector<int> getTPhraseDocs( std::string keyword);
    std::vector<int> getBKeywordDocs( std::string keyword);
    std::vector<int> getBPhraseDocs( std::string keyword);
    std::vector<int> getTIndexes( int docId, std::string keyword);
    std::vector<int> getBIndexes( int docId, std::string keyword);
    std::vector<int> compareIndexes( std::vector<int> a, std::vector<int> b, int offset);


};

#endif 