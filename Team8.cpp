//*********************************************************************
//                      DRIVER FOR TEAM 8 PROJECT
//
// Author: Shuti Wang, Deepika Metkar
// Description: Contains driver code for the project.  Main determines
//          the hash size and builds a CalorieCounterFoodDatabase,
//          then runs the menu.
//
//*********************************************************************

#include <iostream>
#include <fstream>
#include "CalorieCounterFoodDatabase.h"

using namespace std;

//Shannon's files
//const string INPUT_FILE = "/Users/Shannon/Documents/GitHub/Calorie-Counter-Food-Database/foodInput.txt";
//const string OUTPUT_FILE = "/Users/Shannon/Documents/GitHub/Calorie-Counter-Food-Database/foodOutput.txt";

//Wendy's files
//const string INPUT_FILE = "/Users/wendymartell/Dropbox/GITHUB/Food-Calorie-Counter-22C-2015/Calorie-Counter-Food-Database/foodInput.txt";
//const string OUTPUT_FILE = "/Users/wendymartell/Dropbox/GITHUB/Food-Calorie-Counter-22C-2015/Calorie-Counter-Food-Database/foodOutput.txt";


//Shuti's files
const string INPUT_FILE = "foodInput.txt";
const string OUTPUT_FILE = "foodOutput.txt";

//Deepika's files
//const string INPUT_FILE = "D:\De Anza\5. Spring 2015\CIS 22C_Delia Gârbacea\Topic 14_Project Presentations\Calorie-Counter-Food-Database\foodInput.txt";
//const string OUTPUT_FILE = "D:\De Anza\5. Spring 2015\CIS 22C_Delia Gârbacea\Topic 14_Project Presentations\Calorie-Counter-Food-Database\foodOutput.txt";

int determineHashSize(const char* fileName);


int main()
{
	//CalorieCounterFoodDatabase* a = new CalorieCounterFoodDatabase(determineHashSize(INPUT_FILE.c_str()));
    CalorieCounterFoodDatabase* a = new CalorieCounterFoodDatabase(10);
    
	if (!a->readFile(INPUT_FILE.c_str()))
	{
		cout << "Unable to open File, so exiting program \n GoodBye!!!\n";
		return 1;
	}
		

	a->menu(OUTPUT_FILE.c_str());
    delete a;
	return 0;
}

//*********************************************************************
// Author - Shuti Wang, Deepika Metkar
// determineHashSize - reads input file to determine what size hash
//          should be
// @param filename - the input file
// @return - the size of the hash table
//*********************************************************************
int determineHashSize(const char* fileName)
{
	int inputCounter = 0;
	ifstream inFile;
	string temp;

	inFile.open(fileName);
	if (!inFile)
	{
		cout << "Error opening " << fileName << "!\n";
		return false;
	}

	if (inFile.eof())
	{
		cout << "File is empty" << endl;
		return false;
	}

	while (getline(inFile, temp))
	{
		inputCounter++;
	}
	inFile.clear();
	inFile.seekg(0, inFile.beg);
    
    inFile.close();


	return nextPrime(inputCounter * 2);
}
