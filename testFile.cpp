//
//  testFile.cpp
//  PATest3
//
//  Created by Nick Allaire on 5/9/16.
//  Copyright © 2016 Nick Allaire. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include <fstream>
#include "DictionaryHashtable.cpp"
#include "DictionaryBST.cpp"
#include "DictionaryTrie.cpp"
#include "util.cpp"


using namespace std;

int main(int argc, char* argv[]) {
    
  //Check for Arguments
  if(argc != 2){
    cout << "Invalid number of arguments.\n"
    << "Usage: ./main <input filename>.\n";
    return -1;
  }
    
  //Open file
  ifstream in;
  //in.open(argv[1], ios::binary);
  //in.open("../unique_freq_dict.txt");
  in.open("../shuffled_freq_dict.txt");

  //Check if input file was actually opened
  if(!in.is_open()) {
    cout<< "Invalid input file. No file was opened. Please try again.\n";
    return -1;
  }

  //Check for empty file
  in.seekg(0, ios_base::end);
  long long len = in.tellg();
  if(len==0) {
    cout << "The file is empty. \n";
    return -1;
  }

  //Resets the stream to beginning of file
  in.seekg(0, ios_base::beg);

  DictionaryBST* bst = new DictionaryBST();
  DictionaryHashtable* ht = new DictionaryHashtable();
  DictionaryTrie* tst = new DictionaryTrie();

  char answer = 'y';
  string word = " ";
  bool found;
  int choice;
   
  cout << "Enter value for dictionary (0/1/2): ";
  cin >> choice;
  cin.ignore();
   
  if (choice == 0) {
    Utils::load_dict(*bst, in);   
        
    while (answer == 'y') {
      cout << "Enter word to search for(BST): ";
      getline(cin, word);
      found = bst->find(word);
      if (found)
        cout << word << " was found in DictionaryBST." << "\n";
      else
        cout << word << " was NOT found in DictionaryBST." << "\n";
      cout << "Would you like to search again? (y/n): ";
      cin >> answer;
      cin.ignore();
    }    
        
    cout << "\n\n";
        
  }
  else if (choice == 1) {   
    in.seekg(0, ios_base::beg);
    Utils::load_dict(*ht, in);

    answer = 'y';
    found = false;
    word = " ";
    while (answer == 'y') {
      cout << "Enter word to search for(HT): ";
      getline(cin, word);
      found = ht->find(word);
      if (found)
        cout << word << " was found in DictionaryHT." << "\n";
      else 
        cout << word << " was NOT found in DictionaryHT." << "\n";
      cout << "Would you like to search again? (y/n): ";
      cin >> answer;
      cin.ignore();
    }

    cout << "\n\n";
        
  }
  else {
    in.seekg(0, ios_base::beg);
    Utils::load_dict(*tst, in);

    answer = 'y';
    found = false;
    word = " ";
    while (answer == 'y') {
      cout << "Enter word to search for(TST): ";
      getline(cin, word);
      found = tst->find(word);
      if (found)
        cout << word << " was found in DictionaryTST." << "\n";
      else
        cout << word << " was NOT found in DictionaryTST." << "\n";
      cout << "Would you like to search again? (y/n): "; 
      cin >> answer;
      cin.ignore();
    }
        
    cout << "\n\n";
        
    string predictWord;
    int numCompletions;
    answer = 'y';
        
    while (answer == 'y') {
      vector<string> autoCompletions;
      cout << "Enter word to auto-complete: ";
      getline(cin, predictWord);
            
      cout << "Enter number of results you want: ";
      cin >> numCompletions;
      autoCompletions = tst->predictCompletions(predictWord, numCompletions);
            
      cout << "Results: " << "\n";
            
      for (int i = 0; i < autoCompletions.size(); i++)
        cout << autoCompletions[i] << "\n";
            
      cout << "Would you like to search again? (y/n): ";
      cin >> answer;
      cin.ignore();
    }
  }
    
  cout << "Done." << "\n\n";

  delete bst;
  delete ht;
  delete tst;
    
}
