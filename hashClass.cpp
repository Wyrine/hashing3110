#include "hashClass.h"

using namespace std;


bool Variable::insertWord(string str){
  if (word == str){
    frequency++;
    return true;
  }
  else if (frequency == 0){
    word = str;
    frequency++;
    return true;
  }
  return false;
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
    reHash();
    loadFactor = numItemsInTable/tableSize;
  }
}

void HashTable::reHash(){
  int prevSize = tableSize;
  findPrime();
  Variable* newTable = new Variable[tableSize]();
  for(int i = 0; i < prevSize; i++){
    if(frequencyTable[i].frequency != 0){
      
    }
  }
  frequencyTable = NULL;
  delete[] frequencyTable;
  frequencyTable = newTable;
}

int HashTable::lookup(string value){
  int i;
  bool reachedStart = false;
  for(i = 0; i < value.length(); i++)
    value[i] = tolower(value[i]);
  for(i = HASH_MOD; i <= tableSize; i++){
    if(frequencyTable[i].frequency == 0) break;
    else if(frequencyTable[i].word == value) return frequencyTable[i].frequency;
    if(i==tableSize && !reachedStart){
      i = 0;
      reachedStart = true;
    }
  }
  return 0;
}

int HashTable::lookupInsert(string value){
  int loc = HASH_MOD;
  if(frequencyTable[loc].insertWord(value)) return frequencyTable[loc].frequency;
  else{
    int startLoc = loc;
    loc++;
    for(; loc != startLoc; loc++){
      if(loc == tableSize) loc = 0;
      if(frequencyTable[loc].insertWord(value)){
        return frequencyTable[loc].frequency;
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
  for(int i = 0; i < tableSize; i++)
    if(frequencyTable[i].frequency != 0)
      cout << frequencyTable[i].word << " " << frequencyTable[i].frequency << endl;
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
