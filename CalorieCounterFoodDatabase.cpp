//*********************************************************************
//                  CALORIE COUNTER FOOD DATABASE CLASS
//
// Author: Shannon Ladymon, Deepika Metkar, Shuti Wang
// Class: 22C Spring2015
//
// Description: CalorieCounterFoodDatabase maintains a database of Food
//              objects in three data structures: a BinarySearchTree
//              based on food names (primary, unique key), a
//              BinarySearchTree based on food categories (secondary,
//              non-unique key), and a HashTable based on food names.
//
// Purpose: This file is used as the primary object for our project. It
//              maintains all of our data, manages the manipulation of
//              that data, and handles all user interaction through
//              various menus.
//
//*********************************************************************

#include "CalorieCounterFoodDatabase.h"
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>

//********FOR TEST RUN*********
const string PRIME_NUMBERS = "primeNumbers.txt";
//*****************************

//FOR DEVELOPERS
//const string PRIME_NUMBERS = "/Users/Shannon/Documents/GitHub/Calorie-Counter-Food-Database/primeNumbers.txt";
//const string PRIME_NUMBERS = "/Users/wendymartell/Dropbox/GITHUB/Food-Calorie-Counter-22C-2015/Calorie-Counter-Food-Database/primeNumbers.txt";
//Deepika:->
//const string PRIME_NUMBERS = "D:\De Anza\5. Spring 2015\CIS 22C_Delia G�rbacea\Topic 14_Project Presentations\Calorie-Counter-Food-Database\primeNumbers.txt";

using namespace std;


/////////////////////////////////// Constructors/Destructor /////////////////////////////////////

//*********************************************************************
// Author - Shannon Ladymon
// Constructor - initializes the hashSize and inputCounter to 0, and
//          dynamically allocates the primaryBST, secondaryBST, and
//          hash.
//*********************************************************************
CalorieCounterFoodDatabase::CalorieCounterFoodDatabase()
{
	this->hashSize = 0;
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

//*********************************************************************
// Author - Shannon Ladymon
// Destructor - deletes dynamically allocated data structures:
//          primaryBST, secondaryBST, hash
//*********************************************************************
CalorieCounterFoodDatabase::~CalorieCounterFoodDatabase()
{
    //FIXME: This should call a deleteData method
    //maybe before the hash or something that acts as the primary
    // which can also be called in the rehashing method
    //and the deleteData method should maybe call a single deleteData method?
    // that will be used in deleteManager?
    //and then hash needs to be changed to not delete anything itself
    
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
	cout << "***************************************************************\n" << endl
    << "     Welcome to the Calorie Counter Food Database!" << endl << endl
    << "      This database allows users to keep track of various foods" << endl
    << "      and their calorie and nutrition information" << endl << endl
	<< "     _________________________________________________________" << endl
	<< "     |                                                       |" << endl 
	<< "     | Authors:                                              |" << endl
    << "     | Shannon Ladymon - Team Leader and Add/Delete          | " << endl
    << "     | Shuti Wang - Search/List and Hash Size                |" << endl
    << "     | Deepika Metkar - Binary Search Tree and File I/O      |" << endl
    << "     | Wendy Martell - Hash Table                            |" << endl
	<< "     |_______________________________________________________|\n\n" << endl
    << "****************************************************************" << endl << endl;
}

//*********************************************************************
// Author - Shannon Ladymon
// goodbye - displays a goodbye message
//*********************************************************************
void CalorieCounterFoodDatabase::goodbye() const
{ 
	cout << "\t  *                                                      *\n";
	cout << "\t* ~~~ Thank you for using Calorie Counter Food Database ~~~ * \n";
	cout << "\t  *\t\t\t Goodbye!                       *\n ";
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
        if (validateInputString(temp))
        {
            Food* foodObj = inputStringToFood(temp);
            insertInDataStructures(foodObj);

        }
        else
        {
            cout << "Unable to insert: " << temp << " because it was not a valid input string\n";
        }

    }
    
    inFile.close();
    
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
    hash->traverseHash(writeFoodItemToFile, outfile);
	cout << "\n";
    cout << "\t\t\t * All items written to file *\n";
    outfile.close();
    return true;
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
    Food* toSearch1 = new Food();
    
    cout <<"\nEnter the following information for the food you would like to add:\n";
    cout << "\tFood Name            : ";
    getline(cin, name);
    
    while (!validateString(name))
    {
        cout << name << " must have a least one character. Please choose a different food name: ";
        getline(cin, name);
    }
    
    name = stringToLower(name);
    
    toSearch1->setName(name);
    
    while (hash->find_Item(*toSearch1))
    {
        cout << name << " already exists. Please choose a different food name: ";
        getline(cin, name);
        while (!validateString(name))
        {
            cout << name << " must have a least one character. Please choose a different food name: ";
            getline(cin, name);
        }
        name = stringToLower(name);
        toSearch1->setName(name);
    }
    
    cout << "\tCategory (fruit, vegetable, grain, protein, dairy): ";
    getline(cin, category);
    
    while (!validateString(category))
    {
        cout << category << " must have a least one character. Please choose a different category: ";
        getline(cin, category);
    }
    category = stringToLower(category);
    
    cout << "\tAmount (in grams/mL) : ";
    getline(cin, amountStr);
    amount = getNum(amountStr);
    
    cout << "\tCalories             : ";
    getline(cin, caloriesStr);
    calories = getNum(caloriesStr);
    
    cout << "\tFiber (in grams)     : ";
    getline(cin, fiberStr);
    fiber = getNum(fiberStr);
    
    cout << "\tSugar (in grams)     : ";
    getline(cin, sugarStr);
    sugar = getNum(sugarStr);
    
    cout << "\tProtein(in grams)    : ";
    getline(cin, proteinStr);
    protein = getNum(proteinStr);
    
    cout << "\tFat (in grams)       : ";
    getline(cin, fatStr);
    fat = getNum(fatStr);
    
    Food* food = new Food(name, category, amount, calories, fiber, sugar, protein, fat);
    delete toSearch1;
    return food;
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
    
    if (hash->get_load_factor() > 75)
	{
		rehashing();
	}
    
    primaryBST->insert(food);
    secondaryBST->insert(food);
    hash->insert(food);
    return true;
}

