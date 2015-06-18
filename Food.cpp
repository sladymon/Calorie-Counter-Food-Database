//*********************************************************************
//                              FOOD CLASS
//
// Author: Shannon Ladymon
// Class: 22C Spring2015
//
// Description: Food is a class that contains information about a food
//              item, including name (primary, unique key), category
//              (secondary, non-unique key), and information about the
//              calories and nutrition.
//
// Purpose: This is our data class that the database is using.
//
//*********************************************************************

#include "Food.h"
#include <string>
#include <iomanip>
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
	cout<< "\tFood    : " << this->name << endl
		<< "\tCategory: " << setw(3) << this->category << endl
		<< "\tAmount  : " << setw(3) << this->amount << " g/mL" << endl
		<< "\tCalories: " << setw(3) <<this->calories << endl
		<< "\tFiber   : " << setw(3) << this->fiber << " g" << endl
		<< "\tSugar   : " << setw(3) << this->sugar << " g" << endl
		<< "\tProtein : " << setw(3) << this->protein << " g" << endl
		<< "\tFat     : " << setw(3) << this->fat << " g" << endl;
}

