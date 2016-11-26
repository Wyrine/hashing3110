#include "hashClass.h"

using namespace std;


/* PUBLIC MEMBER FUNCTIONS */


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


int HashTable::lookup(string bucket){
  unsigned int i;
  bool reachedStart = false;
  for(i = 0; i < bucket.length(); i++)
    bucket[i] = tolower(bucket[i]);
  for(i = HASH_MOD; i <= tableSize; i++){
    if(frequencyTable[i].frequency == 0) break;
    else if(frequencyTable[i].word == bucket) return frequencyTable[i].frequency;
    if(i==tableSize && !reachedStart){
      i = 0;
      reachedStart = true;
    }
  }
  return 0;
}

int HashTable::lookupInsert(string bucket){
  int loc = HASH_MOD, startLoc, returnVar;
  if(!insert(bucket, frequencyTable, loc, true)){
    startLoc = loc;
    for(loc++; loc != startLoc; loc++){
      if(loc == tableSize) loc = 0;
      if(insert(bucket, frequencyTable, loc, true)) break;
    }
  }
  returnVar = frequencyTable[loc].frequency;
  updateLoad();
  return returnVar;
}

void HashTable::printTable() {
	for (unsigned int i = 0; i < tableSize; i++)
		if (frequencyTable[i].frequency != 0)
			cout << frequencyTable[i].word << " " << frequencyTable[i].frequency << endl;
}


HashTable::~HashTable() {
	frequencyTable = NULL;
	delete[] frequencyTable;
}


/* PRIVATE MEMBER FUNCTIONS */


bool HashTable::insert(string bucket, Variable* frequencyTable, unsigned int loc, bool upNum, unsigned int prevFreq) {
	if (frequencyTable[loc].canInsert(bucket)) {
		if (upNum) frequencyTable[loc].frequency++;
		else frequencyTable[loc].frequency = prevFreq;
		if (frequencyTable[loc].frequency == 1) {
			if (upNum) numItemsInTable++;
			frequencyTable[loc].word = bucket;
		}
		return true;
	}
	return false;
}

unsigned long HashTable::hash(string str) {
	unsigned long hash = 5381;
	for (unsigned int i = 0; i < str.length(); i++) {
		hash = ((hash << 5) + hash) + str[i]; /* hash * 33 + currentStringValue */
	}
	return hash;
}

void HashTable::updateLoad() {
	loadFactor = (double)numItemsInTable / (double)tableSize;
	if (loadFactor >= MAX_LOAD_FACTOR) {
		reHash();
		loadFactor = numItemsInTable / tableSize;
	}
}

void HashTable::updateTableSize(){
  tableSize *= 2;
  bool isPrime = false;
  while(!isPrime){
    isPrime = true;
    for(unsigned int i = 2; i <= tableSize/2; i++){
      if(tableSize % i == 0) isPrime = false;
    }
    if(!isPrime) tableSize++;
  }
}

void HashTable::reHash() {
	unsigned int prevSize = tableSize, loc, prevFreq;
	string bucket;
	updateTableSize();
	Variable* newTable = new Variable[tableSize]();
	for (unsigned int i = 0; i < prevSize; i++) {
		if (frequencyTable[i].frequency != 0) {
			bucket = frequencyTable[i].word;
			prevFreq = frequencyTable[i].frequency;
			loc = HASH_MOD;
			if (!insert(bucket, newTable, loc, false, prevFreq)) {
				for (unsigned int j = i + 1; j != i; j++) {
					if (j == tableSize) j = 0;
					if (insert(bucket, newTable, j, false, prevFreq)) break;
				}
			}
		}
	}
	loadFactor = numItemsInTable / tableSize;
	frequencyTable = NULL;
	delete[] frequencyTable;
	frequencyTable = newTable;
}