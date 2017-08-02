/*********************************************************************
 ** Program name: ant.hpp
 ** Author: reuben youngblom
 ** Date: 1/22/17
 ** Description: header file for Project 1
 *********************************************************************/



#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>    //for using random
using namespace std;


class Ant   //Ant class.  This basically runs the program. It holds all global variables and functions.

{
private:
    int xDim;  // will hold the user-defined X dimension of the grid
    int yDim;  // will hold the user-inputted Y dimension of the grid
    int startX, startY;  //will hold initial starting position (and future current position)
    int randomStartX, randomStartY; //holds random start coordinates
    char ant, antOrientation, origin;  //holds ant variables that will be clear later
    
    
public:
    char ** start();  //function to start (and
    char ** setBoard();
    void printBoard(char ** pointArray);
    char antPosition(char);
    //char antFirstMove(char ** currentArray);  //I had this in here in case I needed the first move to be different.  I only kept it in becuase it was part of my original testing plan
    char antMove (char ** currentArray, char ** colorArray); //actually makes the moves
    
};