/*
COPYRIGHT (C) 2018 Connor Taylor (clt94) All rights reserved
MyFitness Project Part 2
Author: Connor Taylor
        clt94@zips.uakron.edu
Purpose: Have a program where the user enters in the workout
they did, their weight, and the amount of time they
exercised. Then output the calories they burned. Store all info
into a log. Generates a unique user ID for each entry, and holds
a count as well. Requires a password.
*/
#include <iostream>
#include <iomanip>
#include <limits>
#include <cstdlib>
#include <ctime>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>

using std::cin;
using std::cout;
using std::endl;
using std::setfill;
using std::setw;
using std::numeric_limits;
using std::streamsize;
using std::ios;
using std::fstream;
using std::string;

// Precondition: None
// Postcondition: None
void menu();

// Precondition: Reference int, int, and int
// Postcondition: None
void validate(int &, int, int);

// Precondition: Reference int
// Postcondition: None
void getWorkout(int &);

// Precondition: Reference int
// Postcondition: None
void getWeight(int &);

// Precondition: Reference int, and reference int
// Postcondition: None
void getMinutes(int &, int &);

// Precondition: 3 references ints, a reference float and a referenced string
// Postcondition: None
void getCalAndAct(int &, int &, int &, float &, string &);

// Precondition: Reference float and a reference string
// Postcondition: None
void getIntensity(float &, string &);

// Precondition: None
// PostCondition: None
void pause();

// Precondition: Reference int, and int
// Postcondition: None
void createUserID(int &, int);

// Precondition: Reference int
// Postcondition: None
static void hits(int &);

// Precondition: Reference fstream, 2 reference strings, 2 reference ints, a reference float,
// a reference string, and a reference char*
// Postcondition: None
void writeToLog(fstream &, int &, string &, int &, int &, float &, string &, char* &);

// Precondition: Reference char*
// Postcondition: None
void getTime(char* &);

// Precondition: Reference fstream, 2 reference strings, 2 reference ints, a reference float,
// and 2 reference strings
// Postcondition: None
void printLog(fstream &, int &, string &, int &, int &, float &, string &, string &);

// Precondition: None
// Postcondition: True or false
bool password();

// declares constants for MET values for each exercise
const float BIKING = 8.0;
const float RUNNING = 10.0;
const float LIFTING = 3.0;
const float YOGA = 2.5;

int main()
{
    int workout;
    int weight;
    int minutes;
    float calories;
    static int numHits = 0;
    fstream transactionLog;
    string activity;
    string intensity;
    char* timeOf;
    string time;
    int userID;

    // opens file to log info as input and also output. Set in append mode
    transactionLog.open("tranlog.txt", std::ios::in | std::ios::out | std::ios::app);
    if(!transactionLog.is_open()) // checks if it is open and ends the program if it fails
    {
        cout << "tranlog.txt failed to open.";
        return 0;
    }
    // sets random for random user ID generator

    // keeps program in infinite loop until proper input
    while(true)
    {
        // outputs main menu and options for workouts
        menu();
        // outputs an unique user ID
        createUserID(userID, numHits);
        // outputs a times menu has been used
        hits(numHits);
        // prompts user to enter their workout
        getWorkout(workout);

        if (workout != 6 && workout != 5) // normal entry if not a 5 or 6
        {
            // prompts user to enter their weight
            getWeight(weight);
            // prompts user to enter the minutes they exercised
            getMinutes(minutes, workout);
            // calculates and outputs the calories burned according to each exercise
            getCalAndAct(workout, weight, minutes, calories, activity);
            // outputs the intensity
            getIntensity(calories, intensity);
            // gets and outputs time and date
            getTime(timeOf);
            // stores data to log
            writeToLog(transactionLog, userID, activity, minutes, weight, calories, intensity, timeOf);
        }
        else if(workout == 5) // goes to output log
        {
            if (password()) // checks if the user knows the password
            {
                // outputs all info from tranlog.txt
                printLog(transactionLog, userID, activity, minutes, weight, calories, intensity, time);
            }
            else // ends program if the password is incorrect
            {
                return 0;
            }
        }
        else // exits the program
        {
            return 0;
        }

        // Pauses the program
        pause();
    }

    // closes file
    transactionLog.close();

    return 0;
}

