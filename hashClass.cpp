//Kirolos Shahat
//HashTable member function definitions
//hashClass.cpp

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
  //if the value can not be inserted in this location
  if(!insert(bucket, frequencyTable, loc, true)){
    //then we must loop, we set the startLoc to be the location where we just tried
    //to insert
    startLoc = loc;
    //increment loc by one to start at the next index of the array
    //because collisions are being handled by linear probing
    for(loc++; loc != startLoc; loc++){
      //if loc has reached the tableSize then set it to 0 to start at the beginning
      if(loc == tableSize) loc = 0;
      //if the insertion can be done here then do so and break
      if(insert(bucket, frequencyTable, loc, true)) break;
    }
  }
  //set the return variable to be the current index of loc's frequency
  returnVar = frequencyTable[loc].frequency;
  //update the load and potentially rehash if there are too many elements in the table
  updateLoad();
  //return the frequency
  return returnVar;
}

//print table loops and prints the word and frequency of all of the words in the table
//it only prints if the frequency is greater than 0. This was purely used for debugging
void HashTable::printTable() {
  //looping throughout the size of the table
	for (unsigned int i = 0; i < tableSize; i++)
    //if the frequency of the current element is greater than 0 then print
		if (frequencyTable[i].frequency > 0)
			cout << frequencyTable[i].word << " " << frequencyTable[i].frequency << endl;
}

//the destructor deallocates the frequency Table
//and sets the loadFactor, numItemsInTable, and tableSize to 0
HashTable::~HashTable() {
	frequencyTable = NULL;
	delete[] frequencyTable;
  loadFactor = 0.0;
  numItemsInTable = 0;
  tableSize = 0;
}


/* PRIVATE MEMBER FUNCTIONS */

//insert is at the heart of this program. It is a function that returns a boolean, true being the item has been inserted
//and false being the item cannot be inserted here. It is used for both rehashing and insertion. The way it differentiates
//the two is through the parameter upNum. If upNum is true then it knows that it is inserting into a new table
//and if upNum is false then it is reHashing. The only real difference between the two is either incrementing
//frequency and numItemsInTable (original insertion) or just copying over the frequency into the new table (rehashing)
//if upNum is false then prevFreq is going to be the frequency associated with the word in the previous table
bool HashTable::insert(string bucket, Variable* frequencyTable, unsigned int loc, bool upNum, unsigned int prevFreq){
  //calling the canInsert method of the variable class to see
  //if the bucket can be inserted in this location or not if so
  // then insert otherwise return false
	if (frequencyTable[loc].canInsert(bucket)){
    //if upNum is true then we are not rehashing
		if (upNum){
      frequencyTable[loc].frequency++;
      if(frequencyTable[loc].frequency == 1){
        frequencyTable[loc].word = bucket;
        numItemsInTable++;
      }
    }	else { //otherwise we are rehashing
      //copy over frequency and the bucket into the frequencyTable
      frequencyTable[loc].frequency = prevFreq;
      frequencyTable[loc].word = bucket;
    }
    //return true when the item actually has been inserted
		return true;
	}
  //return false when canInsert returns false
	return false;
}

//the provided hashing function
unsigned long HashTable::hash(string str) {
	unsigned long hash = 5381;
  //loops for the length of the string
	for (unsigned int i = 0; i < str.length(); i++) {
    // hash * 33 + currentStringValue
		hash = ((hash << 5) + hash) + str[i];
	}
	return hash;
}

//updateLoad updates the loadFactor and calls reHash if the loadFactor is too high
void HashTable::updateLoad() {
  //items currently in the table / the current tableSize becomes the loadFactor
	loadFactor = (double)numItemsInTable / (double)tableSize;
  //if the loadFactor is > = the MAX_LOAD_FACTOR
	if (loadFactor >= MAX_LOAD_FACTOR) {
    //reHash
		reHash();
    //get the new loadFactor after reHash
		loadFactor = numItemsInTable / tableSize;
	}
}

//update table size doubles current table size and increments by 1 until it finds a tableSize
//that is prime and sets that as the new tableSize. This is used for rehashing
void HashTable::updateTableSize(){
  //double the tableSize
  tableSize *= 2;
  //set isPrime to false
  bool isPrime = false;
  //loop while isPrime is false
  while(!isPrime){
    //assume the current number is prime by setting isPrime to true
    isPrime = true;
    //loop from 2 to tableSize/2
    for(unsigned int i = 2; i <= tableSize/2; i++){
      //if the new tableSize is evenly divisible by the current i
      if(tableSize % i == 0)
        //then set isPrime to false;
        isPrime = false;
    }
    //if isPrime is false increment the tableSize by 1
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
