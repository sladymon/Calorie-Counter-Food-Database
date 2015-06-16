#include <iostream>
#include <fstream>
#include "CalorieCounterFoodDatabase.h"

using namespace std;

//<<<<<<< Updated upstream
//Shannon's files
//const string INPUT_FILE = "/Users/Shannon/Documents/GitHub/Calorie-Counter-Food-Database/foodInput.txt";
//const string OUTPUT_FILE = "/Users/Shannon/Documents/GitHub/Calorie-Counter-Food-Database/foodOutput.txt";

//Wendy's files
//const string INPUT_FILE = "/Users/wendymartell/Dropbox/GITHUB/Food-Calorie-Counter-22C-2015/Calorie-Counter-Food-Database/foodInput.txt";
//const string INPUT_FILE = "/Users/wendymartell/Dropbox/GITHUB/Food-Calorie-Counter-22C-2015/Calorie-Counter-Food-Database/foodOutput.txt";

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



int nextPrime(int inputCounter);
int determineHashSize(const char* fileName);
int main()
{
	CalorieCounterFoodDatabase* a = new CalorieCounterFoodDatabase(determineHashSize(INPUT_FILE.c_str()));
	a->readFile(INPUT_FILE.c_str());
	a->menu();
	return 0;
}

//Shuti
int determineHashSize(const char* fileName)
{
	int inputCounter = 0;
	ifstream inFile("foodInput.txt");
	string temp;

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

	while (getline(inFile, temp))
	{
		inputCounter++;
	}
	inFile.clear();
	inFile.seekg(0, inFile.beg);


	return nextPrime(inputCounter * 2);
}
// 
int nextPrime(int inputCounter)
{
	ifstream inFile("primeNumbers.txt");
	int primeNumber = 0;
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

}