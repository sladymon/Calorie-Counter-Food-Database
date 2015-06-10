//Author: Shannon Ladymon
#include "CalorieCounterFoodDatabase.h"
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>

using namespace std;

//const string INPUT_FILE = "/Users/wendymartell/Dropbox/GITHUB/Food-Calorie-Counter-22C-2015/Calorie-Counter-Food-Database/foodInput.txt";
//const string INPUT_FILE = "/Users/Shannon/Documents/GitHub/Calorie-Counter-Food-Database/foodInput.txt";
//const string INPUT_FILE = "foodInput.txt";
//// This is Deepika Testing ///////
/////
/////
///// This is Shuti Testing  //////
////
//// This is Shannon Testing /////
////
 
//TODO: Figure out how to sort differently for primaryBST & secondaryBST
	//(currently, overloaded operators only sort by primary)


//FIXME: Shannon added temporarily to test indented printing - need Deepika's version
//*********************************************************************
// displayIndentedNode - Displays student ID and level, indented with
//		tabs dependent on level.  Is passed to BST functions
// @param anItem - Student object to be displayed
// @param level - current level of tree
//*********************************************************************
void displayIndentedNode(Food & anItem, int level)
{
	for (int i = 1; i < level; i++)
	{
		cout << "\t";
	}
	cout << level << ". " << anItem.getName() << endl;
}

int main()
{
	CalorieCounterFoodDatabase a;
	a.readFile(INPUT_FILE.c_str());
	//cout << "TESTING tree size: " << a.getPrimaryBST()->size() << endl;

	a.menu();
	return 0;
}

CalorieCounterFoodDatabase::CalorieCounterFoodDatabase()
{
	this->hashSize = 0;
	this->inputCounter = 0;
	primaryBST = new BinarySearchTree<Food>();
	secondaryBST = new BinarySearchTree<Food>();
}


//Author: Deepika Metkar
bool CalorieCounterFoodDatabase::readFile(const char* fileName) //TODO: Shannon changed this
{
	ifstream inFile;
	string fName;
	string fCatagery;
	int amount;
	int calories;
	int fiber;
	int sugar;
	int protein;
	int fat;


	// Open file to read, if couldn't open, display error
	// and exit with false
	inFile.open(INPUT_FILE);
	if (!inFile)
	{
		cout << "Error opening \'foodInput.txt\' File!\n";
		return false;
	}

	if (inFile.eof())
	{
		cout << "File is empty" << endl;
		return false;
	}
	string temp;
	string token;
	while (getline(inFile, temp))
	{
		istringstream ss(temp);

		getline(ss, token, ';');
		fName = token;
		getline(ss, token, ';');
		fCatagery = token;
		getline(ss, token, ';');
		amount = std::stoi(token);
		getline(ss, token, ';');
		calories = std::stoi(token);
		getline(ss, token, ';');
		fiber = std::stoi(token);
		getline(ss, token, ';');
		sugar = std::stoi(token);
		getline(ss, token, ';');
		protein = std::stoi(token);
		getline(ss, token, ';');
		fat = std::stoi(token);

		Food* foodObj = new Food(fName, fCatagery, amount, calories, fiber, sugar, protein, fat); //TODO: Shannon changed this to dynamically allocated
		primaryBST->insert(*foodObj);  //TODO: Shannon changed this
		//TODO: add secondaryBST and Hash
		delete foodObj; //TODO: Shannon changed this

	}
	return true;
}

//Deepika
bool CalorieCounterFoodDatabase::writeToOutputFile(const char* fileName)
{
	return true;
}


