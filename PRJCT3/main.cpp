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
#include <fstream>
#include <string>

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
void validate(int &, const int &, const int &);

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

// Precondition: An int array of pointers
// Postcondition: None
void resetID(int*[]);

// Precondition: An int array of pointers, and two ints
// Postcondition: None
void userIDArray(int*[], int, int);

// Precondition: An int array of pointers
// Postcondition: None
void printIDArray(int*[]);

// Precondition: An int array of pointers
// Postcondition: None
void findUser(int*[], int);

// declares constants for MET values for each exercise
const float BIKING = 8.0;
const float RUNNING = 10.0;
const float LIFTING = 3.0;
const float YOGA = 2.5;

// limits for equipment
const int BIKE_SIZE = 55;
const int TREADMILL_SIZE = 78;
const int WEIGHT_LIFT_SIZE = 123;
const int YOGA_SIZE = 545;

// Global Constants
// Number of fitness activities
const int NUMACTS = 4;
// Number of slots or openings in each of the activities
const int ACTIVITY_SIZES[NUMACTS] = {BIKE_SIZE, TREADMILL_SIZE, WEIGHT_LIFT_SIZE, YOGA_SIZE};

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
    int idSearch;

    // initializes jagged array of pointers
    static int *idArray[NUMACTS];
    idArray[0] = new int[ACTIVITY_SIZES[0]];
    idArray[1] = new int[ACTIVITY_SIZES[1]];
    idArray[2] = new int[ACTIVITY_SIZES[2]];
    idArray[3] = new int[ACTIVITY_SIZES[3]];
    resetID(idArray); // sets all spots to be -1 as empty

    // opens file to log info as input and also output. Set in append mode
    transactionLog.open("tranlog.txt", std::ios::in | std::ios::out | std::ios::app);
    if(!transactionLog.is_open()) // checks if it is open and ends the program if it fails
    {
        cout << "tranlog.txt failed to open.";
        return 0;
    }

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

        if (workout != 8 && workout != 7 && workout != 6 && workout != 5) // normal entry if not a 5, 6, 7, or 8
        {
            // adds user to idArray
            userIDArray(idArray, workout, userID);
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
        else if(workout == 6) // option to print activity usage
        {
            printIDArray(idArray); // prints how many stations are in use
        }
        else if(workout == 7) // option to search for a user
        {
            // prompts user for user they wish to find
            cout << "\nEnter the 5 digit number of the user to find: ";
            cin >> idSearch;
            validate(idSearch, 0, 99999); // validates the input to be from 0 to 99999
            findUser(idArray, idSearch); // calls function to find user
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
    cout << "|\t\t\t 6) Print Activity Usage\t\t\t|" << endl;
    cout << "|\t\t\t 7) Search for a User\t\t\t\t|" << endl;
    cout << "|\t\t\t 8) Quit\t\t\t\t\t|" << endl;
    cout << "|" << setfill('_') << setw(72) << "|" << endl;
}

// Precondition: reference int for user input, int lower bound, and an int upper bound
// Checks for validity of the input from the user and if it falls in the bounds.
// Postcondition: None
void validate(int &input, const int &low, const int &high)
{
	// Compare lower bound input and higher
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
    validate(workout, 1, 8); // validates input from 1 to 6
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

// Precondition: An int array of pointers idArray, and int workout, and int userID
// Adds the user's ID to the array according to the workout they selected
// Postcondition: None
void userIDArray(int *idArray[], int workout, int userID)
{
    static int bikeCount = 0;
    static int treadmillCount = 0;
    static int liftingCount = 0;
    static int yogaCount = 0;

    switch (workout)
    {
        // biking
        case 1 : workout = 1;
            if(idArray[0][BIKE_SIZE - 1] > -1) // goes back to beginning of the array
            {
                cout << "\nSTATIONARY BIKE LIMIT REACHED. RESETTING." << endl;
                bikeCount = 0;
            }
            idArray[0][bikeCount] = userID;
            ++ bikeCount;
            break;
        // running
        case 2 : workout = 2;
            if(idArray[1][TREADMILL_SIZE - 1] > -1) // goes back to beginning of the array
            {
                cout << "\nTREADMILL LIMIT REACHED. RESETTING." << endl;
                treadmillCount = 0;
            }
            idArray[1][treadmillCount] = userID;
            ++ treadmillCount;
            break;
        // lifting
        case 3 : workout = 3;
            if(idArray[2][WEIGHT_LIFT_SIZE - 1] > -1) // goes back to beginning of the array
            {
                cout << "\nWEIGHT MACHINE LIMIT REACHED. RESETTING." << endl;
                liftingCount = 0;
            }
            idArray[2][liftingCount] = userID;
            ++ liftingCount;
            break;
        // yoga
        case 4 : workout = 4;
            if(idArray[3][YOGA_SIZE - 1] > -1) // goes back to beginning of the array
            {
                cout << "\nYOGA MAT LIMIT REACHED. RESETTING." << endl;
                yogaCount = 0;
            }
            idArray[3][yogaCount] = userID;
            ++ yogaCount;
            break;
    }
}

// Precondition: Int array of pointers idArray
// Outputs the amount of stations being used at that moment
// Postcondition: None
void printIDArray(int *idArray[])
{
    int cnt = 0;
    // biking
    for(int i = 0; i < BIKE_SIZE; ++ i)
    {
        if(idArray[0][i] != -1)
        {
            ++ cnt;
        }
        else
        {
            cout << "\nBikes in use/total: \t\t" << cnt << "/" << BIKE_SIZE << endl;
            cnt = 0; // resets count for next exercise
            break;
        }
    }
    // running
    for(int i = 0; i < TREADMILL_SIZE; ++ i)
    {
        if(idArray[1][i] != -1)
        {
            ++ cnt;
        }
        else
        {
            cout << "Treadmills in use/total: \t" << cnt << "/" << TREADMILL_SIZE << endl;
            cnt = 0; // resets count for next exercise
            break;
        }
    }
    // lifting
    for(int i = 0; i < WEIGHT_LIFT_SIZE; ++ i)
    {
        if(idArray[2][i] != -1)
        {
            ++ cnt;
        }
        else
        {
            cout << "Weight machines in use/total: \t" << cnt << "/" << WEIGHT_LIFT_SIZE << endl;
            cnt = 0; // resets count for next exercise
            break;
        }
    }
    // yoga
    for(int i = 0; i < YOGA_SIZE; ++ i)
    {
        if(idArray[3][i] != -1)
        {
            ++ cnt;
        }
        else
        {
            cout << "Yoga mats in use/total: \t" << cnt << "/" << YOGA_SIZE << endl;
            break;
        }
    }
}

// Precondition: Int array of pointers id, and int userID the user is searching for
// Find the index and exercise of the ID the user searched for
// None
void findUser(int *id[], int userID)
{
    bool found = false;
    // biking
    for(int i = 0; i < BIKE_SIZE; ++ i)
    {
        if (id[0][i] == userID)
        {
            cout << "\nUser " << userID << " is doing the activity biking at location " << i + 1 << "." << endl;
            found = true;
        }
    }
    // running
    for(int i = 0; i < TREADMILL_SIZE; ++ i)
    {
        if (id[1][i] == userID)
        {
            cout << "\nUser " << userID << " is doing the activity running at location " << i + 1 << "." << endl;
            found = true;
        }
    }
    // lifting
    for(int i = 0; i < WEIGHT_LIFT_SIZE; ++ i)
    {
        if (id[2][i] == userID)
        {
            cout << "\nUser " << userID << " is doing the activity weight lifting at location " << i + 1 << "." << endl;
            found = true;
        }
    }
    // yoga
    for(int i = 0; i < YOGA_SIZE; ++ i)
    {
        if (id[3][i] == userID)
        {
            cout << "\nUser " << userID << " is doing the activity Hatha yoga at location " << i + 1 << "." << endl;
            found = true;
        }
    }
    // Tells the user the ID is not in the system
    if(!found)
    {
        cout << "\nUser " << userID << " is not active in our system." << endl;
    }
}

// Precondition: Int array of pointers idArray
// Sets all values to -1 as default
// Postcondition: None
void resetID(int *idArray[])
{
    // biking
    for(int i = 0; i < BIKE_SIZE; ++ i)
    {
        idArray[0][i] = -1;
    }
    // running
    for(int i = 0; i < TREADMILL_SIZE; ++ i)
    {
        idArray[1][i] = -1;
    }
    // lifting
    for(int i = 0; i < WEIGHT_LIFT_SIZE; ++ i)
    {
        idArray[2][i] = -1;
    }
    // yoga
    for(int i = 0; i < YOGA_SIZE; ++ i)
    {
        idArray[3][i] = -1;
    }
}
