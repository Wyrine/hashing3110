#include <iostream>
#include <string>

using namespace std;


int const DEFAULT_SIZE = 389;
double const MAX_LOAD_FACTOR = 0.5;
#define HASH_MOD hash(value) % tableSize

class HashTable;

class Variable{
  string word;
  int frequency;
  Variable(){ frequency = 0; };
  bool insertWord(string str);
  friend class HashTable;
};

class HashTable{
  public:
    HashTable();          // default constructor with default size 256
    HashTable(int size);  // constructor with size given
    ~HashTable();         // destructor for the table
    int lookup(string value);  //lookup only
    int lookupInsert(string value);  //lookup and insert
    void printTable();
    double getLoad() { return loadFactor; }
    //int remove(const  string value);
  private:
     // Your declarations go here!
     void reHash();
     unsigned long hash(string str);
     void updateLoad();
     void findPrime();
     Variable *frequencyTable;
     unsigned long tableSize;
     double loadFactor;
     int numItemsInTable;
};
