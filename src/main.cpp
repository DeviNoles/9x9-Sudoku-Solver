/**
 * @brief Example driver program for class Sudoku
 */

#include <iostream>
#include "sudoku.hpp"

/**
 * @fn main
 * @brief Creates two unsolved Sudoku objects (from text files),
 *		  solves, and displays them
 */
int main(){
  Sudoku sdku0("tests/0_sudoku_grid.txt");
  std::cout << sdku0;
  sdku0.Solve();
  std::cout << "Solved" << std::endl;
  std::cout << sdku0;
  sdku0.Save("sdku0_sol.txt");

  std::cout << std::endl << std::endl;

  Sudoku sdku1("tests/1_sudoku_grid.txt");
  std::cout << sdku1;
  sdku1.Solve();
  std::cout << "Solved" << std::endl;
  std::cout << sdku1;
  sdku0.Save("sdku1_sol.txt");

  return 0;
}
