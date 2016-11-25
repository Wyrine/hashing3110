#include <iostream>
#include <string>

using namespace std;


int const DEFAULT_SIZE = 256;
double const MAX_LOAD_FACTOR = 0.5;
#define HASH_MOD hash(bucket) % tableSize

class HashTable;

class Variable{
  string word;
  int frequency;
  Variable(){ frequency = 0; };
  bool canInsert(string bucket);
  friend class HashTable;
};

class HashTable{
  public:
    HashTable();          // default constructor with default size 256
    HashTable(int size);  // constructor with size given
    ~HashTable();         // destructor for the table
    int lookup(string bucket);  //lookup only
    int lookupInsert(string bucket);  //lookup and insert
    void printTable();
    double getLoad() { return loadFactor; }
    //int remove(const  string bucket);
  private:
     // Your declarations go here!
     bool insert(string bucket, Variable* frequencyTable, int loc, bool upNum);
     void reHash();
     unsigned long hash(string str);
     void updateLoad();
     void updateTableSize();
     Variable *frequencyTable;
     unsigned long tableSize;
     double loadFactor;
     int numItemsInTable;
};
