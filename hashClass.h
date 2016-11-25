#include <iostream>
#include <string>

using namespace std;


int const DEFAULT_SIZE = 389;
#define HASH_MOD hash(value) % tableSize

struct Variable{
  string word;
  int frequency;
  Variable(){ frequency = 0; };
  void lowerWord(string word);
};

class HashTable{
  public:
    HashTable();          // default constructor with default size 256
    HashTable(int size);  // constructor with size given
    ~HashTable();         // destructor for the table
    int lookup(string value);  //lookup only
    int lookupInsert(string value);  //lookup and insert
    void printTable();
    //int remove(const  string value);
  private:
     // Your declarations go here!
     unsigned long hash(string str);
     void updateLoad();
     Variable *frequencyTable;
     unsigned long tableSize;
     double loadFactor;
     int numItemsInTable;
};
