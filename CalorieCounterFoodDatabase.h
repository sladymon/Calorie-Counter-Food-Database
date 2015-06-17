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

#ifndef CALORIECOUNTERFOODDATABASE_H_
#define CALORIECOUNTERFOODDATABASE_H_

#include "BinarySearchTree.h"
#include "Food.h"
#include "HashTable.h"
#include <iostream>
#include <cctype>

using namespace std;

class CalorieCounterFoodDatabase
{
private:
	HashTable* hash;
	BinarySearchTree<Food>* primaryBST;
	BinarySearchTree<Food>* secondaryBST;
	int hashSize;
	int inputCounter;

public:
	//constructor
    CalorieCounterFoodDatabase();
    
    //overloaded constructor that takes hashSize as a parameter
    CalorieCounterFoodDatabase(int hashSize);

    //destructor
	~CalorieCounterFoodDatabase();

	//accessors
	HashTable* getHash() {return this->hash;}
	BinarySearchTree<Food>* getPrimaryBST() {return this->primaryBST;}
	BinarySearchTree<Food>* getSecondaryBST() {return this->secondaryBST;}
	int getHashSize() {return this->hashSize;}
	int getInputCounter() {return this->inputCounter;}

	//mutators
	void setHash(HashTable* hash) {this->hash = hash;}
	void setPrimaryBST(BinarySearchTree<Food>* primaryBST) {this->primaryBST = primaryBST;}
	void setSecondaryBST(BinarySearchTree<Food>* secondaryBST) {this->secondaryBST = secondaryBST;}
	void setHashSize(int hashSize) {this->hashSize = hashSize;}
	void setInputCounter(int inputCounter) {this->inputCounter = inputCounter;}

    //welcome message
    void welcome() const;
    
    //goodbye message
    void goodbye() const;
    
	//read input file and insert items into data structures
	bool readFile(const char* fileName);
    
    //write output file with all items from data structures
	bool writeFile(const char* fileName);
    
    //insert a food pointer into all data structures
    bool insertInDataStructures(Food* food);
    
    //convert an input string to a food pointer
    
    
    //enter information for a food item manually
    Food* enterFoodManually() const;
    
    //input string manipulation
    string stringToLower(string str) const;
    bool validateInputString(string input);
    Food* inputStringToFood(string input) const;

	//menus and option manager functions
	void menu(const char* fileName);
	void displayMenu() const;
	void displayListMenu() const;
    void displayInsertMenu() const;
    void displayPlanMenu() const;
	void insertManager();
	bool deleteManager();
	void searchManager() const;
	void listManager() const;
    void planMenuMananger() const;
    
    void compareTwoFoods() const;
    void createMenu() const;

	//hash functions
	void rehashing();
    void traverseData();
};

#endif /* CALORIECOUNTERFOODDATABASE_H_ */


/////////////////// Stand-Alone Functions /////////////////////

// converts Food pointer to an output string
string inputFoodToOutputString(Food* food);

// display functions to pass as parameters to other class functions
void displayIndentedNode(Food* anItem, int level);
void displayFood(Food& anItem);
void visitRehash(Food* anItem, HashTable* newHash);
void writeFoodItemToFile(Food* anItem, ofstream& outfile);

// compare functions to pass as parameters for BST constructors
int compareBST(Food* food1, Food* food2);
int compareBSTSecondary(Food* food1, Food* food2);

// finds next prime number
int nextPrime(int inputCounter);
