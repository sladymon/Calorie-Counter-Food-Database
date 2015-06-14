//Author: Shannon Ladymon

#ifndef CALORIECOUNTERFOODDATABASE_H_
#define CALORIECOUNTERFOODDATABASE_H_

#include "BinarySearchTree.h"
#include "Food.h"
//#include "Hash.h"
#include <iostream>
#include <cctype>

using namespace std;

class CalorieCounterFoodDatabase
{
private:
//	HashTable<Food>* hash;
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
//	HashTable<Food>* getHash() {return this->hash;}
	BinarySearchTree<Food>* getPrimaryBST() {return this->primaryBST;}
	BinarySearchTree<Food>* getSecondaryBST() {return this->secondaryBST;}
	int getHashSize() {return this->hashSize;}
	int getInputCounter() {return this->inputCounter;}

	//mutators
//	void setHash(HashTable<Food>* hash) {this->hash = hash;}
	void setPrimaryBST(BinarySearchTree<Food>* primaryBST) {this->primaryBST = primaryBST;}
	void setSecondaryBST(BinarySearchTree<Food>* secondaryBST) {this->secondaryBST = secondaryBST;}
	void setHashSize(int hashSize) {this->hashSize = hashSize;}
	void setInputCounter(int inputCounter) {this->inputCounter = inputCounter;}

	//read/write file and initilize hash & BSTs
	bool readFile(const char* fileName);
	bool writeToOutputFile(const char* fileName);
    string inputFoodToOutputString(Food* food);

	//menu and option manager functions
	void menu();
	void displayMenu() const;
	void insertManager();
	bool deleteManager();
	void searchManager() const;
	void listManager() const;

	//hash functions
	int determineHashSize(int inputCounter);//FIXME: inputCounter is not needed if in class, correct?
	void rehashing();

};



#endif /* CALORIECOUNTERFOODDATABASE_H_ */
