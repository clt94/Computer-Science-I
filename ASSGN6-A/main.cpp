/*
Pgm: ASSGN6-A
Name: Connor Taylor
Purpose: To take a text file and output the farms name, the amount of
items they contributed, and the total revenue they contributed.
*/
// Note: I could not figure out how to properly implement the data for farms with multiple data entries
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using std::cin;
using std::cout;
using std::endl;
using std::ifstream;
using std::string;
using std::ios;

// Prototype for the function to print the data
// Precondition: an ifstream variable, the farm name, the amount of the item,
//               the name of the item, the price of the item, and the overall total
// Postcondition: none
void printFile(ifstream &, string &, int &, string &, float &, float &);

// Prototype for top of output
// Precondition: None
// Postcondition: None
void printHeader();

int main()
{

	string farm = ""; // declares string variables for the farm names and item names
	string item = "";
	int itemCount = 0; // declares an int variable for the amount of the item
	float price = 0; // declares float variables for the price of the individual item
	float total = 0; // and the revenue from all the items sold
	ifstream myFile; // declares input stream for files

    printHeader(); // outputs top of program

	myFile.open("ASSGN6-B.txt"); // opens the file

	if (!myFile.is_open()) // checks to see if the file successfully opened
	{
		cout << "The file failed to open." << endl;
	}
	else
    {
        printFile(myFile, farm, itemCount, item, price, total); // calls function to print file data
    }

    return 0;
}

// Precondition: None
// Outputs the title in a nice format
// Postcondition: none
void printHeader()
{
    cout << std::setfill('=') << std::setw(74) << "\n"; // outputs top of the menu
	cout << "=\t\t\tFarmer's Market Inventory\t\t\t=\n";
    cout << std::setfill('=') << std::setw(74) << "\n";
    cout << std::setfill(' '); // resets fill to spaces
}

// Precondition: an ifstream variable, the farm name, the amount of the item, the name
//                of the item, the price of the item, and the total for all the items
// Outputs all the farm name, the amount of their item(s) contributed and the overall
// total from those items
// Postcondition: none
void printFile(ifstream &myFile, string &farm, int &itemCount, string &item,
               float &price, float &total)
{
    string hold = ""; // string that holds the previous farm name
    int itemTotal = 0; // int for all the items from an individual farms
    float priceTotal = 0; // float for the overall revenue for each farm

    cout.precision(2); // sets floats to two decimal places
    cout.setf(ios::fixed, ios::floatfield);

    getline(myFile, farm, ',');
    do // takes in the farm name until the end of the file, then terminates
    {
        myFile >> itemCount; // inputs from the file for each variable
        myFile >> item;
        myFile >> price;
        myFile >> total;

        if (!(hold == farm)) // checks if farm and hold are not the same
        {
            if (itemTotal > 0 || priceTotal > 0) // checks if their have been previously added totals
            {
                itemCount = itemTotal;
                total = priceTotal;
            }

            cout << std::left << std::setw(25) << farm << itemCount // outputs farm data
                 << " items contributed totaling $" << total << endl;

            itemTotal = 0;
            priceTotal = 0;
        }
        else // adds up farms item counts and total sales
        {
            itemTotal += itemCount;
            priceTotal += total;
        }
        hold = farm;
    } while(!(getline(myFile, farm, ',')).eof());
}
