//
//  main.cpp
//  DancingLinksAlgorithmX
//
//  Created by Zixuan Zhao on 13/6/2017.
//  Copyright © 2017 Zixuan Zhao. All rights reserved.
//

#include <iostream>
#include "SudokuSolver.hpp"

void test1(){
    std::vector<std::vector<int> > sparse_input;
    std::vector<int> row1 = {2,4,5};
    std::vector<int> row2 = {0,3,6};
    std::vector<int> row3 = {1,2,5};
    std::vector<int> row4 = {0,3};
    std::vector<int> row5 = {1,6};
    std::vector<int> row6 = {3,4,6};
    sparse_input.push_back(row1);
    sparse_input.push_back(row2);
    sparse_input.push_back(row3);
    sparse_input.push_back(row4);
    sparse_input.push_back(row5);
    sparse_input.push_back(row6);
    auto cm = ConstraintMatrix(6, 7, sparse_input);
    auto p = AlgorithmX(&cm);
    p.solve();
    p.printSol();
}

void test2(){
    std::vector<std::vector<int> > sparse_input;
    std::vector<int> row1 = {0,2,4,6};
    std::vector<int> row2 = {1,3,5};
    std::vector<int> row3 = {0,2,4,6};
    std::vector<int> row4 = {1,3,5};
    std::vector<int> row5 = {0};
    std::vector<int> row6 = {0};
    sparse_input.push_back(row1);
    sparse_input.push_back(row2);
    sparse_input.push_back(row3);
    sparse_input.push_back(row4);
    sparse_input.push_back(row5);
    sparse_input.push_back(row6);
    auto cm = ConstraintMatrix(6, 7, sparse_input);
    auto p = AlgorithmX(&cm,true);
    p.solve();
    p.printSol();
}

void test3(){
    std::string _board[9] = {"..9748...","7........",".2.1.9...","..7...24.",".64.1.59.",".98...3..","...8.3.2.","........6","...2759.."};
    char board[9][9];
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            board[i][j] = _board[i][j];
        }
    }
    auto s = SudokuSolver(board);
    s.solve();
    s.printSol();
    
}


int main(int argc, const char * argv[]) {
    test1();
    test2();
    test3();
    return 0;
}
