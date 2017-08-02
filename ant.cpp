/*********************************************************************
 ** Program name: ant.cpp
 ** Author: reuben youngblom
 ** Date: 1/22/17
 ** Description: function implementation file for project 1
 *********************************************************************/


#include "ant.hpp"


/*
 Start function.  Takes in intial dynamically-allocated array and sets it up by taking user input.
 */

char ** Ant::start()
{
    
    cout << "Thanks!" << endl;
    
    while (true)  //input validation.  If input is workable, breaks out of the loop.  But if input is bad, will keep looping and re-prompting.
        
    {
        cout << "Please enter the desired dimensions of the matrix (3x3 or larger is probably best—15x15 or so is optimal)." << endl;  //asks for dimensions
        
        cout << "Rows: ";  //asks for X value
        cin >> xDim;  //set it to xDim
        cout << "Columns: ";  //asks for Y value
        cin >> yDim;  //sets to yDim
        
        if (xDim > 1 && yDim > 1)  //make sure they are above 1.  A board of 1 in any direction doesn't give the any anywhere to move.  3x3 is the minimum in that it will still be pretty crappy, but I think 2x2 is the ABSOLUTE minimum. If someone wants to watch that, more power to them.
        {break;}  //if input is over 1 for both dimensions, breaks out of the loop
        
        cout << endl;
        cout << "Sorry! Please make sure your dimensions are greater than one, or the ant can't move!";
        //if not, keeps re-prompting for better input
        cout << endl;
        
    }
    
    
    /*
     Creates new array called antArray that will act as the gameboard.  I took this code (and comments) from Lab 1
     */
    
    char ** antArray = new char*[xDim];  //creates dynamically 2d allocated array using 'new' by:
    for(int i = 0; i < xDim; i++) //running through creating array until user input dictates a stop, and
        antArray[i] = new char[yDim]; //then using new to create the second dimenion of user-specified size
    
    
    
    /*
     Here, I do a few things over the next few lines.  I tell the user I'm printing their board.  So I fill the array with dots, and then print it, so that they can see how big the board will be.  If I just print blank spaces, you can't really see how large the board is because everything just looks white.
     Then, after printing the version with the dots, I reset the board to just white so that when it actually starts running the ant is moving on white (with no dots)
     */

    cout << "This is what your matrix will look like (dots for scale):" << endl;
    cout << endl;
    
    
    for (int i = 0; i < xDim; ++i)  //fills array with dots
    {
        for (int j = 0; j < yDim; ++j)
        {
            antArray[i][j] = '.' ;
        }
    }
    
    
    
    
    for (int i = 0; i < xDim; ++i)  //prints array with dots
    {
        for (int j = 0; j < yDim; ++j)
        {
            cout << antArray[i][j] << ' ';
        }
        cout << endl;
    }
    
    
    for (int i = 0; i < xDim; ++i)  //sets it back to pure white
    {
        for (int j = 0; j < yDim; ++j)
        {
            antArray[i][j] = ' ' ;   //determines final output.  ultimately, I left it blank.
        }
    }
    
    
    cout << endl;
    
    cout << "Would you like to select the ant's starting postion manually, or randomly?" << endl;  //gives user the choice to choose starting location or use random start
    
    while (true)  //input validation.  If input is bad, re-promts and loops, but if it's good, breaks out of the loop
        
    {cout << "push 'm' to enter manually, or 'r' for a random start:" << endl;
        
        cin >> origin;  //takes in command
        
        if (origin == 'm' or origin == 'M' or origin == 'r' or origin == 'R')  //tests command
        {break;}
        
        cout << endl;
        cout << "Sorry, I didn't get that! Please enter either 'm' or 'r'" << endl;  //reprompt, if necessary
        
    }
    
    
    if (origin == 'm' or origin == 'M')  //IF user wants a manual starting position:
        
    {
        
        cout << "Great!" << endl;
        
        while (true)  //input validation loop.  Same as all the other validation loops
            
        {
            cout << "Where would you like the ant to start? Please enter coordinates:" << endl;
            cout << "X position: ";  //asks for desired X-coordinate
            cin >> startX; //sets to startX
            cout << "Y position: ";  //asks for Y coordinate
            cin >> startY; //sets to startY
            cout << endl;
            
            startX = startX-1;  //sets the coordinates to what is expected.  Most graphs start counting at 1, but arrays start at 0.  A user entering 1,1 will now start on the first space
            startY = startY-1;
            
            
            if (startX < xDim && startY < yDim)  //test.  If coordinates are on the graph, breaks out of loop.
                
            {break;}
            
            
            cout << endl;
            cout << "Sorry, your ant is off the grid! Please place the ant on the grid.   ";  //if not, re-prompt and loop
        }
        
    }
    
    else if (origin == 'r' or origin == 'R')  //But if user wants a random location:
    {
        randomStartX = xDim-1;  //sets upper bound for X dimension, accounting for the fact the arrays start at zero
        randomStartY = yDim-1; //sets upper bound for Y dimension, accounting for the fact the arrays start at zero
        
        srand (time(NULL));  //seeds the random number (code taken from Stack Overflow)
        startX = rand()%(randomStartX); //sets startX to random number (under upper bound determined above)
        startY = rand()%(randomStartY); //sets startY to random number (under upper bound determined above)

    }
    
    
    
    while (true)  //validates ant orientation input
    {
        cout << endl;
        cout << "What direction should the ant face?" << endl;
        cout << "Please input 'u' for up, 'd' for down, 'l' for left, or 'r' for right:" << endl;
        
        cin >> antOrientation;  //I use these to determine which direction the ant should start off facing.  Not specified in the directions, but as I was using these symbols to keep track of the ant's direction anyways, was easy to let user specify.
        
        
        if (antOrientation == 'u' or antOrientation == 'd' or antOrientation == 'l' or antOrientation == 'r')
        {break;}  //checks input.  If allowed, breaks out of loop
        
        
        cout << endl;
        cout << "Sorry, I didn't get that! Please try again.  ";  //if not, reprompt
        
    }
    
    antPosition(antOrientation);  //sends input to antPosition
    
    cout << "Thanks!" << endl;
    cout << endl;
    
    antArray [startX][startY] = '*';  //sets ant on board, given starting coordinates
    
    for (int i = 0; i < xDim; ++i)   //and prints board.  So far, the ant hasn't moved, it's just been placed and has a direction.
    {
        for (int j = 0; j < yDim; ++j)
        {
            cout << antArray[i][j] << ' ';  //prints the board.
        }
        cout << endl;
    }
    
    return antArray; //and returns the array with the ant placed on it
}


