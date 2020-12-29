#include "MazeSolver.h"

void start() {
	int dimensions[2];				  // our dimensions variable
	maze_cell** mymaze;				  // our maze array variable
	std::ifstream mazefile(MAZE3877);    // open text file
	int row = 0;	// start on row 0
	int col = 0;	// start on col 0 
	int pathcount = 0;
	std::string pathstring; 
	std::vector <std::string> allstringpaths;
		
	if (!mazefile) {
		std::cout << "Unable to open maze file\n";
		return;
	}

	getDimensions(mazefile, dimensions);	// get the maze dimensions
	std::cout << pathstring;
	mymaze = getMaze(mazefile, dimensions);	// we want to store the maze 
	mazefile.close();	// we are done with the file now so we can close it
	getPaths(mymaze, &pathcount, pathstring, allstringpaths, dimensions, row, col);
	std::cout << "Total number of paths: " << pathcount << '\n';
	delete[] mymaze;	// release the dynamically allocated memory
	getshortestpath(allstringpaths);
	getcheapestpath(allstringpaths);

	return;
}

// this method will get the maze dimensions
void getDimensions(std::ifstream& mazefile, int* dimensions) {
	int height = 0;
	int width = 0;
	std::string line;

	while (getline(mazefile, line)) {
		height += 1;
	}
	width = line.size();

	dimensions[0] = height;
	dimensions[1] = width;

	mazefile.clear();	// clears end of file flags
	mazefile.seekg(0);	// return to the beginning of the file
		
	return;
}

// we will get the maze
maze_cell** getMaze(std::ifstream& mazefile, int* dimensions) {
	maze_cell** mymaze;	// we need a  2D array of our struct type. we need to have it dynamically allocated because we won't know size of the maze
	std::string line;
	int row_size = dimensions[0];
	int col_size = dimensions[1];
	
	// dynamically allocate memory for the 2d array of maze_cell type
	mymaze = new maze_cell* [row_size];		// dynamically allocate the rows of maze_cells
	for (int i = 0; i < row_size; i++)			// dynamically allocate the columns of maze_cells
		mymaze[i] = new maze_cell[col_size];

	// fill our 2d array with the maze in the text file
	for (int row = 0; row < row_size; row++) {
		getline(mazefile, line);
		for (int col = 0; col < col_size; col++) {
			mymaze[row][col].character = line[col];
			mymaze[row][col].visited = false;
		}
	}
	
	// print the maze
	std::cout << "Our Maze: \n";
	for (int row = 0; row < row_size; row++) {
		for (int col = 0; col < col_size; col++) {
			std::cout << mymaze[row][col].character;
		}	
		std::cout << '\n';
	}
	std::cout << '\n';
	return mymaze;
}

// get path 
void getPaths(maze_cell** mymaze, int* pathcount, std::string& pathstring, std::vector <std::string>& allstringpaths, int* dimensions, int row, int col) {
	int row_size = dimensions[0];
	int col_size = dimensions[1];
	mymaze[row][col].visited = true;	// set the cell we are currently at to be visited

	if (mymaze[row][col].character == MAZE_WALL) {	// check if we have hit a wall
		return;
	}
	pathstring.push_back(mymaze[row][col].character);	// add character to pathstring
	if (col == dimensions[1] - 1){						// check if we have reached the end of the maze
		*pathcount += 1;
		mymaze[row][col].visited = false;				// unvisit the cell so that other paths can make it to the end

		allstringpaths.push_back(pathstring);
		
		pathstring.pop_back();				// pop the last element in the string
		return;
	}

	if (col - 1 >= 0 && mymaze[row][col - 1].visited == false) {		// check backwards
		getPaths(mymaze, pathcount, pathstring, allstringpaths, dimensions, row, col - 1);
	}
	if (row - 1 >= 0 && mymaze[row - 1][col].visited == false) {		// check upwards
		getPaths(mymaze, pathcount, pathstring, allstringpaths, dimensions, row - 1, col);
	}
	if (col + 1 < col_size && mymaze[row][col + 1].visited == false) {	// check forwards
		getPaths(mymaze, pathcount, pathstring, allstringpaths, dimensions, row, col + 1);
	}
	if (row + 1 < row_size && mymaze[row + 1][col].visited == false) {	// check downwards
		getPaths(mymaze, pathcount, pathstring, allstringpaths, dimensions, row + 1, col);
	}
	mymaze[row][col].visited = false;	// unvisit the cell after we return so that this cell is not blocked off from other paths
	pathstring.pop_back();				// pop the last element in the string
	return;
}

void getshortestpath(std::vector <std::string>& allstringpaths) {
	int shortest = 0;
	
	for (int i = 1; i < allstringpaths.size(); i++) {
		if (allstringpaths[i].size() < allstringpaths[shortest].size())
			shortest = i;
	}

	std::cout << "Shortest path: " << allstringpaths[shortest] << '\n';
}

void getcheapestpath(std::vector <std::string>& allstringpaths) {
	int count = 0;
	int shortest_count = 0;
	int count_index = 0;

	for (int j = 0; j < allstringpaths[0][j]; j++) {
		shortest_count += allstringpaths[0][j] - '0';
	}
	for (int i = 1; i < allstringpaths.size(); i++) {
		for (int j = 0; j < allstringpaths[i].size(); j++) {
			count += allstringpaths[i][j] - '0';
		}
		if (count < shortest_count) {
			shortest_count = count;
			count_index = i;
		}
		count = 0;
	}
	
	std::cout << "Cheapest path: " << allstringpaths[count_index] << '\n';
	std::cout << "Cheapest path cost: " << shortest_count << "\n\n";
}