//*********************************************************************
//                              FOOD CLASS
//
// Author: Shannon Ladymon
// Description: Food is a class that contains information about a food
//              item, including name (primary, unique key), category
//              (secondary, non-unique key), and information about the
//              calories and nutrition.
//
//*********************************************************************

#include "Food.h"
#include <string>
#include <iostream>

using namespace std;

//*********************************************************************
// Author - Shannon Ladymon
// Overloaded Constructor - takes all data for a food to construct it
// @param name - a string that is the unique key for the food (its name)
// @param cateogry - a string that is the secondary, non-unique key
//          (type of food - fruit, vegetable, grain, protein, dairy)
// @param amount - int for amount of food in grams/mL
// @param fiber - int for fiber in grams per specified amount
// @param sugar - int for sugar in grams per specified amount
// @param protein - int for protein in grams per specified amount
// @param fat - int for fat in grams per specified amount
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
// Author: Shannon Ladymon
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