// Precondition: None
// Outputs the menu.
// Postcondition: None
void menu()
{
    cout << " " << setfill('_') << setw(72) << " " << endl;
    cout << "|" << setfill('-') << setw(72) << "|" << endl;
    cout << "|\t\t    Welcome to Connor's Fitness Center\t\t\t|" << endl;
    cout << "|\t\t\t     Activity System\t\t\t\t|" << endl;
    cout << "|" << setfill('_') << setw(72) << "|" << endl;
    cout << "|\t\t\t\tMain Menu\t\t\t\t|" << endl;
    cout << "|\t\t\t 1) Stationary Bike\t\t\t\t|" << endl;
    cout << "|\t\t\t 2) Treadmill\t\t\t\t\t|" << endl;
    cout << "|\t\t\t 3) Weight Lifting\t\t\t\t|" << endl;
    cout << "|\t\t\t 4) Hatha Yoga\t\t\t\t\t|" << endl;
    cout << "|\t\t\t 5) Print Transaction Log\t\t\t|" << endl;
    cout << "|\t\t\t 6) Quit\t\t\t\t\t|" << endl;
    cout << "|" << setfill('_') << setw(72) << "|" << endl;
}

// Precondition: reference int for user input, int lower bound, and an int upper bound
// Checks for validity of the input from the user and if it falls in the bounds.
// Postcondition: None
void validate(int &input, int low, int high)
{
    while(cin.fail() || input < low || input > high) // checks for valid values then checks bounds
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Please enter a number from " << low << " to " << high << ": "; // reprompts user
        cin >> input;
    }
}

// Precondition: an int reference variable
// Takes in input from the user for workout and validates it.
// Postcondition: None
void getWorkout(int &workout)
{
    cout << "\nEnter the workout that you wish to track, print log, or quit to exit: ";
    cin >> workout;
    validate(workout, 1, 6); // validates input from 1 to 6
}

// Precondition: an int reference variable
// Takes in input from the user for weight and validates it.
// Postcondition: None
void getWeight(int &weight)
{
    cout << "\nEnter your weight: ";
    cin >> weight;
    validate(weight, 1, 999); // validates input from 1 to 999
}

// Precondition: two int reference variable
// Takes in input from the user for minutes and validates it based on their workout choice.
// Postcondition: None
void getMinutes(int &minutes, int &workout)
{
    cout << "\nEnter the number of minutes: ";
    cin >> minutes;
    switch (workout)
    {
        // biking
        case 1 : workout = 1;
            validate(minutes, 30, 60); // validates input from 30 to 60
            break;
        // running
        case 2 : workout = 2;
            validate(minutes, 30, 60); // validates input from 30 to 60
            break;
        // lifting
        case 3 : workout = 3;
            validate(minutes, 15, 30); // validates input from 15 to 30
            break;
        // yoga
        case 4 : workout = 4;
            validate(minutes, 60, 90); // validates input from 60 to 90
            break;
    }
}

// Precondition: A reference int for the user workout, weight, and minutes,
// a reference float for calories, and then a reference string for activity
// Calculates and outputs the calories burned based off of the user's input.
// Also sets the string to activity to what the user entered
// Postcondition: None
void getCalAndAct(int &workout, int &weight, int &minutes, float &calories, string &activity)
{
    // set decimal format to 1
    cout.setf(ios::fixed);
    cout.setf(ios::showpoint);
    cout.precision(1);
    switch (workout)
    {
        // biking
        case 1 : workout = 1;
            calories = static_cast<float>(minutes) / 60 * BIKING * weight / 2.2; // calculates calories
            cout << "\nYour total calories for the stationary bike was: " << calories << endl;
            activity = "Stationary Bike";
            break;
        // running
        case 2 : workout = 2;
            calories = static_cast<float>(minutes) / 60 * RUNNING * weight / 2.2; // calculates calories
            cout << "\nYour total calories for the treadmill was: " << calories << endl;
            activity = "Treadmill";
            break;
        // lifting
        case 3 : workout = 3;
            calories = static_cast<float>(minutes) / 60 * LIFTING * weight / 2.2; // calculates calories
            cout << "\nYour total calories for weight lifting was: " << calories << endl;
            activity = "Weight Lifting";
            break;
        // yoga
        case 4 : workout = 4;
            calories = static_cast<float>(minutes) / 60 * YOGA * weight / 2.2; // calculates calories
            cout << "\nYour total calories for Hatha yoga was: " << calories << endl;
            activity = "Hatha Yoga";
            break;
    }
}

