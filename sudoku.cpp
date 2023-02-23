//Created by Dionyssis Antypas 2023

#include <iostream>
#include <vector>
#include <fstream>

//check the subsquare(3x3) for the given number numb
bool check_subsquare (std::vector<std::vector <int> >& grid, int i, int j, int numb)
{
	int row = i- i%3;
	int column = j - j%3;

	for (int i = row; i < row+3; i++){
		for (int j = column; j < column+3; j++) {
			if (grid[i][j] == numb)
				return true;
		}
	}
	return false;
}
//check the whole row for the given number numb
bool check_row (std::vector<std::vector <int> >& grid, int i, int numb)
{
	for(int j=0; j < grid.size(); j++)
		if(grid[i][j] == numb)
			return true;
	return false;
}
//check the whole column for the given number
bool check_column(std::vector<std::vector <int> >& grid, int j, int numb)
{
	for (int i=0; i < grid.size(); i++)
		if(grid[i][j] == numb)
			return true;
	return false;
}
//If the number does not exist in the same row, column or subsquare return true
bool valid(std::vector<std::vector <int> >& grid, int i, int j, int numb)
{
	return !check_row(grid, i, numb) && !check_column(grid, j, numb) && !check_subsquare(grid, i, j, numb);
}
//Check for empty fields marked with 0
bool is_empty(std::vector<std::vector <int> >& grid, int& i, int& j) {
	for(i = 0; i < grid.size(); i++) {
		for (j = 0; j < grid.size(); j++) {
			if (grid[i][j] == 0)
				return true;
		}
	}
	return false;
}
//Funktion printing the sudoku matrix
void print(const std::vector<std::vector <int> >& grid)
{
	for(int i = 0; i < grid.size(); i++) {
		for (int j = 0; j < grid.size(); j++) {
			std::cout << grid[i][j] << " ";
		}
		std::cout << std::endl;
	}
}
//Function using backtracking recursion for the solution of sudoku
bool solution (std::vector < std::vector <int> >& grid)
{   //Values for rows(i) and columns(j)
	int i;
	int j;
	//Checks if field is empty
	if(!is_empty(grid, i, j))
		return true;

	//Loop for picking numbers form 1 to 10
	for(int numb = 1; numb <=9; numb++) {
		//Checks if number can be placed calling the valid function.
		//If not the value of numb is assigned to this field
		if (valid(grid, i, j, numb)) {
			grid[i][j] = numb;

			//If successfully solved
			if(solution(grid))
			{
				return true;
			}
			//If not empty the field
			grid[i][j] = 0;
		}
	}
	//Go one step back with backtracking recursion
	return false;
}

int main()
{
	//Initialize 2D Vector with grid. Values set 0
	std::vector< std::vector <int> > grid;

	
	//String saving the content of .txt file
	std::string line;

	//Input stream operation on file "sudoku.txt"

	std::ifstream sudoku ("sudoku.txt", std::ios::in);

	//Check if sodoku was opened
	if(sudoku.is_open()) {
		//Save the content of sudoku in line string
		while (std::getline(sudoku, line)) {
			//Temporary vector containing each row
			std::vector<int> row;
			//Writes the content of line to temporary vector row;
			for (char &c: line) {
				//Copy only digits
				if (isdigit(c)) {
					row.push_back(c-'0');
				}
			}
			//Copies each row to vector grid
			grid.push_back(row);
		}
	}
	else {
		std::cout << "Error. Sudoku is not open" << std::endl;
		return 1;
	}

	if(solution(grid)) {
		std::cout << "Sudoku solved!" << std::endl;
		print(grid);
	}
	else
		std::cout << "This Sudoku has no solution" << std::endl;

	return 0;
}