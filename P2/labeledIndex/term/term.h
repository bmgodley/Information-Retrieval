#ifndef TERM_H
#define TERM_H

#include "../doc/doc.h"

class term {
// class to store the documentID/ position in the document for a given term
  private: 
    std::string token;
    std::vector<doc> postings;
    int df;

  public:
    term( std::string _token);
    void addOccurance( int doc, int pos);
    void printOccurance();
    std::string getToken();
    int getDf();
    std::vector<doc> getPostings();
    std::string output ();
    std::vector<int> getDocs(); 
    std::vector<int> getDocIndexes( int docId);
    double getLTF( int docId);
};

#endif