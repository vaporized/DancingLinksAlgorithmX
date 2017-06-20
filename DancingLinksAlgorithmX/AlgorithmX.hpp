//
//  AlgorithmX.hpp
//  DancingLinksAlgorithmX
//
//  Created by Zixuan Zhao on 20/6/2017.
//  Copyright © 2017 Zixuan Zhao. All rights reserved.
//

#ifndef AlgorithmX_hpp
#define AlgorithmX_hpp

#include "ConstraintMatrix.hpp"

class AlgorithmX{
    ConstraintMatrix* problem;
    std::vector<std::vector<Node*> > solutions;
    std::vector<std::vector<std::vector<int> > > sparseSols;
    std::vector<std::vector<std::vector<bool> > > fullSols;
    int nSols = 0;
    bool solved = false;
    bool oneSolution = false;
public:
    AlgorithmX(ConstraintMatrix* problem, bool oneSolution=false);
    void solve();
    std::vector<std::vector<Node*> >* getRawSol();
    std::vector<std::vector<std::vector<int> > >* getSparseSol();
    std::vector<std::vector<std::vector<bool> > >* getFullSol();
    void printSparseSol();
    void printSol();
private:
    void constructSparseSol();
    void constructFullSol();
    void search(int k, std::vector<Node*>& curSol);
};


#endif /* AlgorithmX_hpp */