//*********************************************************************
// Author - Shannon Ladymon
// stringToLower - converts a string to lower case
// @return - the lowercase string
//*********************************************************************
string CalorieCounterFoodDatabase::stringToLower(string str) const
{
    for (int i = 0; i < str.length(); i++)
    {
        str[i] = tolower(str[i]);
    }
    return str;
}



//*********************************************************************
// Author - Shannon Ladymon
// validateInputString - validates that the input string can be used
//          to create a Food*
// @param input - the string to check
// @return - true if the string is in correct format
//*********************************************************************
bool CalorieCounterFoodDatabase::validateInputString(string input) const
{
    int totalSemicolons = 0;
    bool validity = true;
    bool end = false;
    size_t currentPos = 0;
    
    
    while (!end && input.find(";") != string::npos)
    {
        size_t semicolonPos = input.find(";", currentPos + 1);
        if (semicolonPos <= input.length())
        {
            totalSemicolons++;
            string temp = input.substr(currentPos, semicolonPos - currentPos);
        
            validity = validateString(temp);
            
            currentPos = semicolonPos + 1;
        }
        else
        {
            end = true;
        }
    }
    
    //checks that there is at least one character after the last semicolon
    string temp = input.substr(currentPos);
    if (temp.length() < 1)
    {
        validity = false;
    }
    
    //checks that there are 7 semicolons
    if (totalSemicolons != 7)
    {
        validity = false;
    }
    
    
    return validity;
}

//*********************************************************************
// Author - Shannon Ladymon
// validateString - validates that a string is more than one char and
//          not all spaces
// @param input - the string to check
// @return - true if the string is in correct format
//*********************************************************************
bool CalorieCounterFoodDatabase::validateString(string temp) const
{
    bool validity = true;
    
    //checks that there is at least one character between semicolons
    if (temp.length() < 1)
    {
        validity = false;
    }
    
    //checks if the string is only spaces
    bool allSpaces = true;
    for (int i = 0; i < temp.length(); i++)
    {
        if (!isspace(temp[i]))
        {
            allSpaces = false;
        }
    }
    
    if(allSpaces)
    {
        validity = false;
    }
    
    return validity;
}

