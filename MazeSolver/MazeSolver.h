#pragma once
#include <iostream>
#include <string>
#include <fstream>	// for file i/o
#include <vector>
/* Preprocessor directives to define macros */
#define MAZE1     "maze1.txt"
#define MAZE2     "maze2.txt"
#define MAZE3     "maze3.txt"
#define MAZE119   "maze119.txt"
#define MAZE3877  "maze3877.txt"
#define MAZE_WALL '*'
#define BUFFER    128

// Structure used as the cell for the maze representation
struct maze_cell {
	char character;
	bool visited;
};

void start();
void getDimensions(std::ifstream& mazefile, int* dimensions);
maze_cell** getMaze(std::ifstream& mazefile, int* dimensions);
void getPaths(maze_cell** mymaze, int* pathcount, std::string& pathstring, std::vector <std::string>& allstringpaths, int* dimensions, int row, int col);
void getshortestpath(std::vector <std::string>& allstringpaths);
void getcheapestpath(std::vector <std::string>& allstringpaths);