/*
Pgm: ASSGN2-A
Name: Connor Taylor
Purpose: Determines if there are too many students in a classroom in case of a fire.
*/

#include <iostream>

using namespace std;

int main()
{
    //declares room limits
    const int LH312 = 42;
    const int CAS41 = 44;
    const int KH133 = 38;

    int numStudents = 0;
    int room = 0;

    // tells user prompts for each room
    cout << "Enter 1 for Leigh Hall room 312." << endl;
    cout << "Enter 2 for College of Arts and Science room 41." << endl;
    cout << "Enter 3 for Kolbe Hall room 133." << endl;

    // begins loop so user can check rooms as many times as needed
    string again = "Y";
    while (again == "Y" || again == "y")
    {
        // prompts user for which room to check
        cout << "Which room would you like to check? ";
        cin >> room;

        // checks for valid input
        while (room != 1 && room != 2 && room != 3)
        {
            cout << "Invalid number. Please enter 1, 2, or 3: ";
            cin >> room;
        }

        // checks the room wanted for the user and sees if the number of students is legal. While loops check for valid input.
        if (room == 1)
        {
            cout << "Enter the number of students in Leigh Hall room 312: ";
            cin >> numStudents;
            while (numStudents < 0)
            {
                cout << "Invalid number. There cannot be negative students. Please enter a number greater than or equal to 0: ";
                cin >> numStudents;
            }
            if(numStudents <= LH312)
            {
                cout << "It is legal to hold this class. " << LH312 - numStudents << " students can still legally attend." << endl;
            }
            else
            {
                cout << "This class cannot be held as planned." << endl;
            }
        }
        else if (room == 2)
        {
            cout << "Enter the number of students in College of Arts and Science room 41: ";
            cin >> numStudents;
            while (numStudents < 0)
            {
                cout << "Invalid number. There cannot be negative students. Please enter a number greater than or equal to 0: ";
                cin >> numStudents;
            }
            if(numStudents <= CAS41)
            {
                cout << "It is legal to hold this class. " << CAS41 - numStudents << " students can still legally attend." << endl;
            }
            else
            {
                cout << "This class cannot be held as planned." << endl;
            }
        }
        else
        {
            cout << "Enter the number of students in Kolbe Hall room 133: ";
            cin >> numStudents;
            while (numStudents < 0)
            {
                cout << "Invalid number. There cannot be negative students. Please enter a number greater than or equal to 0: ";
                cin >> numStudents;
            }
            if(numStudents <= KH133)
            {
                cout << "It is legal to hold this class. " << KH133 - numStudents << " students can still legally attend." << endl;
            }
            else
            {
                cout << "This class cannot be held as planned." << endl;
            }
        }

        //asks user to run again
        cout << "Would you like to check again? (Y or N): ";
        cin >> again;
    }

    return 0;
}
