

int getId( string filename){
// extract the id of the doc
// doc_1000_aoeu -> 1000
  int t;

  try {
    string sub = word.substr(4);
    t = sub.find("_");
    sub = sub.substr( 0, t);
    return atoi(sub.c_str());

  } catch (... ) {
  // fails with directory "." 
    return -1; //will be skipped over
  }

}

string tokenize( string word){
  string newWord = word; 
// remove punctuation
  int pos = 0;
  for( string::iterator i = word.begin(); i != word.end(); i++){ 
    if( charCheck(*i) == 0){
    //delete invalid character
      newWord.erase(newWord.begin() + pos);
    } else {
    // else increment position
      pos++;
    }
  }
// to lower case
  transform( newWord.begin(), newWord.end(), newWord.begin(), (int (*)(int)) tolower );

  return newWord;

}

bool charCheck( char c){
// return false if the character should be removed from the string
  // doesn't account for the curled "" marks or ... 
  string invalid = "-_=+,.!?  @#$ ;:[](){''}| ]^&/\"\'";
  size_t pos;

  if( (pos = invalid.find( c)) != string::npos ) {
    return 0;
  }
  return 1;

}