/*
 I use this function to create a secondary board that the user will never see.  It just tracks the colors, because if I just used the original array, I would lose track of the color of the board when the ant is on a space.  That is, here, since there's no ant, I can tell whether a square is filled with ' ' or '#'.  If i just used the game board, the current square would be filled with '*'.  So it's like... the base layer, that jsut keeps track of things in the background.
 */

char ** Ant::setBoard()
{
    
    /*
     Creates new array called colorArray that will track the colors of the spaces.  I took this code (and comments) from Lab 1
     */
    
    char ** colorArray = new char*[xDim];  //creates dynamically 2d allocated array using 'new' by:
    for(int i = 0; i < xDim; i++) //running through creating array until user input dictates a stop, and
        colorArray[i] = new char[yDim]; //then using new to create the second dimenion of user-specified size
    
    for (int i = 0; i < xDim; ++i)
    {
        for (int j = 0; j < yDim; ++j)
        {
            colorArray[i][j] = ' ' ;  //sets array to blank spaces to start (all white)
        }
    }
    
    return colorArray;  //returns array
}

/*
 I use this function to print the current state of antArray—the version of the board with the ant ('*') on it  I never print the colorArray color-tracking board.
 */

void Ant::printBoard(char ** pointArray)
{
    
    cout << endl;  //puts a space first (and after, below) for aesthetics
    
    for (int i = 0; i < xDim; ++i)
    {
        for (int j = 0; j < yDim; ++j)
        {
            cout << pointArray[i][j] << ' ';  //prints the board
        }
        cout << endl;
    }
    cout << endl;
    
}


/*
 this function just converts the user's alpha input to directional symbols, which I will use for tracking the ant's direction.  The user never sees these, so I could have just left them as letters, but this was easier for me to visualize.
 */

