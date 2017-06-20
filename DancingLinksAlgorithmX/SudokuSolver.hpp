//
//  SudokuSolver.hpp
//  DancingLinksAlgorithmX
//
//  Created by Zixuan Zhao on 20/6/2017.
//  Copyright © 2017 Zixuan Zhao. All rights reserved.
//

#ifndef SudokuSolver_hpp
#define SudokuSolver_hpp

#include "AlgorithmX.hpp"

class SudokuSolver{
    char board[9][9];
    bool findMultipleSols;
    ConstraintMatrix* convertedMatrix;
    AlgorithmX* convertedProblem;
    //solution required to be of this form
    std::vector<std::vector<std::vector<char> > > sols;
    bool solved = 0;
public:
    SudokuSolver(char board[9][9], bool findMultipleSols = false);
    SudokuSolver(std::vector<std::vector<char> > board, bool findMultipleSols = false);
    void solve();
    std::vector<std::vector<std::vector<char> > >* getSolutions();
    void printSol();
private:
    void convertToSparseMarix(char board[9][9]);
    void convertFromSparseMarix();
    
};

#endif /* SudokuSolver_hpp */
