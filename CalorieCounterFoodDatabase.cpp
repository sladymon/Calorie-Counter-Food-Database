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
//Get hash working with specified size
//Get hash traverse to work for writing to file
//Get secondaryBST search to print all matching items

//CHECK THAT ONLY HASH DELETES



using namespace std;

//<<<<<<< Updated upstream
//Shannon's files
const string INPUT_FILE = "/Users/Shannon/Documents/GitHub/Calorie-Counter-Food-Database/foodInput.txt";
const string OUTPUT_FILE = "/Users/Shannon/Documents/GitHub/Calorie-Counter-Food-Database/foodOutput.txt";

//Wendy's files
//const string INPUT_FILE = "/Users/wendymartell/Dropbox/GITHUB/Food-Calorie-Counter-22C-2015/Calorie-Counter-Food-Database/foodInput.txt";
//const string OUTPUT_FILE = "/Users/wendymartell/Dropbox/GITHUB/Food-Calorie-Counter-22C-2015/Calorie-Counter-Food-Database/foodOutput.txt";

//Shuti's files
//const string INPUT_FILE = "foodInput.txt";
//const string OUTPUT_FILE = "foodOutput.txt";

//Deepika's files
//=======
//const string INPUT_FILE = "/Users/wendymartell/Dropbox/GITHUB/Food-Calorie-Counter-22C-2015/Calorie-Counter-Food-Database/foodInput.txt";
//const string INPUT_FILE = "/Users/Shannon/Documents/GitHub/Calorie-Counter-Food-Database/foodInput.txt";
//>>>>>>> Stashed changes
//const string INPUT_FILE = "D:\\foodInput.txt";
//const string OUTPUT_FILE = "D:\\foodOutput.txt";


void displayIndentedNode(Food* anItem, int level);
void displayFood(Food& anItem);
int compareBST(Food* food1, Food* food2);
int compareBSTSecondary(Food* food1, Food* food2);


/////////////////////////////////// Stand Alone Functions /////////////////////////////////////

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
// Author - Shannon Ladymon
// displaySecondaryFoods -  Displays all informationg for a food.
//          Is passed to BST function that displays all foods that
//          match a secondary key.
// @param anItem - pointer to Food to be displayed
// @param level - current level of tree
//*********************************************************************
void displayFood(Food& anItem)
{
    anItem.displayFood();
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


/////////////////////////////////// Constructors/Destructor /////////////////////////////////////

//*********************************************************************
// Author - Shannon Ladymon
// Constructor - initializes the hashSize and inputCounter, and
//          dynamically allocates the primaryBST, secondaryBST, and
//          hash.
//*********************************************************************
CalorieCounterFoodDatabase::CalorieCounterFoodDatabase()
{
	this->hashSize = 10; //FIXME: Change this to 0 later once determineHashSize is working
	this->inputCounter = 0;
	primaryBST = new BinarySearchTree<Food>(compareBST);
	secondaryBST = new BinarySearchTree<Food>(compareBSTSecondary);
    hash = new HashTable(hashSize);
}

//*********************************************************************
// Author - Shannon Ladymon
// Overloaded Constructor - initializes the hashSize based on input
//          parameter, the inputCounter, dynamically allocates the
//          primaryBST, secondaryBST, and hash.
//*********************************************************************
CalorieCounterFoodDatabase::CalorieCounterFoodDatabase(int hashSize)
{
    this->hashSize = hashSize;
    this->inputCounter = 0;
    primaryBST = new BinarySearchTree<Food>(compareBST);
    secondaryBST = new BinarySearchTree<Food>(compareBSTSecondary);
    hash = new HashTable(hashSize);
}


//FIXME: Is this how the destructor should work?  How are items actually being deleted?
//why isn't there conflict?
//*********************************************************************
// Author - Shannon Ladymon
// Destructor - deletes dynamically allocated data structures:
//          primaryBST, secondaryBST, hash
//*********************************************************************
CalorieCounterFoodDatabase::~CalorieCounterFoodDatabase()
{
    delete primaryBST;
    delete secondaryBST;
    delete hash;
}


/////////////////////////////////// Welcome/Goodbye Messages /////////////////////////////////////

//*********************************************************************
// Author - Shannon Ladymon
// welcome - displays a welcome message with info on project
//*********************************************************************
void CalorieCounterFoodDatabase::welcome() const
{
    cout << "************************************************************" << endl
    << "Welcome to the Calorie Counter Food Database!" << endl << endl
    << "This database allows users to keep track of various foods" << endl
    << "and their calorie and nutrition information" << endl << endl
    << "Authors:" << endl
    << "Shannon Ladymon - Team Leader and Add/Delete" << endl
    << "Shuti Wang - Search/List and Hash Size" << endl
    << "Deepika Metkar - Binary Search Tree and File I/O" << endl
    << "Wendy Martell - Hash Table" << endl
    << "************************************************************" << endl << endl;
}

//*********************************************************************
// Author - Shannon Ladymon
// goodbye - displays a goodbye message
//*********************************************************************
void CalorieCounterFoodDatabase::goodbye() const
{
    cout << "Goodbye!  Thank you for using Calorie Counter Food Database\n";
}


/////////////////////////////////// Read/Write/Insert Functions /////////////////////////////////////


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
    inFile.open(fileName);
    if (!inFile)
    {
        cout << "Error opening input file!\n";
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
        insertInDataStructures(foodObj);
    }
    
    return true;
}

