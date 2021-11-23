/* Your code here! */
#include "maze.h"
#include <vector>
#include <queue>
#include <iostream>

SquareMaze::SquareMaze() {
    //default constructor
    width_ = 0;
    height_ = 0;
}

SquareMaze::~SquareMaze() {
    walls.clear();
}

void SquareMaze::makeMaze(int width, int height) {
    //create maze disjoint set of size w*h
    width_ = width;
    height_ = height;

    mazeSet.addelements(width_ * height_);
    // for loop index as is or index - 1
    for(int i = 0; i < (width_ * height_); i++) {
        //initially all walls are present
        walls.push_back(cell());
    }

    while (mazeSet.size(0) != (width_ * height_)) {
        int cell = std::rand() % (width_ * height_);
        int side = std::rand() % 2; //right (0) or bottom (1) side to remove

        if(side == 0){ //if right make sure its not edge or in set
            if((cell+1) % width_ == 0 || mazeSet.find(cell) == mazeSet.find(cell+1))
                continue;
            else {
                setWall(cell % width_, cell / width_, 0, false); // right
                mazeSet.setunion(cell, cell+1);
            }
        } else {  //if bottom make sure not floor or in set
            if(cell + width_ >= (width_ * height_) || mazeSet.find(cell) == mazeSet.find(cell+width_))
                continue;
            else {
                setWall(cell % width_, cell / width_, 1, false); //bottom
                mazeSet.setunion(cell, cell + width_);
            }
        }

    }

    /**
    //remove random bottom section
    int x = rand() % width_;
    setWall(x, height_ - 1, 1, false);
*/

}

void SquareMaze::setWall(int x, int y, int dir, bool exists) {
    //right = 0, down = 1, left = 2, up = 3
    //righwall = 1, downwall = 2, bothwalls = 3
    if (dir == 0)
        walls[y * width_ + x].right = exists;
    if (dir == 1)
        walls[y * width_ + x].bottom = exists;
}

bool SquareMaze::canTravel(int x, int y, int dir) const {
    if (dir == 0) //right
        return !walls[y * width_ + x].right;
    if (dir == 1) //bottom
        return !walls[y * width_ + x].bottom;
    if (dir == 2) //left
        return ((x != 0) && !walls[y * width_ + x - 1].right);
    if (dir == 3)//top
        return ((y != 0) && !walls[y * width_ + x - width_].bottom);
    return false;
}

PNG* SquareMaze::drawMaze() const{
    PNG* image = new PNG(width_ * 10 + 1, height_ * 10 + 1);

    //create border
    for (int x = 0; x < width_ * 10 + 1; x++) {
        if (x > 9 || x < 1) {
            HSLAPixel& pixel = image->getPixel(x,0);
            pixel.l = 0;
        }

    }
    for (int y = 0; y < height_ * 10 + 1; y++) {
        HSLAPixel& pixel = image->getPixel(0,y);
        pixel.l = 0;
    }
    //bottom right corner square
    for (int x = width_ * 10; x < width_ * 10 + 1; x++ ) {
        for (int y = height_ * 10; y < height_ * 10 + 1; y++) {
            HSLAPixel& pixel = image->getPixel(x,y);
            pixel.l = 0;
        }
    }

    //draw maze
    int lineWidth = 10;

    for (int x = 0; x < width_; x++) {
        for (int y = 0; y < height_; y++) {

            if (walls[y * width_ + x].right) {
                for (int i = 0; i < lineWidth + 1; i++) {
                    HSLAPixel &pix = image->getPixel((x + 1) * 10, y * 10 + i);
                    pix.l = 0;
                }
            }

            if (walls[y * width_ + x].bottom) {
                for (int i = 0; i < lineWidth + 1; i++) {
                    HSLAPixel &pix = image->getPixel(x * 10 + i, (y + 1) * 10);
                    pix.l = 0;
                }
            }
        }

    }

    return image;
}

std::vector<int> SquareMaze::solveMaze(){
    std::vector<int> prev(width_ * height_, -1);
    std::vector<int> distance(width_ * height_, -1);
    std::vector<int> path(width_ * height_, -1);

    std::queue<int> bfs;
    bfs.push(0);
    int curr;

    while(!bfs.empty()) {
        curr = bfs.front();
        int x = curr % width_;
        int y = curr / width_;
        //right,down,left,up (0,1,2,3)
        if (canTravel(x,y,0) && distance[curr + 1] < 0) {//right
            bfs.push(curr + 1);
            prev[curr + 1] = curr;
            distance[curr + 1] = distance[curr] + 1;
            path[curr + 1] = 0;
        }

        if (canTravel(x,y,1) && distance[curr+ width_] < 0) {
            //lower index = curr + width_
            bfs.push(curr + width_);
            prev[curr + width_] = curr;
            distance[curr + width_] = distance[curr] + 1;
            path[curr + width_] = 1;
        }

        if (canTravel(x,y,2) && distance[curr - 1] < 0) {//left
            bfs.push(curr - 1);
            prev[curr - 1] = curr;
            distance[curr - 1] = distance[curr] + 1;
            path[curr - 1] = 2;
        }

        if (canTravel(x,y,3) && (distance[curr - width_] < 0)) {//up
            bfs.push(curr - width_);
            prev[curr - width_] = curr;
            distance[curr - width_] = distance[curr] + 1;
            path[curr - width_] = 3;
        }

        bfs.pop();
    }

    int maxPathIndex = -1;
    int longestPath = width_ * (height_ - 1);

    for(int i = 0; i < width_; i++){
      if(distance[width_ * (height_ - 1) + i] > distance[longestPath]){
        longestPath = width_ * (height_ - 1) + i;
      }
    }

    destination_ = longestPath;
    maxPathIndex = destination_;

    std::vector<int> solution;

    while (maxPathIndex > 0) {
        solution.push_back(path[maxPathIndex]);
        maxPathIndex = prev[maxPathIndex];
    }
    
    reverse(solution.begin(), solution.end());
    return solution;
}

PNG* SquareMaze::drawMazeWithSolution() {
    PNG* maze = drawMaze();

    //start point for drawed line
    int x = 5;
    int y = 5;

    std::vector<int> solution = solveMaze();

    HSLAPixel red;
    red.h = 0;
    red.s = 1;
    red.l = .5;
    red.a = 1;

    for (int i = 1; i < 10; i++) {
        HSLAPixel &pix = maze->getPixel((destination_ % width_) * 10 + i, ((destination_ / width_) + 1) * 10);
        pix.l = 1;
    }

    for (int i : solution) {
        if (i == 0) {
            for (int h = 0; h <= 10; h++) {
                HSLAPixel &p = maze->getPixel(x + h, y);
                p = red;
            }
            x = x + 10;
        }
        if (i == 1) {
            for (int h = 0; h <= 10; h++) {
                HSLAPixel &p = maze->getPixel(x, y + h);
                p = red;
            }
            y = y + 10;
        }
        if (i == 2) {
            for (int h = 0; h <= 10; h++) {
                HSLAPixel &p = maze->getPixel(x - h, y);
                p = red;
            }
            x = x - 10;
        }
        if (i == 3) {
            for (int h = 0; h <= 10; h++) {
                HSLAPixel &p = maze->getPixel(x, y - h);
                p = red;
            }
            y = y - 10;
        }
        
    }
    return maze;
}