//*********************************************************************
// Author - Shannon Ladymon
// getNum - given a string, converts it to an int.
// @param input - the string to check
// @return - the int version of the string.  If the string is a char,
//      returns 0. If the string is a negative number, returns 0.
//*********************************************************************
int CalorieCounterFoodDatabase::getNum(string input) const 
{
    int num = atoi(input.c_str());
    if (num < 0)
    {
        num = 0;
    }
    return num;
}

//FIXME: Check for negative numbers
//*********************************************************************
// Author - Deepika Metkar, Shannon Ladymon
// inputStringToFood - converts an input string into a food object
//          NOTE: changes name (primary key) and category (secondary
//          key) to lowercase, but allows both numbers and chars.
//          All other items expect numbers, but will ignore chars.
// @param input - string with the information for a new food item
// @return - true for tree being printed
//*********************************************************************
Food* CalorieCounterFoodDatabase::inputStringToFood(string input) const
{
    string token;
    string fName;
    string fCategory;
    int amount;
    int calories;
    int fiber;
    int sugar;
    int protein;
    int fat;
    
    istringstream ss(input);
    
    getline(ss, token, ';');
    fName = stringToLower(token);
    getline(ss, token, ';');
    fCategory = stringToLower(token);
    getline(ss, token, ';');
    amount = getNum(token);
    getline(ss, token, ';');
    calories = getNum(token);
    getline(ss, token, ';');
    fiber = getNum(token);
    getline(ss, token, ';');
    sugar = getNum(token);
    getline(ss, token, ';');
    protein = getNum(token);
    getline(ss, token, ';');
    fat = getNum(token);
    
    Food* foodObj = new Food(fName, fCategory, amount, calories, fiber, sugar, protein, fat);
    return foodObj;
}


/////////////////////////////////// Menu/Option Manager Functions /////////////////////////////////////

//*********************************************************************
// Author - Shannon Ladymon
// menu - a menu which allows users to enter choices for actions until
//          quitting
//*********************************************************************
void CalorieCounterFoodDatabase::menu(const char* fileName)
{
    welcome();
    string choiceStr;
	char choice = 'A'; //default to enter the while loop

	while (choice != 'Q')
	{
        displayMenu();
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
        case 'P': planMenuMananger();
            break;
		case 'W': writeFile(fileName);
			break;
		case 'G': hash->statistics();
			break;
		case 'H': displayMenu();
			break;
            case 'Q': writeFile(fileName);
                      goodbye();
			break;
		default: cout << choice << " is an invalid option.\n";
		}
	}
}

//*********************************************************************
// Author - Shannon Ladymon
// displayMenu - a listing of the menu options
//*********************************************************************
void CalorieCounterFoodDatabase::displayMenu() const
{
	cout << "\t\t\t__________________________________\n"
        << "\t\t\t| MENU OPTIONS                    |" << endl
		<< "\t\t\t| A - Add new food entry          |" << endl
		<< "\t\t\t| D - Delete food entry           |" << endl
		<< "\t\t\t| S - Search for a food entry     |" << endl
		<< "\t\t\t| L - List food entries           |" << endl
        << "\t\t\t| P - Plan menu                   |" << endl
		<< "\t\t\t| W - Write food entries to file  |" << endl
		<< "\t\t\t| G - Get statistics              |" << endl
		<< "\t\t\t| H - Help (see option list again)|" << endl
		<< "\t\t\t| Q - Quit                        |" << endl
	    << "\t\t\t|_________________________________|" << endl;
}

//*********************************************************************
// Author - Shuti Wang
// displayListMenu - a listing of the list menu options
//*********************************************************************
void CalorieCounterFoodDatabase::displayListMenu() const
{
	cout << "\n\t\t\t\tLIST MENU OPTIONS\n" << endl
		<< "\t\t\tI - Special print, as an indented list" << endl
		<< "\t\t\tU - List unsorted data." << endl
		<< "\t\t\tP - List data sorted by the primary key" << endl
		<< "\t\t\tS - List data sorted by the secondary key" << endl
		<< "\t\t\tQ - Quit the list food entries" << endl;
}

