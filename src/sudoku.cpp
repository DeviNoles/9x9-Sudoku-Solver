/**
 * @brief Sudoku class implementation
 */

#include <string>
#include <fstream>
#include <iostream>
#include <iomanip>
#include "sudoku.hpp"

/**
  @brief Parameterized constructor. Parses file passed in and puts data into grid data structure

  @param infile File to open and parse
*/
Sudoku::Sudoku(std::string infile){
	std::ifstream instream(infile);
  	std::string in;
  	Sudoku::Cell cell;
  	std::vector<Sudoku::Cell> row;
  	for(int i = 0; i < 6; ++i){
  		for(int j = 0; j < 6; ++j){
  			instream >> in;
  			if(in.find("/") != std::string::npos){
  				cell.two_vals = true;

  				if(in.substr(0,1) == "-"){
  					cell.vals.first = 0;
  				} else {
  					cell.vals.first = std::stoi(in.substr(0,1));
  				}

  				if(in.substr(2,1) == "-"){
  					cell.vals.second = 0;
  				} else {
  					cell.vals.second = std::stoi(in.substr(2,1));
  				}

  			} else {
  				cell.two_vals = false;

  				if(in.find("-") != std::string::npos){
  					cell.vals.first = 0;
  					cell.vals.second = 0;
  				} else {
  					cell.vals.first = std::stoi(in);
  					cell.vals.second = 0;
  				}
  			}
  			row.push_back(cell);
  		}
  		grid.push_back(row);
  		row.clear();
  	}
}

/**
  @brief Recursively solves Sudoku puzzle

  @return bool
*/
bool Sudoku::Solve(){
	// which is value to change to 0 via backtracking later, default: -1 (designates cell has 1 value)
	int which = -1;

	// locate unsolved cell, row/col default: -1
    int row = -1;
  	int col = -1;
  	locate_unsolved(row, col);

    // If none found (row/col not updated), the puzzle is solved
    if(row == -1 || col == -1){
    	return true;
    }

    // For cells with 2 values, set which to 0 if the first value of the pair in that cell is 0
    // Set which to 1 otherwise (meaning the second value of our pair is 0)
    if(grid[row][col].two_vals == true){
    	if(grid[row][col].vals.first == 0){
    		which = 0;
    	} else {
    		which = 1;
    	}
    }

    // Iterate through all possible values to place in cell (1-9)
    // Recursively solve next cell
    for(int choice = 1; choice < 10; choice++){
    	if(valid_entry(row, col, choice)){
    		if(which == 0 || which == -1){
    			grid[row][col].vals.first = choice;
    		}
    		if(which == 1){
    			grid[row][col].vals.second = choice;
    		}

        	if(Solve()){
          		return true;
        	}
      	}

      	// Setting the correct value in 2-value cell back to 0
      	if(which == 0 || which == -1){
    		grid[row][col].vals.first = 0;
    	}
    	if(which == 1){
    		grid[row][col].vals.second = 0;
    	}
    }
    // If none of the values work at current (row, col), backtrack.
    return false;
}

/**
  @brief Locates unsolved cell in puzzle (one that contains a 0)

  @param r row to be updated to row index of unsolved cell
  @param c column to be updated  to column index of unsolved cell
*/
void Sudoku::locate_unsolved(int & r, int & c){
	for(int i = 0; i < 6; ++i){
		for(int j = 0; j < 6; ++j){
			if(grid[i][j].two_vals == true){
				if((grid[i][j]).vals.first == 0 || (grid[i][j]).vals.second == 0){
					r = i;
					c = j;
					return;
				}
			} else {
				if((grid[i][j]).vals.first == 0){
					r = i;
					c = j;
					return;
				}
			}
		}
	}
}

/**
  @brief Determines if value would be valid in given row

  @param r the row to inspect
  @param val value to look for
  @return bool true if value isn't already in row, false otherwise
*/
bool Sudoku::valid_row(int r, int val){
	for(int i = 0; i < 6; ++i){
		if(grid[r][i].vals.first == val || grid[r][i].vals.second == val){
			return false;
		}
	}
	return true;
}

/**
  @brief Determines if value would be valid in given column

  @param c the column to inspect
  @param val value to look for
  @return bool true if value isn't already in column, false otherwise
*/
bool Sudoku::valid_col(int c, int val){
	for(int i = 0; i < 6; ++i){
		if(grid[i][c].vals.first == val || grid[i][c].vals.second == val){
			return false;
		}
	}
	return true;  
}

/**
  @brief Determines if value would be valid in given sub-box (calculated from r and c)

  @param r row of the cell being inspected
  @param c column of the cell being inspected
  @return bool true if value isn't already in sub-box, false otherwise
*/
bool Sudoku::valid_box(int r, int c, int val){
	// Determining boundaries for sub-box given the row and col of cell
	int b_r = 2 * (r / 2);
	int b_c = 3 * (c / 3);
	for(int i = b_r; i < b_r + 2; i++){
		for(int j = b_c; j < b_c + 3; j++){
			if(grid[i][j].vals.first == val || grid[i][j].vals.second == val){
				return false;
			}
		}
	}
	return true;
}

/**
  @brief Checks that value satisfies all rules of Sudoku before being placed in puzzle at given row and column

  @param r row to check val
  @param c column to check val
  @param val value to check in row, column, and sub-box
  @return true if value satisfies all rules, false otherwise
*/
bool Sudoku::valid_entry(int r, int c, int val){
    return valid_row(r, val) && valid_col(c, val) && valid_box(r, c, val);
}

/**
  @brief Friend function for printing Sudoku puzzle

  @param out osteam
  @sdku Sudoku object
  @return ostream
*/std::ostream & operator<<(std::ostream & out, Sudoku & sdku){
	for(std::vector<std::vector<Sudoku::Cell> >::iterator it = sdku.grid.begin(); it != sdku.grid.end(); ++it){
		//it is a pointer to a vector<Cell>
		for(std::vector<Sudoku::Cell>::iterator jt = it->begin(); jt != it->end(); ++jt){
			// jt is a pointer to a Cell.
			if((*jt).two_vals == true){
				out << (*jt).vals.first << "/" << (*jt).vals.second;
			} else {
				out << (*jt).vals.first;
			}

			if(jt != it->end() - 1){
				out << " ";
			}
		}
		out << std::endl;
	}
	return out; 
}

/**
  @brief Saves Sudoku puzzle to file

  @param outfile File to save puzzle to
*/
void Sudoku::Save(std::string outfile){
	std::ofstream outstream(outfile, std::ofstream::out);
  	
	for(int i = 0; i < 6; ++i){
		for(int j = 0; j < 6; ++j){
			if(grid[i][j].two_vals){
				outstream << grid[i][j].vals.first << "/" << grid[i][j].vals.second;
			} else {
				outstream << grid[i][j].vals.first;
			}
			if(j <= 4){
				outstream << " ";
			}
		}
		outstream << std::endl;
	}
}
