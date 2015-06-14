//Author: Shannon Ladymon
#ifndef _FOOD
#define _FOOD

#include <string>
#include <iostream>

using namespace std;

class Food
{
private:
	string name; //unique key
	string category; //secondary key (type of food - fruit, vegetable, grain, protein, dairy)
	int amount; //in grams/mL
	int calories;
	int fiber; //in grams
	int sugar; //in grams
	int protein; //in grams
	int fat; //in grams
public:
	//constructors
	Food(): name(""), category(""), amount(0), calories(0),
			fiber(0), sugar(0), protein(0), fat(0) {}
	Food(string name, string category, int amount,
			int calories, int fiber, int sugar, int protein, int fat);
    
	//accessors
	string getName() const {return this->name;}
	string getCategory() const {return this->category;}
	int getAmount() const {return this->amount;}
	int getCalories() const {return this->calories;}
	int getFiber() const {return this->fiber;}
	int getSugar() const {return this->sugar;}
	int getProtein() const {return this->protein;}
	int getFat() const {return this->fat;}

	//mutators
	void setName(string name) {this->name = name;}
	void setCategory(string category) {this->category = category;}
	void setAmount(int amount) {this->amount = amount;}
	void setCalories(int calories) {this->calories = calories;}
	void setFiber(int fiber) {this->fiber = fiber;}
	void setSugar(int sugar) {this->sugar = sugar;}
	void setProtein(int protein) {this->protein = protein;}
	void setFat(int fat) {this->fat = fat;}

	//display
	void displayFood();

};

#endif