//*********************************************************************
// Author - Deepika Metkar, Shannon Ladymon
// readFile - reads a file of data for food, creates food objects,
//          and inserts them in the data structures
// @param fileName - the name of the file to be read
// @return - true if able to read file and if not empty
//*********************************************************************
bool CalorieCounterFoodDatabase::writeFile(const char* fileName)
{
    ofstream outfile(fileName);
    if (!outfile)
    {
        cout << "Error opening output file!\n";
        return false;
    }
    
    cout << "TESTING: writeFile is called\n";
    
    //FIXME: call hashItemsList function
    // loop through it
    //outfile << inputFoodToOutputString(food);
    outfile.close();
    return true;
}

//*********************************************************************
// Author - Shannon Ladymon
// insertInDataStructures - inserts a food pointer into all data
//          structures (primaryBST, secondaryBST, hash) if it is
//          a unique key
// @param food - a pointer to the food to be inserted
// @return - true if able to insert
//*********************************************************************
bool CalorieCounterFoodDatabase::insertInDataStructures(Food* food)
{
    string foodName = food->getName();
    if(hash->find_Item(*food))
    {
        cout << "Unable to insert " << foodName << " because it is not a unique name" << endl;
        return false;
    }
    
    primaryBST->insert(food);
    secondaryBST->insert(food);
    //if (hash->getLoadFactor() > 75)
    // { rehash()}
    
    hash->insert(food);
    return true;
}

