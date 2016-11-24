#include "hashClass.h"

using namespace std;

Variable::Variable(string word){
  for(int i = 0; i < word.size(); i++)
    this->word[i] = tolower(word[i]);
  numberOfOccurences = 0;
}

HashTable::HashTable(){
  tableSize = DEFAULT_SIZE;
  frequencyTable = new Variable [tableSize];
  loadFactor = 0.0;
}

HashTable::HashTable(int size){
  tableSize = size;
  frequencyTable = new Variable [tableSize];
  loadFactor = 0.0;
}

HashTable::~HashTable(){
  frequencyTable = NULL;
  delete[] frequencyTable;
}

unsigned long HashTable::hash(unsigned char *str){
  unsigned long hash = 5381;
  int c;
  while (c = *str++)
    hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
  return hash;
}
