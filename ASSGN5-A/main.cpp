/*
Pgm: ASSGN5-A
Name: Connor Taylor
Purpose: Takes in a user input and determines if it is prime or not
*/

#include <iostream>
#include <limits>

using std::cout;
using std::cin;
using std::endl;

bool isPrime(int); // predefines function to determine prime number

int main()
{
    char again = 'Y';
    bool valid;
    int num;
    while(again == 'y' || again == 'Y') // sentinel controlled loop requiring y or Y to repeat program
    {
        do // validates input for if the input is a number and greater than 0
        {
            num = 0;
            valid = false;
            cout << "Enter a number: ";
            cin >> num;
            if(cin.fail() || num <= 0)
            {
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');;
                cout << "Invalid input. Enter a positive number." << endl;
                valid = true;
            }
        }while(valid);

        cout << "Prime numbers until " << num << ": "; // prints all prime numbers prior to user input
        for (int i = 1; i < num; ++ i)
        {
            if(isPrime(i))
            {
                cout << i << " ";
            }
        }
        cout << endl;

        if(isPrime(num)) // outputs if the number is prime or not
        {
            cout << num << " is prime." << endl;
        }
        else
        {
            cout << num << " is not prime." << endl;
        }

        cout << "Again? (Y for yes) "; // prompts user if they want to run the program again
        cin >> again;
        cout << endl;
    }

    return 0;
}

// Precondition: any positive int
// Uses a for loop to check if the number is in fact prime
// Postcondition: returns true if the number is prime and false otherwise
bool isPrime(int num)
{
    for(int i = 2; i < num; ++ i) // checks all numbers except one, until num
    {
        if(num % i == 0) // checks for divisibility, if divisible the number is not prime
        {
            return false;
        }
    }
    return true;
}
