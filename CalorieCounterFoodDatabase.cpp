//*********************************************************************
//                  CALORIE COUNTER FOOD DATABASE CLASS
//
// Author: Shannon Ladymon, Deepika Metkar, Shuti Wang
// Description: CalorieCounterFoodDatabase maintains a database of food
//              objects in three data structures: a BinarySearchTree
//              based on food names (primary, unique key), a
//              BinarySearchTree based on food categories (secondary,
//              non-unique key), and a HashTable based on food names.
//
//*********************************************************************

#include "CalorieCounterFoodDatabase.h"
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>


//TODO:
//Write documentation
//Get hash working with specified size
//do input validation



using namespace std;

//const string INPUT_FILE = "/Users/wendymartell/Dropbox/GITHUB/Food-Calorie-Counter-22C-2015/Calorie-Counter-Food-Database/foodInput.txt";
const string INPUT_FILE = "/Users/Shannon/Documents/GitHub/Calorie-Counter-Food-Database/foodInput.txt";
//const string INPUT_FILE = "D:\\foodInput.txt";



//FIXME: Add a regular displayTree function
void displayIndentedNode(Food* anItem, int level);
int compareBST(Food* food1, Food* food2);
int compareBSTSecondary(Food* food1, Food* food2);

int main()
{

	CalorieCounterFoodDatabase a;
	a.readFile(INPUT_FILE.c_str());
	//cout << "TESTING tree size: " << a.getPrimaryBST()->size() << endl;

	a.menu();
	return 0;
}

//*********************************************************************
// Author - Shannon Ladymon
// displayIndentedNode - Displays food name, indented with
//		tabs dependent on level.  Is passed to BST functions
// @param anItem - pointer to Food to be displayed
// @param level - current level of tree
//*********************************************************************
void displayIndentedNode(Food* anItem, int level)
{
    for (int i = 1; i <= level; i++)
    {
        cout << "\t";
    }
    cout << level + 1 << ". " << anItem->getName() << endl;
}

//*********************************************************************
// Author - Deepika Metkar
// compareBST - a comparison function to work with the primary key, name
// @param food1 - a pointer to the first food to compare
// @param food2 - a pointer to the second food to compare
// @return - 1 if food1 is greater; 0 if equal; -1 if food1 is less
//*********************************************************************
int compareBST(Food* food1, Food* food2)
{
    if (food1->getName() > food2->getName())
    {
        return 1;
    }
    else if (food1->getName() < food2->getName())
    {
        return -1;
    }
    return 0;
}

//*********************************************************************
// Author - Deepika Metkar
// compareBSTSecondary - a comparison function to work with the
//          secondary key, category
// @param food1 - a pointer to the first food to compare
// @param food2 - a pointer to the second food to compare
// @return - 1 if food1 is greater; 0 if equal; -1 if food1 is less
//*********************************************************************
int compareBSTSecondary(Food* food1, Food* food2)
{
    if (food1->getCategory() > food2->getCategory())
    {
        return 1;
    }
    else if (food1->getCategory() < food2->getCategory())
    {
        return -1;
    }
    return 0;
}

//*********************************************************************
// Author - Shannon Ladymon
// Constructor - initializes the hashSize and inputCounter, and
//          dynamically allocates the primaryBST, secondaryBST, and
//          hash.
//*********************************************************************
CalorieCounterFoodDatabase::CalorieCounterFoodDatabase()
{
	this->hashSize = 10; //FIXME: Change this later to work with determinehashsize, etc. (possibly overload)
	this->inputCounter = 0;
	primaryBST = new BinarySearchTree<Food>(compareBST);
	secondaryBST = new BinarySearchTree<Food>(compareBSTSecondary);
    hash = new HashTable(hashSize);
}

CalorieCounterFoodDatabase::~CalorieCounterFoodDatabase()
{
    //TODO: Determine what should go here and how/where things should be deleted
}

//*********************************************************************
// Author - Deepika Metkar
// inputFoodToOutputString - converts information from a Food pointer
//          to a string with the data
// @param food - the Food pointer to get the information from
// @return - the string with all information on the food
//*********************************************************************
string CalorieCounterFoodDatabase::inputFoodToOutputString(Food* food)
{
	stringstream calories, fat, fiber, protein, sugar;
	calories << food->getCalories();
	fat << food->getFat();
	fiber << food->getFiber();
	protein << food->getProtein();
	sugar << food->getSugar();

	return food->getName() + "," + food->getCategory() + "," + calories.str() + "," + fat.str() + "," + fiber.str() + ","
		+ protein.str() +"," + sugar.str();
}


