//Kirolos Shahat
//driver method definitions
//driver.cpp

#include "driver.h"

using namespace std;

//readFile takes a string as an argument which is the fileName and makes
//sure that the file is valid and then allocates a hashTable with the
//size being based on the users choice and then it reads in the data from the file
//into the table until all elements have been read from the file
//and then prints the time it took to make the table and the loadFactor for the
//table. Then calls mainMenu to handle the searching and then returns
void readFile(string fileName){
  //opening the file
  ifstream input(fileName);
  string inData;
  //if the file did not open, exit
  if(input.fail()) {
    cout << "Input file could not be opened. Exiting.\n";
    exit(0);
  }
  //calling getSize to get the tableSize from the user
  int tableSize = getSize();
  //creating a hashTable pointer and if tableSize is -1 call the default constructor
  //otherwise call the one argument constructor with the size provided by the user
  HashTable* myTable = (tableSize == -1) ? new HashTable() : new HashTable(tableSize);
  //getting the starting time
  double startTime = clock();
  //while there is data to read from the input file, read it into inData
  while(input >> inData){
    //call myTable's lookupInsert with inData to insert it
    myTable->lookupInsert(inData);
  }
  //closing the input file
  input.close();
  //the table has been fully created. Call userUpdate to give the user the information needed
  userUpdate(myTable, startTime);
  //calling mainMenu to ask the user stuff
  //mainMenu(myTable);
  myTable->printTable();
  //deallocating the class allocation
  myTable = NULL;
  delete myTable;
}

//userUpdate prints the time it took to create the table in milliseconds
//and prints the loadFactor in the table
void userUpdate(HashTable* myTable, double startTime){
  //set the totalTime to be time difference between now and the start and
  //divide that by the number of clock ticks per second
  //and multiply all of that by 1000 to convert from seconds to milliseconds
  double totalTime = ((clock() - startTime) / CLOCKS_PER_SEC) * 1000;
  //print that time out
  cout << "It took " << totalTime << " ms to build the frequency table.\n";
  //call getLoad from the table to print the loadFactor
  cout << "The load factor is: " << myTable->getLoad() << endl;
}

//getSize returns an integer which can either be -1 or >= 1 and that will be the tableSize
//it asks the user to give that information and makes sure it is valid
int getSize(){
  //set the tableSize to 1
  int tableSize = 1;
  do{
    //if the tableSize is not -1 or >= 1 print an error message
    if(tableSize < 1 && tableSize != -1)
      cout << "Size must greater than or equal to 1 or -1 for default. Try again.\n";
    cout << "Please enter the table size or -1 to use default Size: ";
    //get the size from the user
    cin >> tableSize;
  //loop while the given size is not valid
  }while(tableSize < 1 && tableSize != -1);
  //return that value
  return tableSize;
}

//mainMenu basically asks the user if they want to search for a word in the HashTable
//and they say y or n. if y, ask them for a search value and call lookup with that value
//otherwise exit the loop
void mainMenu(HashTable *myTable){
  //variables needed
  char yesOrNo;
  string value;
  do{
    //ask the user if they would like to search
    cout << "Would you like to search for a word? (y or n): \n";
    //read in their choice
    cin >> yesOrNo;
    //if their input was y
    if(yesOrNo == 'y' || yesOrNo == 'Y'){
      cout << "Enter the word to be search for frequency count: ";
      //get the word they want to search
      cin >> value;
      //and print the frequency from lookup
      cout << value << " appeared " << myTable->lookup(value) << " times.\n";
    }
  //notice the loop ends if they put anything other than y or Y
  }while(yesOrNo == 'y' || yesOrNo == 'Y');
  //thanks the user
  cout << "Thanks for using this program! Goodbye!\n";
}
