//
//  DBSCAN.h
//  DBSCAN
//
//  Created by Doogie's mac on 2015. 11. 27..
//  Copyright © 2015년 Doogie's mac. All rights reserved.
//

#ifndef DBSCAN_h
#define DBSCAN_h

#include "KD_Tree.h"

class DBSCAN
{
public:
    DBSCAN(KD_Tree &kd_tree, float epsilon, int minPoints);
    ~DBSCAN();
    
    void run();
    
    Coordinate_Set cSet;
    KD_Tree *kdt;
};


#endif /* DBSCAN_h */