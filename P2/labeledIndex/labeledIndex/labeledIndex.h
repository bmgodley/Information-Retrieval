#ifndef LABELEDINDEX_H
#define LABELEDINDEX_H

#include "../term/term.h"



int getId( std::string filename);
std::string tokenize( std::string word);
bool charCheck( char c);


class labeledIndex {
// class to handle the labeled index
  private:
    std::vector<term> v;      // vector of terms 
    std::vector<int> docList; // vector to keep track of the documents encountered 
    int invSearch( std::string term);
    std::map< int, std::string> cls; // map of the classes and their ids
    std::map< int, int> docClasses; // map of the documents and their class ids

  public:
    void occurance( std::string term, int doc, int pos);
    int output ( std::string filename);
    int input( std::string filename);
    void printInv();
    void calc();
    int readDir( std::string dirname);
    int readFile( std::string filename);
    int readQFile( std::string filename);
    std::vector<int> getDocs(); // vector to keep track of the documents encountered 
    std::vector<int> getKeywordDocs( std::string keyword);
    std::vector<int> getPhraseDocs( std::string keyword);
    std::vector<int> getIndexes( int docId, std::string keyword);
    std::vector<int> compareIndexes( std::vector<int> a, std::vector<int> b, int offset);
    int getClassId( std::string name);
    std::string getClassName( int id);
    std::vector<double> getVector( int docId);
    std::vector<std::tuple<int,std::vector<double>>> getVectors();
    std::vector<std::tuple<int,std::vector<double>>> getVectors( std::vector<int> v);

};

#endif 