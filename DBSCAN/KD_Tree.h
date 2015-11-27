//
//  KD_Tree.h
//  DBSCAN
//
//  Created by Doogie's mac on 2015. 11. 25..
//  Copyright © 2015년 Doogie's mac. All rights reserved.
//

#ifndef KD_Tree_h
#define KD_Tree_h

#include "median_finding.h"
#include "Coordinate_Set.h"

using namespace std;

class KD_Tree
{
// "dataset"is a multi array of the data to be included in the tree.
public:
    const int dimension;
    const int num_of_ponint;
    Coordinate **dataset;
    
    
public:
    //constructotr
    //data , dimension, number of data
    KD_Tree(float **points, int dimension, int numOfPoints);
    
    // destructor
    ~KD_Tree();
    
public:
    Coordinate_Set getNeighbors(Coordinate &querypoint, float epslion);
    // search for all neighbors in ball of size(square Euclidean distance)
    
    friend class Coordinate;
private:
    Coordinate *root;
    //build the tree
    Coordinate *Build_KD_Tree(Coordinate **dataset, int left, int right, int depth, int dimension);

};



#endif /* KD_Tree_h */