//*********************************************************************
// Author - Deepika Metkar, Shannon Ladymon
// inputStringToFood - converts an input string into a food object
// @param input - string with the information for a new food item
// @return - true for tree being printed
//*********************************************************************
Food* CalorieCounterFoodDatabase::inputStringToFood(string input)
{
   //FIXME: add a check for incorrect input?
    string token;
    string fName;
    string fCatagery;
    int amount;
    int calories;
    int fiber;
    int sugar;
    int protein;
    int fat;
    istringstream ss(input);
    
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
    
    Food* foodObj = new Food(fName, fCatagery, amount, calories, fiber, sugar, protein, fat);
    return foodObj;
}

//FIXME: What is this?  Do I need this?
/*
void printToFile(Food* food)
{
	//ofstream myfile;
	//myfile.open("OutPut.txt");
	//myfile << inputFoodToOutputString(food);
	//myfile.close();
	cout << inputFoodToOutputString(food);
}
*/

//*********************************************************************
// Author - Deepika Metkar, Shannon Ladymon
// readFile - reads a file of data for food, creates food objects,
//          and inserts them in the data structures
// @param fileName - the name of the file to be read
// @return - true if able to read file and if not empty
//*********************************************************************
bool CalorieCounterFoodDatabase::readFile(const char* fileName)
{
	ifstream inFile;

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
	while (getline(inFile, temp))
	{
        Food* foodObj = inputStringToFood(temp);
        
        //FIXME: Add a check for unique item
		primaryBST->insert(foodObj);
		secondaryBST->insert(foodObj);
        hash->insert(foodObj);

	}
	return true;
}

//TODO: Write this
bool CalorieCounterFoodDatabase::writeToOutputFile(const char* fileName)
{
	//primaryBST->printTreeInOrder(printToFile);
	return true;
}


//*********************************************************************
// Author - Shannon Ladymon
// menu - a menu which allows users to enter choices for actions until
//          quitting
//*********************************************************************
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
		case 'G': hash->statistics();
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

//*********************************************************************
// Author - Shannon Ladymon
// displayMenu - a listing of the menu options
//*********************************************************************
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

//*********************************************************************
// Author - Shuti Wang
// displayListMenu - a listing of the list menu options
//*********************************************************************
void CalorieCounterFoodDatabase::displayListMenu() const
{
	cout << "List Menu Options" << endl
		<< "I - Special print, as an indented list" << endl
		<< "U - List unsorted data." << endl
		<< "P - List data sorted by the primary key" << endl
        << "S - List data sorted by the secondary key" << endl;
}



//FIXME: Add options: Enter food individually, enter line of food, enter file of foods
//*********************************************************************
// Author - Shannon Ladymon
// insertManager - manages any insertion of new Food items into the
//          data structures.  Offers different options for insertion
//          and validates input before inserting.  Will display an
//          error message if unable to insert.
//*********************************************************************
void CalorieCounterFoodDatabase::insertManager()
{
    //call menu with options - add individual food, add foodinputstring, add file
    
    //make this a subfunction
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
    
    
    //only insert if unique
	primaryBST->insert(food);
    secondaryBST->insert(food);
    hash->insert(food);
    

	//cout << "TESTING: Size: " << primaryBST->size() << endl;

}

//FIXME: Don't have a return value - get this to work inside itself
//*********************************************************************
// Author - Shannon Ladymon
// deleteManager - manages deletion of Food items from all data
//          structures (primaryBST, secondaryBST, hash).  Will display
//          an error message if unable to find or delete.
// @return - true if able to find and delete
//*********************************************************************
bool CalorieCounterFoodDatabase::deleteManager()
{
	string name;
	cout << "Enter food name to be deleted: ";
	getline(cin, name);

    Food* toSearch = new Food();
	toSearch->setName(name);

    if(!hash->find_Item(*toSearch))
    {
        cout << "Unable to find " << name << ", so it cannot be removed" << endl;
        return false;
    }

	if (!primaryBST->remove(toSearch))  //FIXME: What should happen if unable to remove from only one data structure?
    {
        cout << "Unable to remove " << name << endl;
        return false;
    }
    
    if(!secondaryBST->remove(toSearch, compareBST))  //FIXME: Why doesn't this crash when trying to delete actual item again?
    {
        cout << "Unable to remove " << name << endl;
        return false;
    }
    
        
    //TODO: DELETE IN HASH
    
    cout << name << " was successfully deleted" << endl;

	cout << "TESTING: Size: " << primaryBST->size() << endl;
    
    delete toSearch;
    return true;
}


