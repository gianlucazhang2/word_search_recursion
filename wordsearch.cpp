#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include "grid.h"

//8 possible directions for a word to go
const std::string alpha = "abcdefghijklmnopqrstuvwxyz"; 
const int dx[] = {1, -1, 0, 0, 1, 1, -1, -1}; 
const int dy[] = {0, 0, 1, -1, 1, -1, 1, -1};
std::vector<Grid> solutions = std::vector<Grid>(); 
std::vector<std::string> wordList, xList; 
int r, c; 

//read input file - set width, height, required word list, and forbidden word list
void readWordList(std::string input) {
	std::ifstream inputFile(input); 
	std::string word;
	char ch; 
	inputFile >> c >> r; 
	while (inputFile >> ch >> word) {
		if (ch == '+') {
			wordList.push_back(word); 
		}
		else {
			xList.push_back(word); 
		}
	}
}

bool hasForbWords(Grid grid) {
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			for (int d = 0; d < 8; d++) {
				int nx = i; 
				int ny = j;
				std::string word; 
				while (nx >= 0 && nx < r && ny >= 0 && ny < c) {
					word += grid.getChar(nx, ny); 
					if (std::find(xList.begin(), xList.end(), word) != xList.end()) {
						return true; 
					} 
					nx += dx[d]; 
					ny += dy[d];
				}
			}
		}
	}
	return false; 			
}	

bool gridFilled(Grid grid) {
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			if (grid.getChar(i, j) == '.') {
				return false; 
			}
		}
	}
	return true; 
}

bool wordFits(Grid grid, int direction, int x, int y, int index) {
	std::string word = wordList[index];
	int len = word.length(); 
	for (int i = 0; i < len; i++) {
		int nx = x + i * dx[direction]; 
		int ny = y + i * dy[direction]; 
		if (nx < 0 || ny < 0 || nx >= r || ny >= c || (grid.getChar(nx, ny) != '.' && grid.getChar(nx, ny) != word[i])) {
			return false; 
		}
	}
	return true; 
}

Grid placeWord(Grid grid, int direction, int x, int y, int index) {
	std::string word = wordList[index]; 
	int len = word.length(); 
	for (int i = 0; i < len; i++) {
		int nx = x + i * dx[direction]; 
		int ny = y + i * dy[direction];
		grid.setChar(nx, ny, word[i]); 
	}
	return grid; 
}

void recurAlphabet(Grid grid) {
	if (gridFilled(grid)) {
		for (Grid g: solutions) {
			if (g == grid) {
				return; 
			}
		}
		solutions.push_back(grid); 
		return; 
	}
	int row, col; 
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			if (grid.getChar(i, j) == '.') {
				row = i; 
				col = j; 
			}
		}
	}
	for (int a = 0; a < 26; a++) {
		grid.setChar(row, col, alpha[a]); 
		if (!hasForbWords(grid)) {
			recurAlphabet(grid); 
		}
	}
}

void recurGrid(Grid grid, int index) {
	if (hasForbWords(grid)) {
		return;
	}
	if (gridFilled(grid) && index == (int)wordList.size()) {
		solutions.push_back(grid); 
		return; 
	}
	if (!gridFilled(grid) && index == (int)wordList.size()) {
		recurAlphabet(grid); 
		return; 
	}
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			if (wordFits(grid, 0, i, j, index)) { //vertical 
				Grid g = placeWord(grid, 0, i, j, index); 
				recurGrid(g, index + 1); 
			}
			if (wordFits(grid, 1, i, j, index)) { //reverse vertical
				Grid g = placeWord(grid, 1, i, j, index); 
				recurGrid(g, index + 1); 
			}
			if (wordFits(grid, 2, i, j, index)) { //horizontal
				Grid g =placeWord(grid, 2, i, j, index); 
				recurGrid(g, index + 1); 
			}
			if (wordFits(grid, 3, i, j, index)) { //reverse horizonal
				Grid g = placeWord(grid, 3, i, j, index); 
				recurGrid(g, index + 1); 
			}
			if (wordFits(grid, 4, i, j, index)) { //diagonal br
				Grid g = placeWord(grid, 4, i, j, index); 
				recurGrid(g, index + 1); 
			}
			if (wordFits(grid, 5, i, j, index)) { //diagonal bl
				Grid g = placeWord(grid, 5, i, j, index); 
				recurGrid(g, index + 1); 
			}
			if (wordFits(grid, 6, i, j, index)) { //diagonal tr
				Grid g = placeWord(grid, 6, i, j, index); 
				recurGrid(g, index + 1); 
			}
			if (wordFits(grid, 7, i, j, index)) { //diagonal tl
				Grid g = placeWord(grid, 7, i, j, index); 
				recurGrid(g, index + 1); 
			}
		}
	}	
}

int main(int argc, char* argv[]) {
	if (argc != 4) {
        std::cerr << "Usage: " << argv[0] << " input_file output_file one_solution|all_solutions" << std::endl;
        return 1;
    }
	
	//command arguments
	std::string input = argv[1];
    std::string output = argv[2];
    std::string solutionType = argv[3];
	
	std::ofstream outputFile(output); 
	
	readWordList(input); 
	Grid grid(r, c);  
	recurGrid(grid, 0); 
	
	if (solutionType == "one_solution") {
		outputFile << solutions[0]; 
	}
	else if (solutionType == "all_solutions" && !solutions.empty()) {
		outputFile << solutions.size() << " solution(s)" << std::endl; 
		for (Grid grid: solutions) {
			outputFile << "Board: " << std::endl; 
			outputFile << grid << std::endl; 	
		}
	}
	else {
		outputFile << "No solutions found." <<std::endl; 
	}
	
	return 0; 
}



