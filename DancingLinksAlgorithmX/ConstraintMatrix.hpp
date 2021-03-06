//
//  ConstraintMatrix.hpp
//  DancingLinksAlgorithmX
//
//  Created by Zixuan Zhao on 13/6/2017.
//  Copyright © 2017 Zixuan Zhao. All rights reserved.
//

#ifndef ConstraintMatrix_hpp
#define ConstraintMatrix_hpp


#include <iostream>
#include <vector>

struct Node;
struct Column;

class ConstraintMatrix{
    Column* columns;
public:
    Node* root;

    int nRows;
    int nCols;
    int secondaryCols;
    ConstraintMatrix(int nRows, int nCols, std::vector<std::vector<int> > coords, int secondaryCols = 0);
    void CoverColumn(Column* col);
    void UncoverColumn(Column* col);

private:
    void addNewRow(std::vector<int> row, int rowIdx);
};

struct Node{
    Node* left;
    Node* right;
    Node* up;
    Node* down;
    Column* col;
    int rowIdx;
};

struct Column{
    Node* header;
    int size;
    std::string name;
    int index;
};

#endif /* ConstraintMatrix_hpp */
