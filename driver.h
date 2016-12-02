//Kirolos Shahat
//libraries and prototypes for the driver
//driver.h

#include <iostream>
#include <fstream>
#include <time.h>
#include "hashClass.h"

//function prototypes
void readFile(string fileName);
int getSize();
void userUpdate(HashTable* myTable, double startTime);
void mainMenu(HashTable *myTable);