char Ant::antPosition (char antDirection)
{
    
    
    antDirection = tolower(antDirection);  //converts it to lower case, in case user entered something like 'D' instead of 'd' or something.
    
    if (antDirection == 'u')  //'u' = '^'
    {
        ant = '^';
    }
    
    else if ( antDirection == 'd')  //and so on.  down = the down symbol, etc.
    {
        ant = 'v';
    }
    
    else if (antDirection == 'l')//etc
    {
        ant = '<';
    }
    
    else if (antDirection == 'r') //etc
    {
        ant = '>';
    }
    
    return ant; //and returns the current symbol
}

/*
 This below function I kept in despite it not being used, because it was part of my test plan.  I thought that maybe I would need a different first move and then all the rest of the moves would be the same.  I eventually modified to make all moves, including the first move, the same function.  But this was my original design.
 */
 
 /*

char Ant::antFirstMove (char ** currentArray)
{
    
    
    if (ant == '^')
    {
        currentArray [startX][startY] = '%';
        currentArray [startX-1][startY] = '*';
        printBoard(currentArray);
        
        
        startX = startX-1;
        
    }
    
    if (ant == 'v')
    {
        currentArray [startX][startY] = '%';
        currentArray [startX+1][startY] = '*';
        printBoard(currentArray);
        
        startX = startX+1;
        
    }
    
    if (ant == '<')
    {
        currentArray [startX][startY] = '%';
        currentArray [startX][startY-1] = '*';
        printBoard(currentArray);
        
        startY = startY-1;
    }
    
    
    if (ant == '>')
    {
        currentArray [startX][startY] = '%';
        currentArray [startX][startY+1] = '*';
        printBoard(currentArray);
        
        startY = startY+1;
    }
    
    return ant;
}

 */


/*
 This is my big function that actually makes the moves.  Basically, it looks at the direction, and figures out what to do.
 
 Each block is the same.  It takes the current square the ant is on, determines the color (using colorArray, because according to antArray, the space is filled with '*').  Then, it switches the color on antArray, removing the '*'.
 
 Then, it check to see if a move would put the ant out of bounds.  If it would, it wraps it around.  I did this by checking the X and Y dimensions.  If the any goes out by being too high on either dimension, I reset that coordinate to zero, wrapping it around.  But, if it goes out by trying to go to a space less than zero, I wrap it by changing that coordinate to be equal to the high bound.
 
 Then, I change the position marker of the ant.  I use basic logic for this:  If the ant is facing, say, up ('^'), and it moves onto a white square, it turns 90 degrees right and becomes '>' (right).  I then place the ant on the appropriate square (since it only moves one square at a time, it will either move +/- 1 on either the X or Y dimension.  So For each conditional, the ant will need an orientation, a color, and whether it is out of bounds.  The rest is just brute-force logic.
 
Once the logic is done (via a series of if/else if statements), I print the board, and reset the input coordinates (startX and startY, which I just reuse) to the current ant position, and return the ant (which is my variable holding the orientation).
 
 */


