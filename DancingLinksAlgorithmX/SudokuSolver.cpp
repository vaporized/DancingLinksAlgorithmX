//
//  SudokuSolver.cpp
//  DancingLinksAlgorithmX
//
//  Created by Zixuan Zhao on 20/6/2017.
//  Copyright © 2017 Zixuan Zhao. All rights reserved.
//

#include "SudokuSolver.hpp"
SudokuSolver::SudokuSolver(char _board[9][9], bool findMultipleSols):findMultipleSols(findMultipleSols){
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            board[i][j] = _board[i][j];
        }
    }
    convertToSparseMarix(board);
}

SudokuSolver::SudokuSolver(std::string _board[9], bool findMultipleSols):findMultipleSols(findMultipleSols){
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            board[i][j] = _board[i][j];
        }
    }
    convertToSparseMarix(board);
}

SudokuSolver::SudokuSolver(std::vector<std::vector<char> > _board, bool findMultipleSols):findMultipleSols(findMultipleSols){
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            board[i][j] = _board[i][j];
        }
    }
    convertToSparseMarix(board);
    
}

void SudokuSolver::convertToSparseMarix(char board[9][9]){
    /*for a 3*3 sudoku, there are 9*9*9 rows, 4*9*9 columns
     *columns represents constraints:
     * there are 9*boxes; 9*rows; 9*columns that should be exactly covered
     *rows represents the existence of a number in a position:
     * there are 9*9 positions, and 9 possibilities for each
     * each grid should contain exactly one element, this gives 81 positions
     */
    
    /*in the sparse matrix, 
     *the mapping of rows are board[i][j], with n as row[81*i+9*j+(n-1)]
     *the mapping of cols are
     *row: 9*row_idx + (n-1)
     *col: 81 + 9*col_idx + (n-1)
     *box: 81*2 + 9*box_idx + (n-1)
     *grid: 81*3 + 9*row_idx + 9*col_idx
     *where row_idx = i; col_idx = j; box_idx = i/3*3+j/3
     */
    std::vector<std::vector<int>> sparse_matrix;
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            if (board[i][j]=='.') {
                //all 9 numbers are candidates
                for (int n = 1; n <=9; ++n) {
                    std::vector<int> row;
                    row.push_back(9*i+n-1);
                    row.push_back(9*j+n-1 + 81);
                    row.push_back(9*(i/3*3+j/3)+n-1 + 81*2);
                    row.push_back(9*i+j+ 81*3);
                    sparse_matrix.push_back(row);
                }
                
            }else{
                //given some number
                int given = board[i][j] - '0';
                for (int n = 1; n <=9; ++n) {
                    if (n==given) {
                        std::vector<int> row;
                        row.push_back(9*i+n-1);
                        row.push_back(9*j+n-1 + 81);
                        row.push_back(9*(i/3*3+j/3)+n-1 + 81*2);
                        row.push_back(9*i+j+ 81*3);
                        sparse_matrix.push_back(row);
                    }else{
                        sparse_matrix.push_back(std::vector<int>());
                    }
                }
            }
        }
    }
    
    convertedMatrix = new ConstraintMatrix(9*9*9,4*9*9,sparse_matrix);
}

void SudokuSolver::solve(){
    convertedProblem = new AlgorithmX(convertedMatrix, !findMultipleSols);
    convertedProblem->solve();
    convertFromSparseMarix();
    solved=1;
}

void SudokuSolver::convertFromSparseMarix(){
    //convert the solution back
    auto rawSols = convertedProblem->getRawSol();
    
    for (auto rawSol:*rawSols){
        //initialize the vector 2d array
        auto sol = std::vector<std::vector<char> >(9,std::vector<char>(9,'0'));

        for (auto entry:rawSol){
            int info = entry->rowIdx;
            int i = info/81;
            int j = info/9%9;
            int n = info%9+1;
            sol[i][j] = n+'0';

        }
        sols.push_back(sol);
    }
}

std::vector<std::vector<std::vector<char> > >* SudokuSolver::getSolutions(){
    if (!solved) {
        std::cout<<"Please solve the sudoku first."<<std::endl;
        return 0;
    }
    return &sols;
}

void SudokuSolver::printSol(){
    if (!solved) {
        std::cout<<"Please solve the sudoku first."<<std::endl;
        return;
    }
    for (auto sol: sols){
        for(auto row:sol){
            for (auto elem:row){
                std::cout<<elem;
            }
            std::cout<<std::endl;
        }
        std::cout<<std::endl;
    }
}
