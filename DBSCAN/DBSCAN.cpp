//
//  DBSCAN.cpp
//  DBSCAN
//
//  Created by Doogie's mac on 2015. 11. 27..
//  Copyright © 2015년 Doogie's mac. All rights reserved.
//

#include "DBSCAN.h"

DBSCAN::DBSCAN(KD_Tree &kd_tree, float epsilon, int minPoints): cSet(kd_tree.dimension)
{
    kdt = &kd_tree;
    for(int i = 0; i < kd_tree.num_of_ponint; i++)
    {
        kd_tree.dataset[i]->parent = kd_tree.dataset[i];
        kd_tree.dataset[i]->rank = 1;
        kd_tree.dataset[i]->core = false;
    }
    
    for(int i = 0; i < kd_tree.num_of_ponint; i++)
    {
        cSet = kd_tree.getNeighbors(*kd_tree.dataset[i], epsilon);
        if(cSet.num_of_element >= minPoints)
        {
            kd_tree.dataset[i]->core = true;
            Coordinate *ctemp = cSet.head->next;
            for(int j = 0; j < cSet.num_of_element; j++)
            {
                if(ctemp->core)
                    cSet.UNION(kd_tree.dataset[i], ctemp);
                else if(ctemp->parent != kd_tree.dataset[i])
                {
                    cSet.UNION(kd_tree.dataset[i], ctemp);
                }
                ctemp = ctemp->next;
            }
        }
    }
}

DBSCAN::~DBSCAN()
{
    
}

void DBSCAN::run()
{
    for(int i = 0; i < kdt->num_of_ponint; i++)
    {
        cout << i << ": ";
        quick_sort(kdt->dataset, kdt->num_of_ponint);
        if(kdt->dataset[i]->parent == kdt->dataset[i] && !kdt->dataset[i]->core)
            cout << "-1" << endl;
        else
            cout << kdt->dataset[i]->parent->ID << endl;
    }
}
