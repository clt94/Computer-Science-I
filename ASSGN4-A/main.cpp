/*
Pgm: ASSGN4-A
Name: Connor Taylor
Purpose: Determines an investors first year interest, interest after a specified
amount of years, and the years to reach a goal.
*/

#include <iostream>
#include <iomanip>
#include <limits>
#include <cmath>
using std::cout;
using std::cin;
using std::endl;
using std::ios;

double newBalance(double initialBalance, double interestRate);
/*
This first version of the new balance function computes the
final account balance that will be reached by starting with
an initial balance and adding one year's interest at a given
interest rate (such as 0.05 for 5%). The function works
correctly for any non-negative arguments.
*/

double newBalance(double initialBalance, double interestRate, int n);
/*
This second version of the new balance function computes the
final account balance that will be reached by starting with
an initial balance and adding some n number of years of interest
at a given interest rate (such as 0.05 for 5%). The interest is added
once per year and it is applied to the entire balance.
For example, new_balance(100.00, 0.10, 2) is 121.00 since
the first year received 10.00 interest (10% of 100) and the
second year received 11.00 interest (10% of the 110, which
was the second year's starting balance). The function works
correctly for any non-negative arguments.
Notice n is not an appropriate variable name, but will not be
deducted for this program.
*/

int yearsNeeded(double initialBalance, double interestRate, double goal);
/*
The years needed function computes the number of years needed for
a given starting balance to reach a given goal at a certain rate
of compound interest. The function works correctly for any
positive arguments.
*/

int main()
{
    // initializes and takes user input for the balance before any calculations
    double initialBalance;
    cout << "Enter the initial balance: $";
    cin >> initialBalance;
    // validates input for initial balance
    while(cin.fail() || initialBalance <= 0.0)
    {
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << "Invalid input. Please enter a positive number.\nEnter the initial balance: $";
        cin >> initialBalance;
    }

    // initializes and takes user input for the interest rate
    double interestRate;
    cout << "\nEnter the interest rate: ";
    cin >> interestRate;
    // validates input for interest rate
    while(cin.fail() || interestRate < 0.0 || interestRate > 1.0)
    {
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << "Invalid input. Please enter a number between 0  and 1.\nEnter the interest rate: ";
        cin >> interestRate;
    }

    // initializes and takes user input for years
    int years;
    cout << "\nEnter the years: ";
    cin >> years;
    // validates input for years
    while(cin.fail() || years < 0)
    {
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << "Invalid input. Please enter a number greater than 0.\nEnter the years: ";
        cin >> years;
    }

    // initializes and takes input for the goal
    double goal;
    cout << "\nEnter the goal: $";
    cin >> goal;
    // validates input for goal
    while(cin.fail() || goal < 0.0)
    {
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << "Invalid input. Please enter a number greater than 0.\nEnter the goal: $";
        cin >> goal;
    }

    // sets decimal place to 2
    cout.precision(2);
    cout.setf(ios::fixed, ios::floatfield);

    // outputs the balance after one year, balance after the specified amount of years, and years to meet the goal
    cout << "\nTotal after one year: $" << newBalance(initialBalance, interestRate) << endl;
    cout << "Total after " << years << " years: $" << newBalance(initialBalance, interestRate, years) << endl;
    cout << "Years to meet goal of $" << goal << ": " << yearsNeeded(initialBalance, interestRate, goal) << endl;

    return 0;
}

// Pre: double for balance and double for interest rate
// Computes the balance after one year
// Post: returns double
double newBalance(double initialBalance, double interestRate)
{
    return initialBalance * (1.0 + interestRate);
}

// Pre: double for balance, double for interest rate, and int for years
// Computes the balance after the specified amount of years
// Post: returns double
double newBalance(double initialBalance, double interestRate, int n)
{
    return initialBalance * pow((1.0 + interestRate), n);
}

// Pre: double for balance, double for interest rate, and double for the goal
// Computes how many years it will take to reach the goal
// Post: returns int
int yearsNeeded(double initialBalance, double interestRate, double goal)
{
    int years = 0;
    while(initialBalance <= goal)
    {
        initialBalance = initialBalance * (1.0 + interestRate);
        ++ years;
    }
    return years;
}
