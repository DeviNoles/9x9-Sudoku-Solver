/**
 * @brief Sudoku class declaration, your implementation is up to you.
 */

#ifndef SUDOKU_H
#define SUDOKU_H

#include <fstream>
#include <string>
#include <vector>
#include <utility>

class Sudoku{

  private:
    // Cell struct to store data
    struct Cell{
        std::pair<int,int> vals;
        bool two_vals;
    };

    // 2-dimensional vector of Cells
    std::vector< std::vector<Cell> > grid;

    // Helper functions
    bool valid_col(int, int); 
    bool valid_row(int, int);
    bool valid_box(int, int, int);
    bool valid_entry(int, int, int);
    void locate_unsolved(int &, int &);

  public:
    Sudoku(std::string);
    bool Solve();
    void Save(std::string);
    friend std::ostream & operator<<(std::ostream &, Sudoku &);
};

#endif