//*********************************************************************
// Author - Shannon Ladymon
// displayInsertMenu - a listing of the insert menu options
//*********************************************************************
void CalorieCounterFoodDatabase::displayInsertMenu() const
{
    cout << "\t\t\t\tINSERT MENU OPTIONS\n" << endl
    << "\t\t\tM - Enter a food manually" << endl
    << "\t\t\tS - Enter an input string" << endl
    << "\t\t\tF - Enter multiple foods via file" << endl
    << "\t\t\tQ - Quit" << endl;
}

//*********************************************************************
// Author - Shannon Ladymon
// displayPlanMenu - a listing of the plan menu options
//*********************************************************************
void CalorieCounterFoodDatabase::displayPlanMenu() const
{
    cout << "\t\t\t\tPLAN MENU OPTIONS\n" << endl
    << "\t\t\tC - Compare two foods' calories" << endl
    << "\t\t\tM - Create a menu for a meal" << endl
    << "\t\t\tQ - Quit" << endl;
}

//*********************************************************************
// Author - Shannon Ladymon
// insertManager - manages any insertion of new Food items into the
//          data structures.  Offers different options for insertion.
//          Will display an error message if unable to insert.
//          NOTE: changes name (primary key) and category (secondary
//          key) to lowercase, but allows both numbers and chars.
//          All other items expect numbers, but will ignore chars.
//*********************************************************************
void CalorieCounterFoodDatabase::insertManager()
{

    string choiceStr;
    string inputString;
    string inputFile;
    Food* toInsert;
    char choice = 'A'; //default to enter the while loop

    while (choice != 'Q')
    {
        displayInsertMenu();
        cout << "\nPlease enter the option of your choice: ";
        getline(cin, choiceStr);
        choice = toupper(choiceStr[0]);
        cout << endl;
        
        switch (choice)
        {
            case'M': toInsert = enterFoodManually();
                if (insertInDataStructures(toInsert))
                {
                    cout << endl << toInsert->getName() << " was successfully inserted" << endl << endl;
                }
                break;
            case'S': cout << "\nEnter the input string: " << endl;
                getline(cin, inputString);
                if (validateInputString(inputString))
                {
                    toInsert = inputStringToFood(inputString);
                    if (insertInDataStructures(toInsert))
                    {
                         cout << endl << toInsert->getName() << " was successfully inserted" << endl << endl;
                    }
                }
                else
                {
                    cout << "Incorrect format for input string.  Cannot add." << endl;
                }
                cout << endl;
                break;
            case'F': cout << "\nEnter the name of the file to read: " << endl;
                getline(cin, inputFile);
                if (readFile(inputFile.c_str()))
                {
                    cout << endl << "File was successfully read and items (except those listed) were inserted" << endl << endl;
                }
                cout << endl;
                break;
            case 'Q': cout << "Returning to the main menu\n";
                cout << endl;
                break;
            default: cout << choice << " is an invalid option.\n";
        }
    }
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
    
    if(!secondaryBST->remove(toDelete, compareBST))
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
	char choice = 'A'; //default to enter the while loop
	
	while (choice != 'Q')
	{
	cout << "\n\t\t\t\tSEARCH MENU OPTIONS \n\n"
		<< "\t\t\tP - Search by Primary key (by name)\n"
		<< "\t\t\tS - Search by Secondary key (by fruit, vegetable, grain, protein, dairy)\n"
	    << "\t\t\tQ - Quit search for a food entry\n"
		<< "\nPlease enter the option of your choice: ";
	getline(cin, choiceStr);
	choice = toupper(choiceStr[0]);

		if (choice != 'P' && choice != 'S' && choice !='Q')
		{
			cout << "Invalid option.  Please enter a valid option.\n";
		}

		Food* toSearch = new Food();
		Food* toReturn = new Food();

		if (choice == 'P')
		{
			cout << "\nEnter the food name(P) to search for: ";
			getline(cin, name);
			name = stringToLower(name);
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
		else if (choice == 'S')
		{
			cout << "\nEnter the food category(S) to search for: ";
			getline(cin, name);
			name = stringToLower(name);
			toSearch->setCategory(name);
			cout << endl;


			if (!secondaryBST->getEntry(toSearch, *toReturn))
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
	if (choice == 'Q')
		cout << "\nReturning to main menu\n";
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
	string choiceStr;
	char choice = 'A';
	
	while (choice != 'Q')
	{
		displayListMenu();
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
		case'P': primaryBST->printTreeAsIndentedList(displayIndentedNode);
			break;
		case'S': secondaryBST->printTreeAsIndentedList(displayIndentedNode);
			break;
		case'Q': cout << "\nReturning to main menu\n";
			break;
		default: cout << choice << " is an invalid option.";
	
		}

	}
    
}

//*********************************************************************
// Author - Shannon Ladymon
// planMenuManager - manages planning menu options.  Users can compare
//          two foods, find foods in a calorie range, or plan a menu.
//*********************************************************************
void CalorieCounterFoodDatabase::planMenuMananger() const
{
    string choiceStr;
    char choice = 'A'; //default to enter the while loop
    
    while (choice != 'Q')
    {
        displayPlanMenu();
        cout << "\nPlease enter the option of your choice: ";
        getline(cin, choiceStr);
        choice = toupper(choiceStr[0]);
        cout << endl;
        
        switch (choice)
        {
            case'C': compareTwoFoods();
                cout << endl;
                break;
            case'M': createMenu();
                cout << endl;
                break;
            case'Q': cout << "Returning to the main menu\n";
                break;
            default: cout << choice << " is an invalid option.\n";
        }
        
    }
}

//*********************************************************************
// Author - Shannon Ladymon
// compareTwoFoods - prompts users for two food items and compares
//          the calories.
//*********************************************************************
void CalorieCounterFoodDatabase::compareTwoFoods() const
{
    string food1, food2;
    Food* toSearch1 = new Food();
    Food* toSearch2 = new Food();
    
    cout << "\tPlease enter the first food to compare: ";
    getline(cin, food1);
    food1 = stringToLower(food1);
    toSearch1->setName(food1);
    
    while (!hash->find_Item(*toSearch1))
    {
        cout << food1 << " was not found in our list.  Please choose a different food: ";
        getline(cin, food1);
        food1 = stringToLower(food1);
        toSearch1->setName(food1);
    }
    
    cout << "\tPlease enter the second food to compare: ";
    getline(cin, food2);
    food2 = stringToLower(food2);
    toSearch2->setName(food2);
    
    while (!hash->find_Item(*toSearch2))
    {
        cout << food2 << " was not found in our list.  Please choose a different food: ";
        getline(cin, food2);
        food2 = stringToLower(food2);
        toSearch2->setName(food2);
    }
    
    cout << "\tComparison:\n";
    cout << "\t\t|| " << food1 << " calories: " << toSearch1->getCalories() << endl;
    cout << "\t\t|| " << food2 << " calories: " << toSearch2->getCalories() << endl;
    
    delete toSearch1;
    delete toSearch2;
}

//*********************************************************************
// Author - Shannon Ladymon
// createMenu - calculates calories based on food choices for a meal
//          menu
//*********************************************************************
void CalorieCounterFoodDatabase::createMenu() const
{
    int sum = 0;
    string food1;
    Food* toSearch1 = new Food();
    
    string choiceStr;
    char choice = 'A'; //default to enter the while loop
    
    
    while (choice != 'Q')
    {
        cout << "\tEnter 'A' to add an item to the menu, 'Q' to quit the menu planner: ";
        getline(cin, choiceStr);
        choice = toupper(choiceStr[0]);
        
        if (choice == 'A')
        {
            cout << "\tAdd Food: ";
            getline(cin, food1);
            food1 = stringToLower(food1);
            toSearch1->setName(food1);
            
            while (!hash->find_Item(*toSearch1))
            {
                cout << food1 << " was not found in our list.  Please choose a different food: ";
                getline(cin, food1);
                food1 = stringToLower(food1);
                toSearch1->setName(food1);
            }
            
            cout <<"\n\t\t|| "<< food1 << " has " << toSearch1->getCalories() << " calories" << endl;
            sum += toSearch1->getCalories();
            cout << "\t\t|| Total menu calories is now: " << sum << endl << endl;
            
        }
        else if (choice == 'Q')
        {
            cout << "\n\tThank you for planning your meal.\n"
				 << "\t\t|| Your meal has " << sum << " calories total" << endl;
        }
        else
        {
            cout << "Invalid choice\n";
        }
    }
    
    delete toSearch1;
}



/////////////////////////////////// Rehash Function /////////////////////////////////////


//*********************************************************************
// Author - Shannon Ladymon, Shuti Wang
// rehashing - dynamically allocates a new hash table that is twice
//          the size and fills it with all the previous Food*
//*********************************************************************
void CalorieCounterFoodDatabase::rehashing()
{
    
    // create new hash with doulbe the size and fill it with the Food*
    int newSize = nextPrime(hash->get_sizeTable() * 2);
    HashTable* newHash = new HashTable(newSize);
    primaryBST->rehashTraverse(visitRehash, newHash);
    
    // set previous hash Food* to null and delete hash
    hash->setAllPointersToNull();
    delete hash;

    // set CalorieCounterFoodDatabase hash to the new hashtable
    hash = newHash;
}

/////////////////////////////////// Stand Alone Functions /////////////////////////////////////

//*********************************************************************
// Author - Deepika Metkar, Shannon Ladymon
// inputFoodToOutputString - converts information from a Food pointer
//          to a string with the data
// @param food - the Food pointer to get the information from
// @return - the string with all information on the food
//*********************************************************************
string inputFoodToOutputString(Food* food)
{
    stringstream amount, calories, fat, fiber, protein, sugar;
    calories << food->getCalories();
    amount << food->getAmount();
    fat << food->getFat();
    fiber << food->getFiber();
    protein << food->getProtein();
    sugar << food->getSugar();
    
    return food->getName() + ";" + food->getCategory() + ";" + amount.str()
    + ";" + calories.str() + ";" + fiber.str() + ";" + sugar.str()
    + ";"+ protein.str() + ";" + fat.str() ;
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
// Author - Shannon Ladymon
// displaySecondaryFoods -  Displays all informationg for a food.
//          Is passed to BST function that displays all foods that
//          match a secondary key.
// @param anItem - reference parameter of Food to be displayed
//*********************************************************************
void displayFood(Food& anItem)
{
    anItem.displayFood();
    cout << endl;
}

//*********************************************************************
// Author - Shannon Ladymon
// visitRehash - Given an Food* and a hash table, will insert the
//          Food* into the hash table
// @param anItem - pointer to Food* to be inserted
// @param newHash - the hash table to insert the Food* into
//*********************************************************************
void visitRehash(Food* anItem, HashTable* newHash)
{
    newHash->insert(anItem);
}

//*********************************************************************
// Author - Shannon Ladymon
// writeFoodItemToFile - Given a food pointer, converts the food info
//          to an output string and writes it to a file
// @param anItem - pointer to Food to be displayed
// @param outfile - the file to write the output string to
//*********************************************************************
void writeFoodItemToFile(Food* anItem, ofstream& outfile)
{
    string outStr = inputFoodToOutputString(anItem);
    outfile << outStr << endl;
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
// Author - Shuti Wang, Deepika Metkar
// nextPrime - given a number, finds the next prime number
// @param inputCounter - the number to start with
// @return - the next prime number
//*********************************************************************
int nextPrime(int inputCounter)
{
    ifstream inFile(PRIME_NUMBERS);
    int primeNumber = inputCounter + 1;
    if (!inFile)
    {
        cout << "Error opening prime number file." << endl;
        return false;
    }
    if (inFile.eof())
    {
        cout << "File is empty." << endl;
        return false;
    }
    while (inFile >> primeNumber)
    {
        if (inputCounter < primeNumber)
        {
            inFile.close();
            return primeNumber;
        }
        
    }
    return primeNumber;
}



