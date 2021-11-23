#include <iostream>
#include "dsets.h"
#include "maze.h"
#include "cs225/PNG.h"

using namespace std;

int main()
{
    // Write your own main here
    
    SquareMaze maze;
    maze.makeMaze(10,10);
    PNG* canvas = maze.drawMaze();
    canvas->writeToFile("smallMaze.png");
    cout << "MazeTest created in mazeTest.png" << endl;

    PNG* solvedMaze = maze.drawMazeWithSolution();
    solvedMaze->writeToFile("smallMaze_solved.png");

    SquareMaze maze2;
    maze2.makeMaze(750,750);
    PNG* m2 = maze2.drawMaze();
    m2->writeToFile("BigMaze.png");
    
    PNG* solvedM2 = maze2.drawMazeWithSolution();
    solvedM2->writeToFile("bigMaze_solved.png");

    return 0;
}
