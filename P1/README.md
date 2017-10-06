
# programs

## Create an inverted index 

Given a location of documents, return an inverted index of the corpus.
Inverted index is saved in create_index_out.txt

usage
'''
./create_index [document dir]  
'''




## Print inverted index

Given a location of an inverted index print the index

usage
'''
./print_index [inverted index location]
'''

 


## Boolean Query

Given an inverted index location and a query, return the set of documents that satisfies the query


usage
'''
./boolean_query [inverted index location] ['query']  
'''


example query: "(stemming AND off) AND of"

## Vector space 

Given an inverted index location and a set of terms, return the top k documents that closely fit vector space model of the terms. 

usage 
'''
./vs_query [inverted index location] [k] [scores] [terms]
'''

k is the top number of documents returned
scores can be y/n. If y then the scores of the documenst


## compilation
'''
g++ -o file file.c -std=c++11
'''

