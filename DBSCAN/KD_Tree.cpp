//
//  KD_Tree.cpp
//  DBSCAN
//
//  Created by Doogie's mac on 2015. 11. 25..
//  Copyright © 2015년 Doogie's mac. All rights reserved.
//

#include "KD_Tree.h"

KD_Tree::KD_Tree(float **points, int dimension, int numOfPoints)
{
    int depth = 0;
    for(int i = 0; i < numOfPoints; i++)
    {
        dataset[i] = new Coordinate();
        dataset[i]->ID = i;
        dataset[i]->point = points[i];
    }
    while(1)
    {
        depth++%dimension;
    }
    
}
KD_Tree::~KD_Tree()
{
}

Coordinate_Set KD_Tree::getNeighbors(Coordinate querypoint, float radius)
{
    Coordinate_Set x;
    return x;
}