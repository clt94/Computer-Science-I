/*
COPYRIGHT (C) 2018 Connor Taylor (clt94) All rights reserved
MyFitness Project Part 1
Author: Connor Taylor
        clt949@zips.uakron.edu
Version. 1.011 07.09.2017
Purpose: Have a program where the user enters in the workout
they did, their weight, and the amount of time they
exercised. Then output the calories they burned.
*/
#include <iostream>
#include <iomanip>
#include <limits>

using namespace std;

int main()
{
    // declares constants for MET values for each exercise
    const float BIKING = 8.0;
    const float RUNNING = 10.0;
    const float LIFTING = 3.0;
    const float YOGA = 2.5;

    // variable for if user wants to view the menu again
    string menu = "Y";

    while (true)
    {
        // outputs main menu and options for workouts
        if (menu == "Y")
        {
            cout << " " << setfill('_') << setw(48) << " " << endl;
            cout << "|" << setfill(' ') << setw(48) << "|" << endl;
            cout << "|\tWelcome to Connor's Fitness Center\t|" << endl;
            cout << "|" << setfill('_') << setw(48) << "|" << endl;
            cout << "|" << setfill(' ') << setw(48) << "|" << endl;
            cout << "|\t\t1) Stationary Bike\t\t|" << endl;
            cout << "|\t\t2) Treadmill\t\t\t|" << endl;
            cout << "|\t\t3) Weight Lifting\t\t|" << endl;
            cout << "|\t\t4) Hatha Yoga\t\t\t|" << endl;
            cout << "|\t\t5) End\t\t\t\t|" << endl;
            cout << "|" << setfill('_') << setw(48) << "|" << endl;
            menu = "";
        }
        // prompts user to enter their workout
        int workout;
        cout << "\nEnter the workout that you wish to track, or end \nto exit: ";
        cin >> workout;

        // checks user for correct inputs (I could not figure out how to fix the input if it was a double)
        while (cin.fail() || workout < 1 || workout > 5)
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');;
            cout << "Please enter a number from 1 to 5: ";
            cin >> workout;
        }

        // exits the program
        if (workout == 5)
        {
            return 0;
        }

        // prompts user to enter their weight
        int weight;
        cout << "\nEnter your weight: ";
        cin >> weight;

        // checks user for correct inputs
        while ((cin.fail()) || weight < 1 || weight > 999)
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');;
            cout << "Please enter a number from 1 to 999: ";
            cin >> weight;
        }

        // prompts user to enter the minutes they exercised
        int minutes;
        cout << "\nEnter the number of minutes: ";
        cin >> minutes;

        // set decimal format to 1
        cout.setf(ios::fixed);
        cout.setf(ios::showpoint);
        cout.precision(1);

        // outputs calories based on exercise chosen by the user
        float met;
        float calories;
        switch (workout)
        {
            case 1 : met = BIKING;
                // checks user for correct inputs
                while ((cin.fail()) || minutes < 30 || minutes > 60)
                {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');;
                    cout << "Please enter a number from 30 to 60: ";
                    cin >> minutes;
                }
                calories = (float)minutes / 60.0 * met * (float)weight / 2.2;
                cout << "\nYour total calories for the stationary bike was: " << calories << endl;
                break;
            case 2 : met = RUNNING;
                // checks user for correct inputs
                while ((cin.fail()) || minutes < 30 || minutes > 60)
                {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');;
                    cout << "Please enter a number from 30 to 60: ";
                    cin >> minutes;
                }
                calories = (float)minutes / 60.0 * met * (float)weight / 2.2;
                cout << "\nYour total calories for the treadmill was: " << calories << endl;
                break;
            case 3 : met = LIFTING;
                // checks user for correct inputs
                while ((cin.fail()) || minutes < 15 || minutes > 30)
                {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');;
                    cout << "Please enter a number from 15 to 30: ";
                    cin >> minutes;
                }
                calories = (float)minutes / 60.0 * met * (float)weight / 2.2;
                cout << "\nYour total calories for weight lifting was: " << calories << endl;
                break;
            case 4 : met = YOGA;
                // checks user for correct inputs
                while ((cin.fail()) || minutes < 60 || minutes > 90)
                {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');;
                    cout << "Please enter a number from 60 to 90: ";
                    cin >> minutes;
                }
                calories = (float)minutes / 60.0 * met * (float)weight / 2.2;
                cout << "\nYour total calories for Hatha yoga was: " << calories << endl;
                break;
        }

        // outputs intensity of the exercise
        if (calories <= 200)
        {
            cout << "\nLight-intensity aerobic activity." << endl;
        }
        else if (calories <= 500)
        {
            cout << "\nModerate-intensity activity." << endl;
        }
        else
        {
            cout << "\nVigorous-intensity aerobic activity." << endl;
        }

        // Pauses the program (I could not figure out how to press any key to continue
        cout << "\nPress enter to continue.";
        cin.ignore();
        cin.get();

        // asks user if they would like to view the menu again
        cout << "\nEnter Y to reopen the main menu: ";
        cin >> menu;
    }

    return 0;
}
