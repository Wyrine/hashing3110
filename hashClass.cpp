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
  unsigned int loc = HASH_MOD, startLoc, returnVar;
  //call insert to put the bucket into the table
  insert(bucket, frequencyTable, loc, true);
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

//insert is at the heart of this program. It purely checks to see if the element can be inserted
//in the current location and if it can then it does so, otherwise it loops to the next element
//in the scope version of frequencyTable in case of rehashing and attempts to do the same there
void HashTable::insert(string bucket, Variable* frequencyTable, unsigned int loc, bool upNum,
  unsigned int prevFreq){
  //assigning the curLoc to be the value of loc incase of a collision
  unsigned int curLoc = loc;
  do{
    //this is only needed in a collision case, if the curLoc is the same as the tableSize
    //then we set it to 0 so we don't access elements outside of our range.
    if(curLoc == tableSize ) curLoc = 0;
    //if we can insert in this location
    if(frequencyTable[curLoc].canInsert(bucket)){
      if (upNum){ //if we are inserting normally and not rehashing
        //increment the frequency
        frequencyTable[curLoc].frequency++;
        //if this word is not in the table
        if(frequencyTable[curLoc].frequency == 1){
          //copy the bucket over to the current location
          frequencyTable[curLoc].word = bucket;
          //update the number of elements in the table
          numItemsInTable++;
        }
      }	else { //otherwise we are rehashing
        //copy over frequency and the bucket into the frequencyTable
        frequencyTable[curLoc].frequency = prevFreq;
        frequencyTable[curLoc].word = bucket;
      }
      //return since insertion is complete
      return;
    }
    //if we have gotten here then a collision has occurred, so we try the next
    //element by incrementing curLoc by 1
    curLoc++;
  //and loop while curLoc is not the same as loc which is our starting location
  }while(curLoc != loc);
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
    //call this function again in case that reHash did not change the loadFactor by much
    //which this will only be useful for smaller table sizes
    updateLoad();
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

//rehash is called whenever the loadFactor is >= MAX_LOAD_FACTOR and it creates
//a new table with the size being at least double the current tableSize but the
//tableSize is always going to be a prime number and then loops through the old table
//and hashes each element into the new table and calls insert to insert it
void HashTable::reHash() {
  //setting the prevSize to be the old tableSize
  //and making some other variables
	unsigned int prevSize = tableSize, loc, prevFreq;
	string bucket;
  //getting a new tableSize
	updateTableSize();
  //allocating a new table with that new tableSize
	Variable* newTable = new Variable[tableSize]();
  //looping through the old table from start to end
	for (unsigned int i = 0; i < prevSize; i++) {
    //if the frequency of the current element is greater than 0
		if (frequencyTable[i].frequency > 0) {
      //copying the data members of this index from the old table
			bucket = frequencyTable[i].word;
			prevFreq = frequencyTable[i].frequency;
      //hashing that word with the new tableSize
			loc = HASH_MOD;
      //inserting into the new table
      insert(bucket, newTable, loc, false, prevFreq);
		}
	}
  //update the loadFactor
	loadFactor = numItemsInTable / tableSize;
  //deallocate the oldTable
	frequencyTable = NULL;
	delete[] frequencyTable;
  //set frequencyTable to be the new table
	frequencyTable = newTable;
}