//*********************************************************************
// Author - Shuti Wang
// searchManager - manages searching for a Food item in the data
//          structures.  Offers options to search by primary or
//          secondary key.
//*********************************************************************
void CalorieCounterFoodDatabase::searchManager() const
{
	string name;
	string choiceStr;
	char choice;
	
	do{
		cout << "Search Menu Options: \n"
			 << "P - Search by Primary key (by name)\n"
			 << "S - Search by Secondary key (by category)\n";
		getline(cin, choiceStr);
		choice = toupper(choiceStr[0]);
        
        if (choice != 'P' && choice != 'S')
        {
            cout << "Invalid option.  Please enter a valid option.\n";
        }

	} while (choice != 'P' && choice != 'S');
    
	Food* toSearch = new Food();
	Food* toReturn = new Food();
	
	if (choice == 'P')
	{
		cout << "Enter the food name(P) to search for: ";
		getline(cin, name);
		toSearch->setName(name);
        
        if (hash->find_Item(*toSearch))
        {
            toSearch->displayFood();
        }
        else
        {
            cout << name << " was not found." << endl;
        }
	}
	else if (choice == 'S') //FIXME: display ALL Matches - need to write additional search function for all matches
	{
		cout << "Enter the food category(S) to search for: ";
		getline(cin, name);
		toSearch->setCategory(name);
        
        
		if(!secondaryBST->getEntry(toSearch, *toReturn))
        {
            cout << "Could not find " << name << endl;
        }
        else
        {
            toReturn->displayFood();
        }
	}

    delete toSearch;
    delete toReturn;

}



//*********************************************************************
// Author - Shuti Wang
// listManager - manages listing all food items stored in data
//          structures.  Offers options to display by indented
//          list, unsorted list, primary sorted list, or secondary
//          sorted list.
//*********************************************************************
void CalorieCounterFoodDatabase::listManager() const
{
	string name;
	string choiceStr;
	char choice;
	displayListMenu();
	do{

		cout << "Please enter the option of your choice ('H': go back to the main menu): ";
		getline(cin, choiceStr);
		choice = toupper(choiceStr[0]);

		switch (choice)
		{
		case'I': hash->print_Indented_Items_with_Index_from_Bucket();
			break;
		case'U': hash->print_Table();
			break;
		case'P': primaryBST->printTreeAsIndentedList(displayIndentedNode); //FIXME: should this be a list or an indented list?
			break;
		case'S': secondaryBST->printTreeAsIndentedList(displayIndentedNode); //FIXME: should this be a list or an indented list?
			break;
		default: cout << choice << " is an invalid option."
			<< " Please choose one of the following options: \n";
			displayListMenu();
		}

	} while (choice != 'I' && choice != 'U' && choice != 'P' && choice != 'S');
}

//Shuti
int CalorieCounterFoodDatabase::determineHashSize(const char* fileName)
{
	int inputCounter = 0;
	ifstream inFile("foodInput.txt");
	string temp;

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
	
	while (getline(inFile, temp))
	{
		inputCounter++;
	}
	inFile.clear();
	inFile.seekg(0, inFile.beg);
	

	return isPrime(inputCounter * 2);
	/*cout << "Determine Hash Size called" << endl;
	return 0;*/
}
// 
bool CalorieCounterFoodDatabase::isPrime(int inputCounter)
{
	int divisor = 6;
	if (inputCounter == 2 || inputCounter == 3) 
		return true;
	if (inputCounter % 2 == 0 || inputCounter % 3 == 0)
		return false;
	while (divisor * divisor - 2 * divisor + 1 <= inputCounter)
	{
		if (inputCounter % (divisor - 1))
			return false;
		if (inputCounter % (divisor + 1))
			return false;
			divisor += 6;
	}
	return true;

} 
// 
int CalorieCounterFoodDatabase::nextPrime(int size)
{
	//while (!isPrime(++size))

	return size;    // size is the hash size; which is the prime number, find place to return
}

//TODO: Write this
void CalorieCounterFoodDatabase::rehashing()
{
	cout << "Rehashing called" << endl;
}
