//Author: Shannon Ladymon
#include "Food.h"
#include <string>
#include <iostream>

using namespace std;

//*********************************************************************
// Overloaded Constructor
//*********************************************************************
Food::Food(string name, string category, int amount, int calories, int fiber, int sugar, int protein, int fat)
{
	this->name = name;
	this->category = category;
	this->amount = amount;
	this->calories = calories;
	this->fiber = fiber;
	this->sugar = sugar;
	this->protein = protein;
	this->fat = fat;
}

//*********************************************************************
// displayFood - displays all member data for Food object
//*********************************************************************

void Food::displayFood()
{
	cout << "Food: " << this->name << endl
		<< "Category: " << this->category << endl
		<< "Amount: " << this->amount << " grams/mL" << endl
		<< "Calories: " << this->calories << endl
		<< "Fiber: " << this->fiber << " grams" << endl
		<< "Sugar: " << this->sugar << " grams" << endl
		<< "Protein: " << this->protein << " grams" << endl
		<< "Fat: " << this->fat << " grams" << endl;
}

