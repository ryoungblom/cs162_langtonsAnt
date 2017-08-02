/*********************************************************************
 ** Program name: main.cpp
 ** Author: reuben youngblom
 ** Date: 1/22/17
 ** Description: main cpp file for project 1
 *********************************************************************/

#include "ant.hpp"

int main ()  //main function
{
    
    Ant langton;  // I created an instance of my Ant class and named it Langton because I'm creative

    int steps;  //creates a variable for user-inputted number of steps
    
    char ** antHolder;  //creates pointer-to-pointer array.  This one is for displaying ant and board
    char ** colorArray;  //this one is purely used for holding colors (black vs white)
    
    cout << "Hello! This is Langton's Ant." << endl;  //intro
    cout << "Please enter some information to get started." << endl;  //intro
    cout << "First, how many steps would you like to ant to go through?" << endl;  //directions (will take user input later)
    
    while (true)  //input validation.  Will keep looping until good input breaks out of the loop
    {
    cout << "Please enter a number (over 20 would be best):" << endl;  //asks for numer of steps, suggests 20+
    cin >> steps;  //takes in input

        if (steps > 0)  //must be larger than zero.  If greater than zero, breaks out of while loop
        {break;}
        
        cout << "Sorry, I didn't get that! Your number is too low!";  //if not, re-prompts and will re-loop
        cout << endl;
    }

    antHolder = langton.start();  //sends initial empty array to start() for filling and more input (board creation)
    colorArray = langton.setBoard();  // sets the board up initially


    for (int i = 0; i < steps; i++)  //then loops through the user-specified number of times (steps)
    
    {
        langton.antMove(antHolder, colorArray);  //every loop sends set-up array and color tracker to antMove function, where it will move the ant and print the current board.
    }

    return 0;
}