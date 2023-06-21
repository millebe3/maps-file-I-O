//***********************************************************************************************
// Title: main.cpp
// Author: Ben Miller
// Date: 6/14/2023
// Purpose: Program that reads in text items (single word on a line) from a file and 
// counts how many times each item is listed in the file.  Each item and its numerical 
// occurance is output to the user and written to another file.  User is presented with 
// choices for output.
//***********************************************************************************************


#include <iostream>
#include <map>
#include <string>
#include <fstream>
using namespace std;


//==============================================================================
// Class Mapquest: contains two print methods (printMap1 and printMap2) that
// output the different types of maps to the user.  
//==============================================================================
class Mapquest
{

public:
	void printMap1(map<string, int> map1);
	void printMap2(map<string, string>);


private:
	string key = "";
	string stringValue = "";
	int intValue = 0;

};
//==============================================================================



//--------printMap1 and printMap2 definitions-----------------------------------
void Mapquest::printMap1(map<string, int> map1)
{
	for (auto l : map1)    // iterate through map, ouptutting the key then value
		cout << l.first << " " << l.second << endl;
}

void Mapquest::printMap2(map<string, string> map2)
{
	for (auto m : map2)    // iterate through map, ouptutting the key then value
		cout << m.first << " " << m.second << endl;
}
//------------------------------------------------------------------------------



//-----------------------displayMenu method definition--------------------------
void displayMenu()	// outputs the menu to the user.
{
	cout << "------------------------------------------------------" << endl;
	cout << "                     PROGRAM MENU" << endl;
	cout << "======================================================" << endl;
	cout << "1. Enter 1 to search for an item." << endl;
	cout << "2. Enter 2 to output the item list (with numbers)" << endl;
	cout << "3. Enter 3 to output the item list (with asterisks)" << endl;
	cout << "4. Enter 4 to quit." << endl << endl;
}
//------------------------------------------------------------------------------



//===============================================================================
// main method.  Responsible for openingn and reading from input file, opening 
// and writing to output file.  Creates two different maps and sends them to
// Mapquest printMap1 and printMap2 when they're full.  Fills maps with produce
// items and their associated values.  The associated values in produceMap are 
// integers that represent the number of times each item was listed in the input
// file.  The associated values in produceMapAst are asterisks (*); one each for
// how many times that item was listed in the file.  Has switch statement for 
// the 4 options listed in the "PROGRAM MENU".
// ==============================================================================
int main()
{
	int userChoice = 0;
	map<string, int> produceMap;
	map<string, string> produceMapAst;
	string produceItem = "";
	ifstream inFS;
	ofstream outFS;
	string inFileName = "CS210_Project_Three_Input_File.txt";
	string outFileName = "frequency.dat";
	int failCount = 0;
	int astFailCount = 0;
	string searchItem;
	Mapquest mapInt;
	Mapquest mapString;
	


	inFS.open(inFileName);							// try to open the input file.

	if (!inFS.is_open())							// error message to user if could not open input file
	{
		cout << "Could not open file: " << inFileName << endl;
		return 1;
	}

	produceMap.clear();								// ensure map is clear.
	produceMapAst.clear();							// ensure map is clear.


	while (!inFS.eof())								// Read until end of the file.
	{
		inFS >> produceItem;						// Attempt to read in a produceItem from the file.
		
		produceMap.emplace(produceItem, 0);			// Add first produceItem (key) to produceMap.  
		produceMapAst.emplace(produceItem, "");		// Add first produceItem (key) to procuceMapAst.

		if (produceMap.count(produceItem) == 1)		// if produceItem is already in ProduceMap (key)
		{
			produceMap.at(produceItem) += 1;		// add 1 to the int contained in produceMap's value that is assoc
													// with the key produceItem.
		}
		else
		{
			++failCount;							// for possible debugging.
		}

		if (produceMapAst.count(produceItem) == 1)	// if produceItem is already in ProduceMapAst (key)
		{
			produceMapAst.at(produceItem) += "*";	// add a "*" onto the string of asterisks in produceMapAst's value
													// that is assoc with the key produceItem.
		}
		else
		{
			++astFailCount;							// for possible debugging.
		}

		if (inFS.fail())							// No produce item to read
		{
			cout << "No produce item to input." << endl;
			cout << produceItem << endl;
		}


	}

	inFS.close();									// close tht input file.

	outFS.open(outFileName);						// open the output file.

	if (!outFS.is_open())							// error message to user if cannot open output file.
	{
		cout << "Could not open file " << outFileName << endl;
		return 1;
	}

	for (auto i : produceMap)						// send produceMap to the output file.
		outFS << i.first << " " << i.second << endl;

	outFS.close();									// close output file.


	while (userChoice != 4)							// display menu until user chooses option 4.
	{
		displayMenu();
		cin >> userChoice;							// get userChoice input 

		
		switch (userChoice)							// switch on userChoice
		{
		case 1:										// menu option 1 (case 1) displays the value in ProduceMap associated
													// with corresponding key value (searchItem).
			cout << "Enter item to search for: ";
			cin >> searchItem;
			if (produceMap.count(searchItem) == 1)
			{
				cout << searchItem << ": " << produceMap.at(searchItem) << endl;
			}
			else
			{
				cout << "Item wasn't purchased." << endl;
			}
			
			break;

		case 2:										// menu option 2 (case 2) outputs the map ProduceMap to the user.
			cout << "Output item list with numbers." << endl;
			mapInt.printMap1(produceMap);
			break;
		
		case 3:										// menu option 3 (case 3) outputs the map ProduceMapAst to the user.
			cout << "Output item list with asterisks." << endl;
			mapString.printMap2(produceMapAst);
			break;

		case 4:										// menu option 4 (case 4) quits the program.
			cout << "Quit." << endl;
			break;

		default:
			cout << "Invalid choice, choose again." << endl << endl;
			break;
		}

	}


	return 0;
}
//=======================================================================================
