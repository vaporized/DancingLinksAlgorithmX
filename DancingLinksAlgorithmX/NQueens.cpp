//
//  NQueens.cpp
//  DancingLinksAlgorithmX
//
//  Created by Zixuan Zhao on 21/6/2017.
//  Copyright © 2017 Zixuan Zhao. All rights reserved.
//

#include "NQueens.hpp"

NQueens::NQueens(int n, bool findMultipleSols):n(n),findMultipleSols(findMultipleSols){
    convertToSparseMarix();
}

void NQueens::solve(){
    convertedProblem = new AlgorithmX(convertedMatrix, !findMultipleSols);
    convertedProblem->solve();
    solved=1;
}

int NQueens::getNSols(){
    if (!solved) {
        std::cout<<"Please solve the n queen first."<<std::endl;
        return 0;
    }
    return convertedProblem->nSols;
}

std::vector<std::vector<std::vector<bool> > >* NQueens::getFullSols(){
    if (!solved) {
        std::cout<<"Please solve the n queen first."<<std::endl;
        return 0;
    }
    if (sols.empty())
        convertFromSparseMarix();
    return &sols;
}

void NQueens::printFullSols(bool printOnlyOne){
    if (!solved) {
        std::cout<<"Please solve the n queen first."<<std::endl;
        return;
    }
    if (sols.empty())
        convertFromSparseMarix();
    for (auto sol: sols){
        for(auto row:sol){
            for (auto elem:row){
                std::cout<<elem;
            }
            std::cout<<std::endl;
        }
        std::cout<<std::endl;
        if (printOnlyOne) 
            break;
    }
}

void NQueens::convertToSparseMarix(){
    /*the n-queen problem has n*n possible entries, therefore is has n*n rows
     *there are four kinds of constraints:
     *row/column are primary constraints, forming 2*n columns
     *diagonal/reverse diagonal are secondary constraints, forming 2*(2*n-1) secondaru columns
     *
     *the mapping of columns and constraints:
     *rows: row_idx
     *columns: n + col_idx
     *diagonal: row_idx - col_idx + n-1 + 2*n
     *reverse diagonal: row_idx + col_idx  +2*n+2*n-1
     *total cols: 6*n-2, optional: 4*n-2
     */
    std::vector<std::vector<int>> sparse_matrix;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            std::vector<int> row;
            row.push_back(i);
            row.push_back(j + n);
            row.push_back(i-j+n-1 + 2*n);
            row.push_back(i+j + 2*n + 2*n-1);
            sparse_matrix.push_back(row);
        }
    }
    
    convertedMatrix = new ConstraintMatrix(n*n,6*n-2,sparse_matrix,4*n-2);
    
}

void NQueens::convertFromSparseMarix(){
    auto rawSols = convertedProblem->getRawSol();
    
    for (auto rawSol:*rawSols){
        auto sol = std::vector<std::vector<bool> >(n,std::vector<bool>(n,0));
        
        for (auto entry:rawSol){
            int info = entry->rowIdx;
            int i = info/n;
            int j = info%n;
            sol[i][j] = 1;
        }
        sols.push_back(sol);
    }
}
