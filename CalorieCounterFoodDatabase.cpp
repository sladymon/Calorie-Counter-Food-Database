//Author: Shannon Ladymon
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
//const string INPUT_FILE = "/Users/Shannon/Documents/GitHub/Calorie-Counter-Food-Database/foodInput.txt";
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
// displayIndentedNode - Displays student ID and level, indented with
//		tabs dependent on level.  Is passed to BST functions
// @param anItem - Student object to be displayed
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

//Author: Deepika Metkar
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

//Author: Deepika Metkar
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

CalorieCounterFoodDatabase::CalorieCounterFoodDatabase()
{
	this->hashSize = 0;
	this->inputCounter = 0;
	primaryBST = new BinarySearchTree<Food>(compareBST);
	secondaryBST = new BinarySearchTree<Food>(compareBSTSecondary);
}

CalorieCounterFoodDatabase::~CalorieCounterFoodDatabase()
{
    //TODO: Determine what should go here and how/where things should be deleted
}

//Author: Deepika Metkar
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

//Author: Deepika Metkar & Shannon Ladymon
bool CalorieCounterFoodDatabase::readFile(const char* fileName)
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

		Food* foodObj = new Food(fName, fCatagery, amount, calories, fiber, sugar, protein, fat);
		primaryBST->insert(foodObj);
		secondaryBST->insert(foodObj);
        //TODO: add Hash

	}
	return true;
}

//TODO: Write this
bool CalorieCounterFoodDatabase::writeToOutputFile(const char* fileName)
{
	//primaryBST->printTreeInOrder(printToFile);
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



//FIXME: Add options: Enter food individually, enter line of food, enter file of foods
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
	primaryBST->insert(food);
    secondaryBST->insert(food);

	cout << "TESTING: Size: " << primaryBST->size() << endl;


	//TODO: should call insert on hash

}


//FIXME: Fix - how to delete appropriate item from secondaryBST
bool CalorieCounterFoodDatabase::deleteManager()
{
	string name;
	cout << "Enter food name to be deleted: ";
	getline(cin, name);

    Food* toSearch = new Food();
    Food* toDelete = new Food();
	toSearch->setName(name);
    
    //TODO: search for item first, and get the category so can delete in secondary
    //for now, use primaryBST, but change to hash in the future
    
    
    if(!primaryBST->getEntry(toSearch, *toDelete))
    {
        cout << "Unable to find " << name << ", so it cannot be removed" << endl;
        return false;
    }

	if (!primaryBST->remove(toDelete))
    {
        cout << "Unable to remove " << name << endl;
        return false;
    }
    
    if(!secondaryBST->remove(toDelete, compareBST))  //FIXME: Why doesn't this crash when trying to delete actual item again?
    {
        cout << "Unable to remove " << name << endl;
        return false;
    }
    
    //TODO: should call delete on hash
    
    cout << name << " was successfully deleted" << endl;

	cout << "TESTING: Size: " << primaryBST->size() << endl;
    
    delete toSearch;
    delete toDelete;
    
    return true;
}

//FIXME: Search by category works incorreclty
//Shuti
void CalorieCounterFoodDatabase::searchManager() const
{
	string name;
	string searchType;
	
	cout << "Do you want to search with name or category. Enter N for name and C for category : ";
	getline(cin, searchType);
	Food* toSearch = new Food();
	Food* toReturn = new Food();
	if (searchType == "N" || searchType == "n")
	{
		cout << "Enter the food name to search for: ";
		getline(cin, name);
		toSearch->setName(name);
		if(!primaryBST->getEntry(toSearch, *toReturn))
        {
            cout << "Could not find " << name << endl;
        }
        else
        {
            toReturn->displayFood();
        }
	}
	else if (searchType == "C" || searchType == "c") //FIXME: How should this work? What should it print?  Not a single item, but all items
	{
		cout << "Enter the food category to search for: ";
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
    
    //FIXME: Make this a loop for if the entered choice is not valid


    delete toSearch;
    delete toReturn;

}



//Shuti
void CalorieCounterFoodDatabase::listManager() const
{
	primaryBST->printTreeAsIndentedList(displayIndentedNode);
    secondaryBST->printTreeAsIndentedList(displayIndentedNode);

	//TODO: add in rest of list manager
}

//Shuti
int CalorieCounterFoodDatabase::determineHashSize(int inputCounter)
{
	cout << "Determine Hash Size called" << endl;
	return 0;
}

//TODO: Write this
void CalorieCounterFoodDatabase::rehashing()
{
	cout << "Rehashing called" << endl;
}
