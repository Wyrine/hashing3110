#include "hashClass.h"

using namespace std;


Variable::Variable(string word){
  for(int i = 0; i < word.size(); i++)
    this->word[i] = tolower(word[i]);
  frequency = 1;
}

HashTable::HashTable(){
  tableSize = DEFAULT_SIZE;
  frequencyTable = new Variable [tableSize];
  loadFactor = 0.0;
  numItemsInTable = 0;
}

HashTable::HashTable(int size){
  tableSize = size;
  frequencyTable = new Variable [tableSize];
  loadFactor = 0.0;
  numItemsInTable = 0;
}

void HashTable::updateLoad(){
  loadFactor = numItemsInTable / tableSize;
  if(loadFactor > 0.5){
    //rehash
    loadFactor = numItemsInTable/tableSize;
  }
}

int HashTable::lookup(string value){
  return frequencyTable[HASH_MOD].frequency;
}

int HashTable::lookupInsert(string value){
  int loc = HASH_MOD;
  if(frequencyTable[loc].word == value) frequencyTable[loc].frequency++;
  else if(frequencyTable[loc].frequency == 0){
    frequencyTable[loc].word = value;
    frequencyTable[loc].frequency++;
  }
  else{
    int startLoc = loc;
    loc++;
    for(; loc != startLoc; loc++){
      if(frequencyTable[loc].frequency == 0){
        frequencyTable[loc].word = value;
        frequencyTable[loc].frequency++;
        break;
      }
      else if(frequencyTable[loc].word == value) {
        frequencyTable[loc].frequency++;
        break;
      }
    }
  }
  numItemsInTable++;
  updateLoad();
  return frequencyTable[loc].frequency;
}

HashTable::~HashTable(){
  frequencyTable = NULL;
  delete[] frequencyTable;
}

unsigned long HashTable::hash(string str){
  unsigned long hash = 5381;
  int c, i = 0;
  while (c = str[i++])
    hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
  return hash;
}