char Ant::antMove (char ** currentArray, char ** colorArray)
{
    

/* BLOCK ONE */
    
    if (ant == '^')  //if ant orientation is '^':
    {
        
        
        if (colorArray[startX][startY] == ' ')  //check current square color, and switch it
        {
            colorArray[startX][startY] = '#';
            currentArray [startX][startY] = '#';
        }
        
        
        else if (colorArray[startX][startY] == '#') //i.e. if it's black...
        {
            colorArray[startX][startY] = ' ';  ///make it white on both antArray and colorArray
            currentArray [startX][startY] = ' ';
            
        }
        
        
        if(startX-1 < 0)  //Make sure it's in-bounds.  Make sure it's greater than zero.  If not...
        {
            
            startX = xDim-1;   //wrap it around, and then:
            
            if (colorArray[startX][startY] == ' ')  //check color, and set orientation properly
            {ant = '>';} //i.e. given that original orientatin was up, if this new wrapped square is white, 90 degree right is right.
            else if (colorArray[startX][startY] == '#')
            {ant = '<';} //same for black, but 90 degrees left
            
            currentArray [startX][startY] = '*';  //and place ant
        }
        
        
        
        else  //however, if it's not out of bounds, just do the same logic.
        {
            if (colorArray[startX-1][startY] == ' ')  //if this new square is white...
            {ant = '>';}  //90 degrees to the right
            else if (colorArray[startX-1][startY] == '#')
            {ant = '<';}  //but if it's black, 90 degrees to the left.
            
            
            currentArray [startX-1][startY] = '*';  //and place the ant on antArray
            startX = startX-1;  //and reset the coordinates (X is the only one that changes in this situation)
        }
        
        
        printBoard(currentArray);  //then print board.
        
        
    }
    
    
    /*
     The rest of the blocks (blocks 2-4) are exactly the same logic.  Take starting input... Run through if/else statements until you get to the proper starting input.  Given this orientation, do the following:
     1. switch square colors;
     2. check for out of bounds
     3. if it's out of bounds, wrap it
     4. Then change the orientation, based on the original input and the square color
     5. place the ant on ant Array
     6. print
     
     */
    
    
/* BLOCK TWO */
    
    else if (ant == 'v')
    {
        
        
        
        if (colorArray[startX][startY] == ' ')
        {
            colorArray[startX][startY] = '#';
            currentArray [startX][startY] = '#';
        }
        
        
        else if (colorArray[startX][startY] == '#')
        {
            colorArray[startX][startY] = ' ';
            currentArray [startX][startY] = ' ';
        }
        
        
        if(startX+1 >= xDim)
        {
            startX = 0;
            
            if (colorArray[startX][startY] == ' ')
            {ant = '<';}
            else if (colorArray[startX][startY] == '#')
            {ant = '>';}
            
            currentArray [startX][startY] = '*';
            
            
        }
        
        
        else
        {
            if (colorArray[startX+1][startY] == ' ')
            {ant = '<';}
            else if (colorArray[startX+1][startY] == '#')
            {ant = '>';}
            
            currentArray [startX+1][startY] = '*';
            startX = startX+1;
        }
        
        printBoard(currentArray);
        
        
    }
    
    
    /*
     Same logic for block three:
     1. switch square colors;
     2. check for out of bounds
     3. if it's out of bounds, wrap it
     4. Then change the orientation, based on the original input and the square color
     5. place the ant on ant Array
     6. print
     */
    
/* BLOCK THREE */
    
    else if (ant == '<')
    {
        if (colorArray[startX][startY] == ' ')
        {
            colorArray[startX][startY] = '#';
            currentArray [startX][startY] = '#';
        }
        
        
        else if (colorArray[startX][startY] == '#')
        {
            colorArray[startX][startY] = ' ';
            currentArray [startX][startY] = ' ';
        }
        
        
        
        if (startY-1 <0)
        {
            
            startY = yDim-1;
            
            if (colorArray[startX][startY] == ' ')
            {ant = '^';}
            else if (colorArray[startX][startY] == '#')
            {ant = 'v';}
            
            
            
            currentArray [startX][startY] = '*';
            
        }
        
        else{
            if (colorArray[startX][startY-1] == ' ')
            {ant = '^';}
            else if (colorArray[startX][startY-1] == '#')
            {ant = 'v';}
            
            
            currentArray [startX][startY-1] = '*';
            startY = startY-1;
        }
        
        printBoard(currentArray);
        
    }
    
    /*
     Same logic for block four:
     1. switch square colors;
     2. check for out of bounds
     3. if it's out of bounds, wrap it
     4. Then change the orientation, based on the original input and the square color
     5. place the ant on ant Array
     6. print
     */
    
/* BLOCK FOUR */
    
    else if (ant == '>')
    {
        
        
        
        if (colorArray[startX][startY] == ' ')
        {
            colorArray[startX][startY] = '#';
            currentArray [startX][startY] = '#';
        }
        
        
        else if (colorArray[startX][startY] == '#')
        {
            colorArray[startX][startY] = ' ';
            currentArray [startX][startY] = ' ';
            
        }
        
        
        
        
        if (startY+1 >= yDim)
        {
            startY = 0;
            
            if (colorArray[startX][startY] == ' ')
            {ant = 'v';}
            
            else if (colorArray[startX][startY] == '#')
            {ant = '^';}
            
            
            currentArray [startX][startY] = '*';
        }
        
        
        
        else
        {
            if (colorArray[startX][startY+1] == ' ')
            {ant = 'v';}
            
            else if (colorArray[startX][startY+1] == '#')
            {ant = '^';}
            
            
            currentArray [startX][startY+1] = '*';
            startY = startY+1;
            
        }
        
        printBoard(currentArray);
        
    }
    
    
    usleep (450000);  //here, I put a pause so the ant wouldn't just blaze through at processing speed.  There should be a pause in between prints
    return ant;  //and returns ant, and the cycle starts all over again.
    
}


