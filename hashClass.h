#include <iostream>
#include <string>

using namespace std;


int const DEFAULT_SIZE = 256;
double const MAX_LOAD_FACTOR = 0.5;
#define HASH_MOD hash(bucket) % tableSize

class HashTable;

class Variable{
  //private data members
  string word;
  unsigned int frequency;
  //private methods
  Variable(){ frequency = 0; };
  bool canInsert(string bucket) { 
	return (word == bucket || frequency == 0) ? true : false; 
  }
  //friend the class HashTable
  friend class HashTable;
  Variable operator=(Variable rhs) {
	  Variable temp;
	  temp.frequency = rhs.frequency;
	  temp.word = rhs.word;
	  return temp;
  }
};

class HashTable{
  public:
    HashTable();          // default constructor with default size 256
    HashTable(int size);  // constructor with size given
    int lookup(string bucket);  //lookup only
    int lookupInsert(string bucket);  //lookup and insert
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
     bool insert(string bucket, Variable* frequencyTable, unsigned int loc, bool upNum, unsigned int prevFreq = 0);
	 unsigned long hash(string str);
	 void updateLoad();
	 void updateTableSize();
     void reHash();
};
