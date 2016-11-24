#include <iostream>
#include <string>

using namespace std;

int const DEFAULT_SIZE = 256;

struct Variable{
  string word;
  unsigned numberOfOccurences;
  Variable(){ numberOfOccurences = 0; };
  Variable(string word);
};

class HashTable{
  public:
    HashTable();          // default constructor with default size 256
    HashTable(int size);  // constructor with size given
    ~HashTable();         // destructor for the table
    int  lookup(string value);  //lookup only
    int  lookupInsert(string value);  //lookup and insert
    //int remove(const  string value);
  private:
     // Your declarations go here!
     unsigned long hash(unsigned char *str);
     Variable *frequencyTable;
     unsigned long tableSize;
     double loadFactor;
};
