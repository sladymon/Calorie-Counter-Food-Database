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
	//FIXME: Temporary constructor for testing without hash:
	CalorieCounterFoodDatabase();

	//CalorieCounterFoodDatabase(); //TODO: consider making overloaded constructor
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

	//read/write file and initilize hash & BSTs
	bool readFile(const char* fileName);
	bool writeToOutputFile(const char* fileName);
    string inputFoodToOutputString(Food* food);
    Food* inputStringToFood(string input);

	//menu and option manager functions
	void menu();
	void displayMenu() const;
	void displayListMenu() const;
	void insertManager();
	bool deleteManager();
	void searchManager() const;
	void listManager() const;

	//hash functions
	int determineHashSize(const char* fileName);//FIXME: inputCounter is not needed if in class, correct?
	bool isPrime(int inputCounter);
	int nextPrime(int size);
	void rehashing();
	void display_Indented_Hash() const;
	void display_Unsorted_Hash() const;
	void display_Primary_key() const;
	void display_Secondary_key() const;

};



#endif /* CALORIECOUNTERFOODDATABASE_H_ */
