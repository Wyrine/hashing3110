//Kirolos Shahat
//HashTable and Variable class definitions
//hashClass.h

#include <iostream>
#include <string>

using namespace std;

//constants used, default table size is 256
int const DEFAULT_SIZE = 256;
//max load factor is .5
double const MAX_LOAD_FACTOR = 0.5;
//preprocessing directive which calls hash(bucket) and mods it by the tableSize
#define HASH_MOD hash(bucket) % tableSize

//prototype of the HashTable class
class HashTable;

//Variable class definition
class Variable{
  //private data members
  string word;
  unsigned int frequency;
  //private methods
  //constructor sets the frequency to 0
  Variable(){ frequency = 0; };
  //canInsert returns true if the word is the same as the bucket or if
  //the frequency is 0, otherwise returns false
  bool canInsert(string bucket) {
	return (word == bucket || frequency == 0) ? true : false;
  }
  //friend the class HashTable
  friend class HashTable;
};

//HashTable class
class HashTable{
  public:
    HashTable();          // default constructor with default size 256
    HashTable(int size);  // constructor with size given
    int lookup(string bucket);  //lookup only
    int lookupInsert(string bucket);  //lookup and insert
    //getLoad returns the loadFactor
    double getLoad() { return loadFactor; }
    void printTable();
  	~HashTable();         // destructor for the table
  private:
     // Private data members
  	 Variable *frequencyTable;
  	 unsigned long tableSize;
  	 double loadFactor;
  	 unsigned int numItemsInTable;

  	 //private method prototypes
     bool insert(string bucket, Variable* frequencyTable, unsigned int &loc, bool upNum, unsigned int prevFreq = 0);
  	 unsigned long hash(string str);
  	 void updateLoad();
  	 void updateTableSize();
     void reHash();
};
