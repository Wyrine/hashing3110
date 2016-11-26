#include "driver.h"

using namespace std;

void readFile(){
  ifstream input("frequency.txt");
  string inData;
  if(input.fail()) exit(0);
  int tableSize = getSize();
  HashTable myTable((tableSize == -1) ? : tableSize );
  double startTime = clock();
  while(input >> inData){
    myTable.lookupInsert(inData);
  }
  double totalTime = (clock() - startTime) / CLOCKS_PER_SEC;
  cout << "It took " << totalTime << " to build the frequency table.\n";
  cout << "The load factor is: " << myTable.getLoad() << endl;
  mainMenu(myTable);
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

void mainMenu(HashTable myTable){
  char yesOrNo;
  string value;
  do{
    cout << "Would you like to search for a word? (y or n): \n";
    cin >> yesOrNo;
    if(yesOrNo == 'y' || yesOrNo == 'Y'){
      cout << "Enter the word to be search for frequency count: ";
      cin >> value;
      cout << value << " appeared " << myTable.lookup(value) << " times.\n";
    }
  }while(yesOrNo == 'y' || yesOrNo == 'Y');
  cout << "Thanks for using this program! Goodbye!\n";
}