//*********************************************************************
// Author - Deepika Metkar
// inputFoodToOutputString - converts information from a Food pointer
//          to a string with the data
// @param food - the Food pointer to get the information from
// @return - the string with all information on the food
//*********************************************************************
string CalorieCounterFoodDatabase::inputFoodToOutputString(Food* food) const
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
Food* CalorieCounterFoodDatabase::inputStringToFood(string input) const
{
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

//*********************************************************************
// Author - Shannon Ladymon
// enterFoodManually - prompts a user to enter a food's information
//          and creates a food object dynamically with that info
// @return - a pointer to the food created
//*********************************************************************
Food* CalorieCounterFoodDatabase::enterFoodManually() const
{
    string name, category, amountStr, caloriesStr, fiberStr, sugarStr, proteinStr, fatStr;
    int amount, calories, fiber, sugar, protein, fat;
    
    cout << "\nEnter the name of the food you would like to add: ";
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
    return food;
}


/////////////////////////////////// Menu/Option Manager Functions /////////////////////////////////////

//*********************************************************************
// Author - Shannon Ladymon
// menu - a menu which allows users to enter choices for actions until
//          quitting
//*********************************************************************
void CalorieCounterFoodDatabase::menu()
{
    welcome();
    string choiceStr;
	char choice = 'A'; //default to enter the while loop
	displayMenu();

	while (choice != 'Q')
	{
		cout << "\nPlease enter the option of your choice ('Q' to quit, 'H' to see option list): ";
		getline(cin, choiceStr);
        cout << endl;
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
		case 'W': writeFile(OUTPUT_FILE.c_str());
			break;
		case 'G': hash->statistics();
			break;
		case 'H': displayMenu();
			break;
            case 'Q': writeFile(OUTPUT_FILE.c_str());
            goodbye();
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
	cout << "\nMenu Options:" << endl
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
	cout << "\nList Menu Options:" << endl
		<< "I - Special print, as an indented list" << endl
		<< "U - List unsorted data." << endl
		<< "P - List data sorted by the primary key" << endl
        << "S - List data sorted by the secondary key" << endl;
}

//*********************************************************************
// Author - Shannon Ladymon
// displayInsertMenu - a listing of the insert menu options
//*********************************************************************
void CalorieCounterFoodDatabase::displayInsertMenu() const
{
    cout << "\nInsert Menu Options:" << endl
    << "M - Enter a food manually" << endl
    << "S - Enter an input string" << endl
    << "F - Enter multiple foods via file" << endl;
}

//*********************************************************************
// Author - Shannon Ladymon
// insertManager - manages any insertion of new Food items into the
//          data structures.  Offers different options for insertion
//          and validates input before inserting.  Will display an
//          error message if unable to insert.
//*********************************************************************
void CalorieCounterFoodDatabase::insertManager()
{

    string choiceStr;
    string inputString;
    string inputFile;
    char choice;
    Food* toInsert;
    displayInsertMenu();

    do
    {
        cout << "\nPlease enter the option of your choice: ";
        getline(cin, choiceStr);
        choice = toupper(choiceStr[0]);
        cout << endl;
        
        switch (choice)
        {
            case'M': toInsert = enterFoodManually();
                insertInDataStructures(toInsert);
                break;
            case'S': cout << "\nEnter the input string: " << endl;
                getline(cin, inputString);
                toInsert = inputStringToFood(inputString);
                insertInDataStructures(toInsert);
                break;
            case'F': cout << "\nEnter the name of the file to read: " << endl;
                getline(cin, inputFile);
                readFile(inputFile.c_str());
                break;
            default: cout << choice << " is an invalid option."
                << " Please choose one of the following options: \n";
                displayInsertMenu();
        }
        
    } while (choice != 'M' && choice != 'S' && choice != 'F');
}

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
	cout << "\nEnter food name to be deleted: ";
	getline(cin, name);
    cout << endl;
    
    Food* toDelete = new Food();
	toDelete->setName(name);

    if(!hash->find_Item(*toDelete))
    {
        cout << "Unable to find " << name << ", so it cannot be removed" << endl;
        return false;
    }

	if (!primaryBST->remove(toDelete))
    {
        cout << "Unable to remove " << name << " from primaryBST" << endl;
        cout << "Suggestion: restart your program - this is an unexpected error.\n";
    }
    
    if(!secondaryBST->remove(toDelete, compareBST))  //FIXME: Why doesn't this crash when trying to delete actual item again?
    {
        cout << "Unable to remove " << name << " from secondaryBST" << endl;
        cout << "Suggestion: restart your program - this is an unexpected error.\n";
    }
    
    if(!hash->delete_Item(*toDelete))
    {
        cout << "Unable to remove " << name << " from hash" << endl;
        cout << "Suggestion: restart your program - this is an unexpected error.\n";
    }
    
    cout << name << " was successfully deleted" << endl;
    
    delete toDelete;
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
		cout << "\nSearch Menu Options: \n"
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
		cout << "\nEnter the food name(P) to search for: ";
		getline(cin, name);
		toSearch->setName(name);
        cout << endl;
        
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
		cout << "\nEnter the food category(S) to search for: ";
		getline(cin, name);
		toSearch->setCategory(name);
        cout << endl;
        
        
		if(!secondaryBST->getEntry(toSearch, *toReturn))
        {
            cout << "Could not find " << name << endl;
        }
        else
        {
            secondaryBST->printAllMatches(toSearch, displayFood);
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

		cout << "\nPlease enter the option of your choice: ";
		getline(cin, choiceStr);
		choice = toupper(choiceStr[0]);
        cout << endl;
        
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


/////////////////////////////////// Hash Functions /////////////////////////////////////


//TODO: Write this
void CalorieCounterFoodDatabase::rehashing()
{
	cout << "Rehashing called" << endl;
}
