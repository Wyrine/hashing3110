#include "hashClass.h"

using namespace std;


void Variable::lowerWord(string word){
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
  if(loadFactor > MAX_LOAD_FACTOR){
    rehash();
    loadFactor = numItemsInTable/tableSize;
  }
}

void HashTable::rehash(){
  int prevSize = tableSize;
  findPrime();
  Variable* newTable = new Variable[tableSize]();
  for(int i = 0; i < prevSize; i++){
    if(frequencyTable[i].frequency != 0) return;
  }
}

int HashTable::lookup(string value){
  return frequencyTable[HASH_MOD].frequency;
}

int HashTable::lookupInsert(string value){
  int loc = HASH_MOD;
  if(frequencyTable[loc].word == value) frequencyTable[loc].frequency++;
  else if(frequencyTable[loc].frequency == 0){
    frequencyTable[loc].lowerWord(value);
  }
  else{
    int startLoc = loc;
    loc++;
    for(; loc != startLoc; loc++){
      if(frequencyTable[loc].frequency == 0){
        frequencyTable[loc].lowerWord(value);
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

void HashTable::findPrime(){
  tableSize *= 2;
  bool isPrime = false;
  while(!isPrime){
    isPrime = true;
    for(int i = 2; i <= tableSize/2; i++){
      if(tableSize % i == 0) isPrime = false;
    }
    if(!isPrime) tableSize++;
  }
}

void HashTable::printTable(){
  for(int i = 0; i < tableSize; i++){
    if(frequencyTable[i].frequency != 0) cout << frequencyTable[i].word << endl;
  }
}

HashTable::~HashTable(){
  frequencyTable = NULL;
  delete[] frequencyTable;
}

unsigned long HashTable::hash(string str){
  unsigned long hash = 5381;
  for(int i = 0; i < str.length(); i++){
    hash = ((hash << 5) + hash) + str[i]; /* hash * 33 + currentStringValue */
  }
  return hash;
}
