#include "util.hpp"
#include "DictionaryTrie.hpp"
#include <map>
#include <queue>

/* Create a new Dictionary that uses a Trie back end */
DictionaryTrie::DictionaryTrie(){
    root = nullptr;
}

/* Insert a word with its frequency into the dictionary.
 * Return true if the word was inserted, and false if it
 * was not (i.e. it was already in the dictionary or it was
 * invalid (empty string) */
bool DictionaryTrie::insert(std::string word, unsigned int freq) {
  if (word.length() == 0) // not a word
    return false;
    
  TSTNode* tempNode;
  tempNode = root;
    
  for (unsigned int i = 0; i < word.length(); i++) {
    if (root == nullptr) {  // tree is empty
      if (word.length() == 1) {   // root is a word
        TSTNode* tempNode = new TSTNode(true, 0, 0, 0, 0, word[0], freq, word);
        root = tempNode;
        return true;
      } else {    // root is not a word
          TSTNode* insertingNode = new TSTNode(false, 0, 0, 0, 0, word[0], 0, word);
          root = insertingNode;
          tempNode = root;
      }
    } else {
        while (tempNode != nullptr) {
          if (tempNode->text == word[i]) {    // go down middle node
            if (i == word.length() - 1) {  // if on last node of word
              if (tempNode->isWord == true) { // already in tree
                return false;
              }
              else if (tempNode->mid != nullptr) { // word not a leaf
                tempNode->word = word;
                break;
              }
            }
          }
          if (tempNode->mid == nullptr) { // go down middle node and create node if nonexistent
            TSTNode* insertingNode = new TSTNode(false, 0, 0, 0, tempNode, word[i], 0, word);
            tempNode->mid = insertingNode;
            tempNode = tempNode->mid;
            break;
          }
          else if (tempNode->text == word[i]) {
            tempNode = tempNode->mid;
            break;
          }
          else if (word[i] < tempNode->text) { // go down left node
            if (tempNode->left == nullptr) {    // create node if nonexistent
              TSTNode* insertingNode = new TSTNode(false, 0, 0, 0, tempNode, word[i], 0, word);
              tempNode->left = insertingNode;
              tempNode = tempNode->left;
              break;
            }
            else {
              tempNode = tempNode->left;
            }
          }
          else if (word[i] > tempNode->text) {  // go down right node
            if (tempNode->right == nullptr) {   // create node if nonexistent
              TSTNode* insertingNode = new TSTNode(false, 0, 0, 0, tempNode, word[i], 0, word);
              tempNode->right = insertingNode;
              tempNode = tempNode->right;
              break;
            }
            else {
              tempNode = tempNode->right;
            }
          }
        }
      }
    }
    
  if (!tempNode->isWord) {
    tempNode->isWord = true;
    tempNode->freq = freq;
    return true;
  }
  return false;
}

/* Return true if word is in the dictionary, and false otherwise */
bool DictionaryTrie::find(std::string word) const {
  TSTNode* temp;
  temp = root;
  if (temp == nullptr)
    return false;
    
  for (unsigned int i = 0; i < word.length(); i++) {
    while (temp != nullptr) {
      if (word[i] < temp->text)
        temp = temp->left;
      else if (word[i] > temp->text)
        temp = temp->right;
      else if (temp->text == word[i]) {
        if (i == word.length() - 1)
          break;
        else {
          temp = temp->mid;
          break;
        }
      }
      if (temp == nullptr)
        return false;
      }
  }    
   
  if (temp->isWord)
    return true;
  else
    return false;
}

/* Return up to num_completions of the most frequent completions
 * of the prefix, such that the completions are words in the dictionary.
 * These completions should be listed from most frequent to least.
 * If there are fewer than num_completions legal completions, this
 * function returns a vector with as many completions as possible.
 * If no completions exist, then the function returns a vector of size 0.
 * The prefix itself might be included in the returned words if the prefix
 * is a word (and is among the num_completions most frequent completions
 * of the prefix)
 */
std::vector<std::string> DictionaryTrie::predictCompletions(std::string prefix, unsigned int num_completions) {
  std::vector<std::string> words;
  string word;
    
  TSTNode* temp;
  temp = root;
  if (temp == nullptr)
    return words;
    
  for (unsigned int i = 0; i < prefix.length(); i++) { // get to last node of prefix
    while (temp != nullptr) {
      if (prefix[i] < temp->text) {
        temp = temp->left;
      }
      else if (prefix[i] > temp->text) {
        temp = temp->right;
      }
      else if (temp->text == prefix[i]) {
        if (i == prefix.length() - 1) {
          //word += temp->text;
          break;
        }
        else {
          //word += temp->text;
          temp = temp->mid;
          break;
        }
      }
    }
  }
    
  vector<string> completions; // holds auto-completed words
  vector<unsigned int> completionFreqs; // holds frequencies of auto-completed words
  queue<TSTNode* > q;
  q.push(temp->mid);
    
  if (temp->isWord) { // if prefix is a valid word
    completions.push_back(prefix);
    completionFreqs.push_back(temp->freq);
  }
    
  if (temp->mid == nullptr)
    return words;

  while (!q.empty()) { // breadth first search
    temp = q.front();
    q.pop();
    if (temp->isWord) { // found a word
      completions.push_back(temp->word);
      completionFreqs.push_back(temp->freq);
    }
    if (temp->mid != nullptr)
      q.push(temp->mid);
    if (temp->left != nullptr)
      q.push(temp->left);
    if (temp->right != nullptr)
      q.push(temp->right);
  }
    
  for (unsigned int i = 0; i < completionFreqs.size() - 1; i++) { // sort found words by frequency
    for (unsigned int j = i + 1; j < completionFreqs.size(); j++) {
      if (completionFreqs[i] < completionFreqs[j]) {
        int tempFreq;
        string tempWord;
        tempFreq = completionFreqs[j];
        completionFreqs[j] = completionFreqs[i];
        completionFreqs[i] = tempFreq;
        tempWord = completions[j];
        completions[j] = completions[i];
        completions[i] = tempWord;
        }
    }
  }
  if (num_completions > completionFreqs.size())
    num_completions = completionFreqs.size();
    
  for (unsigned int i = 0; i < num_completions; i++)
    words.push_back(completions[i]);
    
  return words;
}

/* Destructor */
DictionaryTrie::~DictionaryTrie(){
  deleteAll(root);
}

void DictionaryTrie::deleteAll(TSTNode* n) {
  if (n == nullptr)
    return;
  deleteAll(n->left);
  deleteAll(n->mid);
  deleteAll(n->right);
  delete n;
}