void CalorieCounterFoodDatabase::menu()
{
	string choiceStr;
	char choice = 'A'; //default to enter the while loop
	cout << "Welcome to the Calorie Counter Food Database!" << endl;
	displayMenu();

	while (choice != 'Q')
	{
		cout << "Please enter the option of your choice ('Q' to quit, 'H' to see option list): ";
		getline(cin, choiceStr);
		choice = toupper(choiceStr[0]);

		switch(choice)
		{
		case 'A': insertManager();
			break;
		case 'D': deleteManager();
			break;
		case 'S': searchManager();
			break;
		case 'L': listManager();
			break;
		case 'W':  cout << "TODO: Call writeToOutPutFile\n";
			break;
		case 'G': cout << "TODO: Call statistics\n";
			break;
		case 'H': displayMenu();
			break;
		case 'Q': cout << "Goodbye!\n";
			break;
		default: cout << choice << " is an invalid option."
				<<" Please choose one of the following options: \n";
			displayMenu();


		}
	}
}

void CalorieCounterFoodDatabase::displayMenu() const
{
	cout << "Menu Options" << endl
		<< "A - Add new food entry" << endl
		<< "D - Delete food entry" << endl
		<< "S - Search for a food entry" << endl
		<< "L - List food entries" << endl
		<< "W - Write food entries to file" << endl
		<< "G - Get statistics" << endl
		<< "H - Help (see option list again)" << endl
		<< "Q - Quit" << endl;
}



//FIXME: Is this just called for add a new entry?
//FIXME: Should this ask for all the info to input separately?  Or should it ask for it in the input file manner?
void CalorieCounterFoodDatabase::insertManager()
{
	string name, category, amountStr, caloriesStr, fiberStr, sugarStr, proteinStr, fatStr;
	int amount, calories, fiber, sugar, protein, fat;

	cout << "Enter the name of the food you would like to add: ";
	getline(cin, name);
	cout << "Enter the category (fruit, vegetable, grain, protein, dairy): ";
	getline(cin, category);
	cout << "Enter the amount (in grams/mL): ";
	getline(cin, amountStr);
	amount = atoi(amountStr.c_str());
	cout << "Enter the calories: ";
	getline(cin, caloriesStr);
	calories = atoi(caloriesStr.c_str());
	cout << "Enter the fiber (in grams): ";
	getline(cin, fiberStr);
	fiber = atoi(caloriesStr.c_str());
	cout << "Enter the sugar (in grams): ";
	getline(cin, sugarStr);
	sugar = atoi(sugarStr.c_str());
	cout << "Enter the protein (in grams): ";
	getline(cin, proteinStr);
	protein = atoi(proteinStr.c_str());
	cout << "Enter the fat (in grams): ";
	getline(cin, fatStr);
	fat = atoi(fatStr.c_str());

	Food* food = new Food(name, category, amount, calories, fiber, sugar, protein, fat);
	primaryBST->insert(*food);
	delete food;

	cout << "TESTING: Size: " << primaryBST->size() << endl;


	//TODO: should call insert on hash and both BSTs given a food item

}

void CalorieCounterFoodDatabase::deleteManager() //should take a food argument
{
	string name;
	cout << "Enter food name to be deleted: ";
	getline(cin, name);

	Food* food = new Food();
	food->setName(name);
	primaryBST->remove(*food);

	//TODO: should call delete on hash and both BSTs given a food name
	delete food;

	cout << "TESTING: Size: " << primaryBST->size() << endl;
}


//Shuti
void CalorieCounterFoodDatabase::searchManager() const
{
	string name;
	cout << "Enter the food name to search for: ";
	getline(cin, name);

	Food* toSearch = new Food();
	Food* toReturn = new Food();
	toSearch->setName(name);
	primaryBST->getEntry(*toSearch, *toReturn);

	toReturn->displayFood();


	//should call BST getEntry
}



//Shuti
void CalorieCounterFoodDatabase::listManager() const
{
	cout << "TESTING Primary BST Indented Tree" << endl;
	primaryBST->printTreeAsIndentedList(displayIndentedNode);

	//TODO: add in rest of list manager
}

//Deepika
int CalorieCounterFoodDatabase::determineHashSize(int inputCounter)
{
	cout << "Determine Hash Size called" << endl;
	return 0;
}

//Deepika
void CalorieCounterFoodDatabase::rehashing()
{
	cout << "Rehashing called" << endl;
}
