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

class KD_Tree
{
public:
    KD_Tree(float **points, int dimension, int numOfPoints);
    ~KD_Tree();
    Coordinate_Set getNeighbors(Coordinate querypoint, float radius);
    
    Coordinate **dataset;
};



#endif /* KD_Tree_h */
