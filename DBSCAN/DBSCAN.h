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
    
    //Union & find method are included in DBSCAN
    void UNION(Coordinate *core, Coordinate *point);
    Coordinate* Find_Set(Coordinate* point);

public:
    //for run
    KD_Tree *kdt = NULL;
    Coordinate *dummy = NULL;
};


#endif /* DBSCAN_h */
