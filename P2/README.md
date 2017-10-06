
# programs

## zone scoring

Returns the top k scores of documents based on their similarity to an inputed document

usage
'''
./create_zone_index [document dir] [index dir]  
./zone_scorer [index dir] [k] [g] [q]  
'''

k is the number of documents to be returned  
g is the weight of the scoreing [0,1]  
q is the location of the document to be scored  


## document classification

Given a set of already classified documents, classify a input document into one of the classes.

usage
'''
./create_labeled_index [document dir] [index dir]  
./knn_classifier [index dir] [k] [q]  
'''

k is the number of documents to be returned  
q is the query that will be scored. Query needs to be within single quotes (' ')  


## document clustering

clusters documents based on their similarities to each other.


usage
'''
./create_index [document dir] [index dir]  
./k_means_clusterer [index dir] [k] [optional id_1 id_2 ... id_k]  
'''

k is the number of documents to be returned  
optional ids: can include ids of the specific documents in the index to cluster  
    if no ids are specified then all the documents in the index are clustered  


## compilation
'''
g++ -o file file.c -std=c++11
'''

