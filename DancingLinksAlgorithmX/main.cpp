//
//  main.cpp
//  DancingLinksAlgorithmX
//
//  Created by Zixuan Zhao on 13/6/2017.
//  Copyright © 2017 Zixuan Zhao. All rights reserved.
//

#include <iostream>
#include "AlgorithmX.hpp"



int main(int argc, const char * argv[]) {
    // insert code here...
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

    return 0;
}