// Precondition: A referenced float variable calories and reference string intensity
// Outputs the intensity of the workout based off of the calories burned. Also
// sets the intensity of the workout
// Postcondition: None
void getIntensity(float &calories, string &intensity)
{
    if (calories <= 200)
    {
        cout << "\nLight-intensity aerobic activity." << endl;
        intensity = "light";
    }
    else if (calories <= 500)
    {
        cout << "\nModerate-intensity activity." << endl;
        intensity = "moderate";
    }
    else
    {
        cout << "\nVigorous-intensity aerobic activity." << endl;
        intensity = "heavy";
    }
}

// Precondition: None
// Pauses the program
// Postcondition: None
void pause()
{
    cout << "\nPress enter to continue.";
    cin.ignore();
    cin.get();
}

// Precondition: reference variable string userID
// Randomly generates an unique user ID
// Postcondition: None
void createUserID(int &userID, int numHits)
{
    if(numHits == 0)
    {
        srand(time(NULL));
    }
    userID = rand() % 99999 + 1;
    cout << setfill(' ') << setw(67) << "User ID: " << setfill('0') << setw(5) << userID << endl;
}

// Precondition: Int reference variable
// Keeps count of how many times the menu has been brought up.
// Postcondition: None
static void hits(int &numHits)
{
    cout << setfill(' ') << setw(67) << "Number of hits today: " << setfill('0') << setw(5) << ++numHits << endl;
}

// Precondition: referenced stream for the log, referenced string userID, referenced string activity,
// reference ints minutes, weight, calories, intensity, and referenced char* timeOf
// Stores all values to tranlog.txt
// Postcondition: None
void writeToLog(fstream &transactionLog, int &userID, string &activity, int &minutes,
                int &weight, float &calories, string &intensity, char* &timeOf)
{
    transactionLog << userID << ' ' << activity << ',' << minutes << ' ' << weight << ' '
                   << calories << ' ' << intensity << ' ' << timeOf << ',' << '\n';
}

// Precondition: a reference char* timeOf
// Gets the time and data and stores it in time of
// Postcondition: None
void getTime(char* &timeOf)
{
    // current date/time based on current system
    time_t now = time(0);  // convert now to c-string form
    timeOf = ctime(&now);  // we want a way to limit the size to be just 20 in length
    timeOf[20] = '\0'; // this effectively truncates the c-string
}

// Precondition: referenced stream for the log, referenced string userID, referenced string activity,
// reference ints minutes, weight, calories, intensity, and referenced char* timeOf
// Prints a heading and then outputs all values from tranlog.txt
// Postcondition: None
void printLog(fstream &transactionLog, int &userID, string &activity, int &minutes,
              int &weight, float &calories, string &intensity, string &time)
{
    cout << "\nUserID    Activity     Mins Weight Calories Intensity     Time Stamp" << endl;
    // reset everything and go to the beginning of the file
    transactionLog.clear();
    transactionLog.seekg(0, std::ios::beg);
    cout.precision(1); // sets floats to one decimal places
    cout.setf(ios::fixed, ios::floatfield);
    // string id = std::to_string(userID);
    while(transactionLog >> userID) // gets input from file until the end of the file
    {
        getline(transactionLog, activity, ',');
        transactionLog >> minutes >> weight >> calories >> intensity;
        getline(transactionLog, time, ',');
        cout << setfill('0') << setw(5) << userID << "  " << std::left << setfill(' ') << setw(17) << activity << minutes << "   " // outputs info from one line
             << setw(7) << weight << setw(8) << calories << std::left << setw(9) << intensity << time << std::internal << "\n";
    }
    // reset everything and go to the end of the file
    transactionLog.clear();
    transactionLog.seekg(0, std::ios::end);
}

// Precondition: None
// Checks if user knows the password.
// Postcondition: True if password is entered correctly, false otherwise
bool password()
{
    string attempt;
    cout << "Enter the super secret password to view the log: ";
    cin >> attempt;
    if(attempt == "Top-Secret")
    {
        return true;
    }
    cout << "SECURITY BREACH";
    return false;
}
