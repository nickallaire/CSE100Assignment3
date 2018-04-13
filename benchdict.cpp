//
//  benchdict.cpp
//  PATest3
//
//  Created by Nick Allaire on 5/10/16.
//  Copyright © 2016 Nick Allaire. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include <fstream>
#include "DictionaryHashtable.hpp"
#include "DictionaryBST.hpp"
#include "DictionaryTrie.hpp"
#include "util.hpp"


using namespace std;

int main(int argc, char* argv[]) {
  //Check for Arguments
  if(argc != 5){
    cout << "Invalid number of arguments.\n"
    << "Usage: ./main <input filename>.\n";
    return -1;
  }
    
  //Open file
  ifstream in;
  in.open(argv[4], ios::binary);
  //in.open("../unique_freq_dict.txt");
  //in.open("../shuffled_freq_dict.txt");
    
  //Check if input file was actually opened
  if(!in.is_open()) {
    std::cout<< "Invalid input file. No file was opened. Please try again.\n";
    return -1;
  }
    
  //Check for empty file
  in.seekg(0, ios_base::end);
  long long len = in.tellg();
  if(len==0) {
    std::cout << "The file is empty. \n";
    return -1;
  }
    
  //Resets the stream to beginning of file
  in.seekg(0, ios_base::beg);
    
  unsigned int min_size = atoi(argv[1]);
  unsigned int step_size = atoi(argv[2]);
  unsigned int num_iterations = atoi(argv[3]);
  //int min_size = 50000;
  //int step_size = 50000;
  //int num_iterations = 5;
 
  //DictionaryHashtable* ht = new DictionaryHashtable();
  //Utils::load_dict(*ht, in);
  //int dictSize = ht->getSize();
  //cout << dictSize << "\n";
  //in.seekg(0, ios_base::beg);
  //delete ht;
  Timer T;
  long long time_duration;
    
  cout << "Benchmarking BST Dictionary: " << "\n";
  for (unsigned int i = 0; i < num_iterations; i++) {
    DictionaryBST* bst = new DictionaryBST();
    in.seekg(0, ios_base::beg);
    Utils::load_dict(*bst, in, (min_size + (i * step_size)));
    T.begin_timer();
    bst->find("invertedd");
    bst->find("adiaabatic");
    bst->find("nnumbskul");
    bst->find("dipphosgenne");
    bst->find("prohbtion");
    bst->find("groqmer");
    bst->find("rguling");
    bst->find("motez");
    bst->find("isolhated");
    bst->find("preralote");
    time_duration = T.end_timer();   
    cout << (min_size + (i * step_size)) << "\t" << time_duration << "\n";
    delete bst;
  }
    
  in.seekg(0, ios_base::beg);
    
  cout << "\nBenchmarking Hashtable Dictionary: " << "\n";
  for (unsigned int i = 0; i < num_iterations; i++) {
    DictionaryBST* ht = new DictionaryBST();
    in.seekg(0, ios_base::beg);
    Utils::load_dict(*ht, in, (min_size + (i * step_size)));
    T.begin_timer();
    ht->find("invertedd");
    ht->find("adiaabatic");
    ht->find("nnumbskul");
    ht->find("dipphosgenne");
    ht->find("prohbtion");
    ht->find("groqmer");
    ht->find("rguling");
    ht->find("motez");
    ht->find("isolhated");
    ht->find("preralote");
    time_duration = T.end_timer();
    cout << (min_size + (i * step_size)) << "\t" << time_duration << "\n";
    delete ht;
  }
    
  in.seekg(0, ios_base::beg);
    
  cout << "\nBenchmarking Trie Dictionary: " << "\n";
  for (unsigned int i = 0; i < num_iterations; i++) {
    DictionaryBST* tst = new DictionaryBST();
    in.seekg(0, ios_base::beg);
    Utils::load_dict(*tst, in, (min_size + (i * step_size)));
    T.begin_timer();
    tst->find("invertedd");
    tst->find("adiaabatic");
    tst->find("nnumbskul");
    tst->find("dipphosgenne");
    tst->find("prohbtion");
    tst->find("groqmer");
    tst->find("rguling");
    tst->find("motez");
    tst->find("isolhated");
    tst->find("preralote");
    time_duration = T.end_timer();
    cout << (min_size + (i * step_size)) << "\t" << time_duration << "\n";
    delete tst;
  }
    
  cout << "\n\nDone\n";
    
}
