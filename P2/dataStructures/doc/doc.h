#ifndef DOC_H
#define DOC_H


class doc {
  private:
    int docID;
    int tf;
    double tf_idf;
    std::vector<int> bIndex;
    std::vector<int> tIndex;

  public: 
    doc( int id);
    void addBIndex( int index);
    void addTIndex( int index);
    int getID();
    void printPostings(); 
    int getTf();
    void setTfIdf( int ndoc, int df);
    std::string output();
    std::vector<int> getBIndexes();
    std::vector<int> getTIndexes();

    int hasTitle();
    int hasBody();



};

#endif