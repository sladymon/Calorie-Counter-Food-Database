#include <iostream>
#include <fstream>
#include "CalorieCounterFoodDatabase.h"

using namespace std;

//Shannon's files
//const string INPUT_FILE = "/Users/Shannon/Documents/GitHub/Calorie-Counter-Food-Database/foodInput.txt";
//const string OUTPUT_FILE = "/Users/Shannon/Documents/GitHub/Calorie-Counter-Food-Database/foodOutput.txt";
//const string PRIME_NUMBERS = "/Users/Shannon/Documents/GitHub/Calorie-Counter-Food-Database/primeNumbers.txt";

//Wendy's files
//const string INPUT_FILE = "/Users/wendymartell/Dropbox/GITHUB/Food-Calorie-Counter-22C-2015/Calorie-Counter-Food-Database/foodInput.txt";
//const string INPUT_FILE = "/Users/wendymartell/Dropbox/GITHUB/Food-Calorie-Counter-22C-2015/Calorie-Counter-Food-Database/foodOutput.txt";
//const string PRIME_NUMBERS = "/Users/wendymartell/Dropbox/GITHUB/Food-Calorie-Counter-22C-2015/Calorie-Counter-Food-Database/primeNumbers.txt";

//Shuti's files
//const string INPUT_FILE = "foodInput.txt";
//const string OUTPUT_FILE = "foodOutput.txt";
//const string PRIME_NUMBERS = "primeNumbers.txt";

//Deepika's files
//const string INPUT_FILE = "D:\\foodInput.txt";
//const string OUTPUT_FILE = "D:\\foodOutput.txt";
//const string OUTPUT_FILE = "D:\\primeNumbers.txt";


int determineHashSize(const char* fileName, const char* primeFile);
int nextPrime(int inputCounter, const char* primeFile);

int main()
{
	CalorieCounterFoodDatabase* a = new CalorieCounterFoodDatabase(determineHashSize(INPUT_FILE.c_str(), PRIME_NUMBERS.c_str()));
	a->readFile(INPUT_FILE.c_str());
	a->menu();
	return 0;
}

//Shuti
int determineHashSize(const char* fileName, const char* primeFile)
{
	int inputCounter = 0;
	ifstream inFile;
	string temp;

	inFile.open(fileName);
	if (!inFile)
	{
		cout << "Error opening " << fileName << "!\n";
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


	return nextPrime(inputCounter * 2, primeFile);
}

//
int nextPrime(int inputCounter, const char* fileName)
{
	ifstream inFile(fileName);
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