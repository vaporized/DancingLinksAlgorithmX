//
//  AlgorithmX.cpp
//  DancingLinksAlgorithmX
//
//  Created by Zixuan Zhao on 20/6/2017.
//  Copyright © 2017 Zixuan Zhao. All rights reserved.
//

#include "AlgorithmX.hpp"

AlgorithmX::AlgorithmX(ConstraintMatrix* problem, bool oneSolution):problem(problem),oneSolution(oneSolution){
    //pass
}

void AlgorithmX::search(int k, std::vector<Node*>& curSol){
    if (solved&&oneSolution) return;
    if (problem->root->right==problem->root){
        solutions.push_back(curSol);
        solved = 1;
        ++nSols;
        return;
    }

    //find column with lease size
    Column* toCover = 0;
    int size = INT_MAX;
    Node* it = problem->root->right;
    while (it != problem->root) {
        if (it->col->size < size){
            size = it->col->size;
            toCover = it->col;
        }
        it = it->right;
    }

    if (size==0) return;

    problem->CoverColumn(toCover);

    Node* col_it = toCover->header->down;
    if (curSol.size() < k+1) curSol.push_back(0);
    while(col_it != toCover->header){

        curSol[k] = col_it;
        Node* row_it = col_it->right;
        while (row_it != col_it) {
            problem->CoverColumn(row_it->col);
            row_it = row_it->right;
        }

        search(k+1, curSol);

        //col_it = curSol[k];
        //toCover = col_it->col;

        row_it = col_it->left;
        while (row_it != col_it) {
            problem->UncoverColumn(row_it->col);
            row_it = row_it->left;
        }


        col_it = col_it->down;
    }

    problem->UncoverColumn(toCover);

}

void AlgorithmX::solve(){
    std::vector<Node*> curSol;
    search(0, curSol);
    nSols = (int)solutions.size();
    solved = 1;
}

std::vector<std::vector<Node*> >* AlgorithmX::getRawSol(){
    if (solved){
        return &solutions;
    }else{
        std::cout<<"Please solve the problem first."<<std::endl;
        return 0;
    }
}

void AlgorithmX::constructSparseSol(){
    if (nSols==0) return;
    for (auto sol:solutions){
        std::vector<std::vector<int> > sparseSol;
        for (auto col_it:sol){
            std::vector<int> row;
            row.push_back(col_it->col->index);
            auto elem = col_it->right;
            while(elem != col_it){
                row.push_back(elem->col->index);
                elem = elem->right;
            }
            sparseSol.push_back(row);
        }
        sparseSols.push_back(sparseSol);
    }
}

std::vector<std::vector<std::vector<int> > >* AlgorithmX::getSparseSol(){
    if (solved){
        if (sparseSols.empty())
            constructSparseSol();
        return &sparseSols;
    }else{
        std::cout<<"Please solve the problem first."<<std::endl;
        return 0;
    }
}

void AlgorithmX::constructFullSol(){
    if (nSols==0) return;
    if (sparseSols.empty())
        constructSparseSol();
    for (auto sol:sparseSols){
        std::vector<std::vector<bool> > fullSol;
        for (auto col:sol){
            std::vector<bool> row(problem->nCols,0);
            for (auto elem: col)
                row[elem] = 1;
            fullSol.push_back(row);
        }
        fullSols.push_back(fullSol);
    }
}

std::vector<std::vector<std::vector<bool> > >* AlgorithmX::getFullSol(){
    if (solved){
        if (fullSols.empty())
            constructFullSol();
        return &fullSols;
    }else{
        std::cout<<"Please solve the problem first."<<std::endl;
        return 0;
    }
}

void AlgorithmX::printSparseSol(){
    if(!solved){
        std::cout<<"Please solve the problem first."<<std::endl;
        return;
    }
    if (nSols==0){
        std::cout<<"No solution."<<std::endl;
        return;
    }
    if (sparseSols.empty())
        constructSparseSol();
    for (auto solution:sparseSols){
        for (auto row: solution){
            for (auto elem: row){
                std::cout<<elem<<" ";
            }
            std::cout<<std::endl;
        }
        std::cout<<std::endl;
    }


}

void AlgorithmX::printSol(){
    if(!solved){
        std::cout<<"Please solve the problem first."<<std::endl;
        return;
    }
    if (nSols==0){
        std::cout<<"No solution."<<std::endl;
        return;
    }
    if (fullSols.empty())
        constructFullSol();
    for (auto solution:fullSols){
        for (auto row: solution){
            for (auto elem: row){
                std::cout<<elem;
            }
            std::cout<<std::endl;
        }
        std::cout<<std::endl;
    }

}
