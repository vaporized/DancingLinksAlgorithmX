//
//  ConstraintMatrix.cpp
//  DancingLinksAlgorithmX
//
//  Created by Zixuan Zhao on 13/6/2017.
//  Copyright © 2017 Zixuan Zhao. All rights reserved.
//

#include "ConstraintMatrix.hpp"

ConstraintMatrix::ConstraintMatrix(int nRows, int nCols, std::vector<std::vector<int> > coords):nRows(nRows),nCols(nCols){

    //build column headers
    columns = new Column[nCols];
    for (auto i = 0; i < nCols; ++i) {
        //initialize headers
        columns[i].header = new Node;
    }
    root = new Node;
    //initialize column headers and the circular doubly linked list

    //build links between headers
    //headers in each column object points to headers in other columns
    for (auto i = 0; i < nCols - 1; ++i) {
        
        //horizontal doubly links
        columns[i].header->right = columns[i+1].header;
        columns[i+1].header->left = columns[i].header;
    }

    for (auto i = 0; i < nCols; ++i) {
        //vertical links for each column, only one object(header) exists in each columns now
        columns[i].size = 0;
        columns[i].header->up = columns[i].header;
        columns[i].header->down = columns[i].header;
        //fill header's column info
        columns[i].header->col = &columns[i];
        columns[i].index = i;
    }

    //link root into the row, and forms the horizontal circle
    root->right = columns[0].header;
    columns[0].header->left = root;

    root->left = columns[nCols-1].header;
    columns[nCols-1].header->right = root;

    //add rows
    for (auto row : coords)
        addNewRow(row);

}

void ConstraintMatrix::CoverColumn(Column* col){
    //remove header reference
    col->header->right->left = col->header->left;
    col->header->left->right = col->header->right;

    //iterate through elements of column
    auto col_it = col->header->down;
    while (col_it != col->header) {
        //iterate through each element of a row
        auto row_it = col_it->right;
        while (row_it != col_it) {
            //remove from column list
            row_it->down->up = row_it->up;
            row_it->up->down = row_it->down;

            //decrease counter
            --row_it->col->size;

            //next
            row_it = row_it->right;
        }

        //next
        col_it = col_it->down;
    }
}

void ConstraintMatrix::UncoverColumn(Column* col){
    //iterate through elements of column
    auto col_it = col->header->up;
    while (col_it != col->header) {
        //iterate through each element of a row
        auto row_it = col_it->left;
        while (row_it != col_it) {
            //add to column list
            row_it->down->up = row_it;
            row_it->up->down = row_it;

            //increase counter
            ++row_it->col->size;

            //next
            row_it = row_it->left;
        }

        //next
        col_it = col_it->up;
    }

    //add header reference
    col->header->right->left = col->header;
    col->header->left->right = col->header;
}

void ConstraintMatrix::addNewRow(std::vector<int> row_pos){

    auto rowSize = row_pos.size();
    if (rowSize==0) return;

    //create new nodes
    Node* row = new Node[rowSize];
    for (auto i = 0; i < rowSize; ++i) {
        //link into a horizontal circular doubly linked list
        row[i].right = &row[(i+1)%rowSize];
        row[(i+1)%rowSize].left = &row[i];
        //insert into columns
        auto prevLast = columns[row_pos[i]].header->up;

        columns[row_pos[i]].header->up = &row[i];
        prevLast->down = &row[i];

        row[i].up = prevLast;
        row[i].down = columns[row_pos[i]].header;

        //fill column info
        row[i].col = &columns[row_pos[i]];

        //update column size counters
        ++columns[row_pos[i]].size;

    }




}
