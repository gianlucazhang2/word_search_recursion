#include <iostream>
#include <fstream>
#include <vector>
#include <string>

class Grid {
public:
	//constructor
	Grid(unsigned int r, unsigned int c) {
		grid = std::vector<std::vector<char>>(r, std::vector<char>(c, '.')); 
		numRows = r; 
		numCols = c; 
	}
	
	//accessors 
	unsigned int getRows() {
		return numRows; 
	}
	
	unsigned int getCols() {
		return numCols;  
	}
	
	char getChar(unsigned int r, unsigned c) {
		return grid[r][c];
	}
	
	//modifiers
	void setChar(unsigned int r, unsigned c, char ch) {
		grid[r][c] = ch; 
	}

private:
	std::vector<std::vector<char>> grid; 
	int numRows, numCols; 
}; 

std::ostream& operator<<(std::ostream &out, Grid &grid) {
	for (unsigned int i = 0; i < grid.getRows(); i++) {
		out << "  "; 
		for (unsigned int j = 0; j < grid.getCols(); j++) {
			out << grid.getChar(i, j); 
		}
		if (i != grid.getRows() - 1) {out << std::endl; }
	}
	return out; 
}

bool operator==(Grid g1, Grid g2) {
	if (g1.getRows() != g2.getRows() || g1.getCols() != g2.getCols()) {
		return false; 
	}
	else {
	for (int i = 0; i < g1.getRows(); i++) {
		for (int j = 0; j < g1.getCols(); j++) {
			if (g1.getChar(i, j) != g2.getChar(i, j)) {
				return false; 
			}
		}
	}
	}
	return true; 
}
	