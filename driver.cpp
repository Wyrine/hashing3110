#include "driver.h"

using namespace std;

void readFile(){
  ifstream input("frequency.txt");
  string inData;
  if(input.fail()) exit(0);
  int tableSize = getSize();
  HashTable myTable(tableSize);
  double startTime = clock();
  while(input >> inData){
    myTable.lookupInsert(inData);
  }
  double totalTime = (clock() - startTime) / CLOCKS_PER_SEC;
  cout << "It took " << totalTime << " to build the frequency table.\n";
  myTable.printTable();
  input.close();
}

int getSize(){
  int tableSize = 1;
  do{
    if(tableSize < 1 && tableSize != -1) cout << "Size must be at least 1. Try again.\n";
    cout << "Please enter the table size or -1 to use default Size: ";
    cin >> tableSize;
  }while(tableSize < 1 && tableSize != -1);
  return tableSize;
}
