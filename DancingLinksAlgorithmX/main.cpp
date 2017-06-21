//
//  main.cpp
//  DancingLinksAlgorithmX
//
//  Created by Zixuan Zhao on 13/6/2017.
//  Copyright © 2017 Zixuan Zhao. All rights reserved.
//

#include <iostream>
#include "SudokuSolver.hpp"
#include "NQueens.hpp"

void testExactCoverProblem(std::vector<std::vector<int> >& sparse_input, int col, bool oneSol = false){
    auto cm = ConstraintMatrix((int)sparse_input.size(), col, sparse_input);
    auto p = AlgorithmX(&cm,oneSol);
    p.solve();
    p.printSol();
}


void testSudoku(std::string board[9], bool findAllSol = false){
    auto s = SudokuSolver(board,findAllSol);
    s.solve();
    s.printSol();
}

void testNQueen(int n){
    auto nq = NQueens(n);
    nq.solve();
    std::cout<<"Num of sols for "<<n<<" queen: "<<nq.getNSols()<<std::endl;
    nq.printFullSols(true);
}

int main(int argc, const char * argv[]) {
    std::vector<std::vector<int> > sparse_input;
    
    //knuth's example in his paper
    sparse_input = {{2,4,5},{0,3,6},{1,2,5},{0,3},{1,6},{3,4,6}};
    testExactCoverProblem(sparse_input, 7);
    
    //multiple solution example, displaying one solution
    sparse_input={{0,2,4,6},{1,3,5},{0,2,4,6},{1,3,5},{},{0}};
    testExactCoverProblem(sparse_input, 7, true);
    
    //example from leetcode
    std::string board1[9] = {"..9748...","7........",".2.1.9...","..7...24.",".64.1.59.",".98...3..","...8.3.2.","........6","...2759.."};
    testSudoku(board1);
    
    //one said to be a most difficult sudoku
    std::string board2[9] = {"8........","..36.....",".7..9.2..",".5...7...","....457..","...1...3.","..1....68","..85...1.",".9....4.."};
    testSudoku(board2);
    
    //check for # of sols for nqueen problem, and prints an example sol
    testNQueen(8);
    
    return 0;
}
