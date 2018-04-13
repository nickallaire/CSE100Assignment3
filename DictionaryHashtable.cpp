#include "util.hpp"
#include "DictionaryHashtable.hpp"
#include <unordered_set>

using namespace std;

/* Create a new Dictionary that uses a Hashset back end */
DictionaryHashtable::DictionaryHashtable(){
    
}

/* Insert a word into the dictionary. */
bool DictionaryHashtable::insert(std::string word) {
  bool checkWord = find(word);
  if (checkWord)
    return false;
  else {
    size++;
    HashTable.insert(word);
  }
  return true;
}

/* Return true if word is in the dictionary, and false otherwise */
bool DictionaryHashtable::find(std::string word) const {
  auto wordToFind = HashTable.find(word);
  if (wordToFind == HashTable.end())
    return false;
  return true;
}

int DictionaryHashtable::getSize() {
  return size;
}

/* Destructor */
DictionaryHashtable::~DictionaryHashtable(){
}
