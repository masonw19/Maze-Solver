#include "MazeSolver.h"

void process() {
	int dimensions[2];				  // our dimensions variable
	maze_cell** mymaze;				  // our maze array variable
	std::ifstream mazefile(MAZE119);    // open text file
	int row = 0;	// start on row 0
	int col = 0;	// start on col 0 
	int pathcount = 0;
	int* pathpointer = &pathcount;	// number of paths found will start at 0
		
	if (!mazefile) {
		std::cout << "Unable to open maze file\n";
		return;
	}

	getDimensions(mazefile, dimensions);	// get the maze dimensions
	mymaze = getMaze(mazefile, dimensions);	// we want to store the maze 
	mazefile.close();	// we are done with the file now so we can close it
	getPaths(mymaze, pathpointer, dimensions, row, col);
	std::cout << "\nPATHS FOUND: " << pathcount << '\n';

	showPathing(mymaze, dimensions);
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
	for (int row = 0; row < row_size; row++) {
		for (int col = 0; col < col_size; col++) {
			std::cout << mymaze[row][col].character;
		}	
		std::cout << '\n';
	}

	return mymaze;
}

// get path 
void getPaths(maze_cell** mymaze, int* pathpointer, int* dimensions, int row, int col) {
	int row_size = dimensions[0];
	int col_size = dimensions[1];
	mymaze[row][col].visited = true;	// set the cell we are currently at to be visited

	if (mymaze[row][col].character == MAZE_WALL) {	// check if we have hit a wall
		return;
	}
	if (col == dimensions[1] - 1){						// check if we have reached the end of the maze
		*pathpointer += 1;
		mymaze[row][col].visited = false;				// unvisit the cell so that other paths can make it to the end
		return;
	}
	

	if (col - 1 >= 0 && mymaze[row][col - 1].visited == false) {		// check backwards
		getPaths(mymaze, pathpointer, dimensions, row, col - 1);
	}
	if (row - 1 >= 0 && mymaze[row - 1][col].visited == false) {		// check upwards
		getPaths(mymaze, pathpointer, dimensions, row - 1, col);
	}
	if (col + 1 < col_size && mymaze[row][col + 1].visited == false) {	// check forwards
		getPaths(mymaze, pathpointer, dimensions, row, col + 1);
	}
	if (row + 1 < row_size && mymaze[row + 1][col].visited == false) {	// check downwards
		getPaths(mymaze, pathpointer, dimensions, row + 1, col);
	}
	mymaze[row][col].visited = false;	// unvisit the cell after we return so that this cell is not blocked off from other paths
	return;
}


// show the pathing
void showPathing(maze_cell** mymaze, int* dimensions) {
	int row_size = dimensions[0];
	int col_size = dimensions[1];
	for (int row = 0; row < row_size; row++) {
		for (int col = 0; col < col_size; col++) {
			std::cout << mymaze[row][col].character << ", " << mymaze[row][col].visited << '\t';
		}
		std::cout << '\n';
	}
	return;
}