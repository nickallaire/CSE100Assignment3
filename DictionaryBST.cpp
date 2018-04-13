#include "util.hpp"
#include "DictionaryBST.hpp"

/* Create a new Dictionary that uses a BST back end */
DictionaryBST::DictionaryBST() {
    
}

/* Insert a word into the dictionary. */
bool DictionaryBST::insert(std::string word) {
  bool checkWord = find(word);
  if (checkWord)
    return false;
  else {
    BST.insert(word);
    sizeOfDictionary++;
  }
  return true;
}

/* Return true if word is in the dictionary, and false otherwise */
bool DictionaryBST::find(std::string word) const {
  auto wordFound = BST.find(word);
  if (wordFound == BST.end())
    return false;
  return true;
}

int DictionaryBST::getSize() {
  return sizeOfDictionary;
}

/* Destructor */
DictionaryBST::~DictionaryBST(){
    
}
