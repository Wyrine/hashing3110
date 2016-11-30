#include "hashClass.h"

using namespace std;


/* PUBLIC MEMBER FUNCTIONS */

//intializer of the class with 0 parameters
HashTable::HashTable(){
  //setting the table size to the default size
  tableSize = DEFAULT_SIZE;
  //allocating a table of size tableSize
  frequencyTable = new Variable [tableSize];
  //setting the load factor and number of items in the table to 0
  loadFactor = 0.0;
  numItemsInTable = 0;
}

//intializer of the class with 1 parameter being the initial table size
HashTable::HashTable(int size){
  //setting the tableSize to be the given size
  tableSize = size;
  //allocating a new table with the size being the given size
  frequencyTable = new Variable [tableSize];
  //setting the load factor and number of items in the table to 0
  loadFactor = 0.0;
  numItemsInTable = 0;
}


//lookup returns the frequency(count of the word in the table) from the table by
//hashing the bucket and looping until you find the word or a 0 meaning the word is
//not in the list
int HashTable::lookup(string bucket){
  unsigned int i;
  //reached start is a boolean that ensures the loop does not loop infinitely
  //and it breaks as soon as the index is the start position again
  bool reachedStart = false;
  //loops for the bucket size and lowercases the word for safe comparisons
  for(i = 0; i < bucket.length(); i++)
    bucket[i] = tolower(bucket[i]);
  //starts at the location of HASH_MOD until the size is greater than the tableSize
  for(i = HASH_MOD; i <= tableSize; i++){
    //if the frequency is 0, the bucket is not in the list; break
    if(frequencyTable[i].frequency == 0) break;
    //if the bucket is equal to the word in the current location of the table the it has been found
    //return the current frequency of the table
    else if(frequencyTable[i].word == bucket) return frequencyTable[i].frequency;
    //if i is the same as the tableSzie and reachedStart is false
    if(i==tableSize && !reachedStart){
      //start at the beginning of the table and set reachedStart to true
      i = 0;
      reachedStart = true;
    }
  }
  //return 0 as the frequency because the word has not been found
  return 0;
}

//lookupInsert returns the frequency(count of the word in the table) from the table
//along with inserting the word if it's not in the table already along with incrementing the
//frequency of the words location
int HashTable::lookupInsert(string bucket){
  //defining some variables and setting loc to be the HASH_MOD
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
