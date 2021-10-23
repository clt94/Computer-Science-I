/*
Pgm: ASSGN3-A
Name: Connor Taylor
Purpose: Prints a square made of X's to specified size of the user
*/

#include <iostream>

using namespace std;

int main()
{
    int num = 0;

    do  // checks user input to make sure it's valid
    {
        cout << "Please enter a number greater than 0 and less than 75: ";
        cin >> num; // prompts user and takes in input
    } while (num < 0 && num > 75);  // parameters of the user input

    for (int i = 0; i < num; ++ i)  // column
    {
        for  (int j = 0; j < num; ++ j) // row
        {
            cout << "X";
        }
        cout << endl;   // goes to next column
    }
    return 0;
}
