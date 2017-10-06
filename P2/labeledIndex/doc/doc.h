#ifndef DOC_H
#define DOC_H


class doc {
  private:
    int docID;
    int tf;
    double tf_idf;
    std::vector<int> index;

  public: 
    doc( int id);
    void addIndex( int index);
    int getID();
    void printPostings(); 
    int getTf();
    void setTfIdf( int ndoc, int df);
    std::string output();
    std::vector<int> getIndexes();



};

#endif