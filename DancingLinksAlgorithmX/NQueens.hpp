//
//  NQueens.hpp
//  DancingLinksAlgorithmX
//
//  Created by Zixuan Zhao on 21/6/2017.
//  Copyright © 2017 Zixuan Zhao. All rights reserved.
//

#ifndef NQueens_hpp
#define NQueens_hpp

#include "AlgorithmX.hpp"

class NQueens{
    int n;
    bool findMultipleSols;
    ConstraintMatrix* convertedMatrix;
    AlgorithmX* convertedProblem;
    //solution required to be of this form
    std::vector<std::vector<std::vector<bool> > > sols;
    bool solved = 0;
public:
    NQueens(int n, bool findMultipleSols  = true);
    void solve();
    int getNSols();
    std::vector<std::vector<std::vector<bool> > >* getFullSols();
    void printFullSols(bool printOnlyOne = true);
private:
    void convertToSparseMarix();
    void convertFromSparseMarix();
    
};

#endif /* NQueens_hpp */
