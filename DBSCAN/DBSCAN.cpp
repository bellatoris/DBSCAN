//
//  DBSCAN.cpp
//  DBSCAN
//
//  Created by Doogie's mac on 2015. 11. 27..
//  Copyright © 2015년 Doogie's mac. All rights reserved.
//

#include "DBSCAN.h"




DBSCAN::DBSCAN(KD_Tree &kd_tree, float epsilon, int minPoints)
{
    kdt = &kd_tree;
    dummy = new Coordinate();
    for(int i = 0; i < kd_tree.num_of_ponint; i++)
    {
        //check if it is NULL
        if(kd_tree.dataset[i])
        {
            kd_tree.dataset[i]->parent = kd_tree.dataset[i];
            kd_tree.dataset[i]->rank = 1;
            //set core_or_member = -1 --> this point is not core and member of cluster
            kd_tree.dataset[i]->core_or_member = -1;
        }
    }
    //need to modify UNION and Find_Set
    for(int i = 0; i < kd_tree.num_of_ponint; i++)
    {
        if(kd_tree.dataset[i])
        {
            cSet = kd_tree.getNeighbors(*kd_tree.dataset[i], epsilon);
            if(cSet->num_of_neighbor >= minPoints)
            {
                //dataset[i] is core
                kd_tree.dataset[i]->core_or_member = 1;
                Coordinate *ctemp = cSet->head->next;
                for(int j = 0; j < cSet->num_of_neighbor; j++)
                {
                    if(ctemp->core_or_member)
                        UNION(kd_tree.dataset[i]->parent, ctemp);
                    else if(ctemp->parent != kd_tree.dataset[i] && ctemp->core_or_member == -1)
                    {
                        UNION(kd_tree.dataset[i], ctemp);
                        //mark that ctemp is member of cluster
                        ctemp->core_or_member = 0;
                    }
                    ctemp = ctemp->next;
                }
            }
            delete cSet;
        }
    }
}

DBSCAN::~DBSCAN()
{
    if(dummy)
    {
        if(dummy->left)
            dummy->left = NULL;
        delete  dummy;
    }
}

void DBSCAN::run()
{
    Coordinate *temp;
    Coordinate *temp_array[kdt->num_of_ponint];
    int n = 0;
    for(int i = 0; i < kdt->num_of_ponint; i++)
    {
        if(kdt->dataset[i])
        {
            temp_array[n++] = kdt->dataset[i];
        }
    }

    for(int i = 0; i < n; i++)
    {
        quick_sort(temp_array, n);
        cout << temp_array[i]->ID << ": ";
        if(temp_array[i]->parent == temp_array[i] && temp_array[i]->core_or_member == -1)
            cout << "-1" << endl;
        else
        {
            temp = temp_array[i];
            while(temp->parent != temp)
                temp = temp->parent;
            cout << temp->ID << endl;
            temp = NULL;
        }
    }
}



void DBSCAN::UNION(Coordinate *core, Coordinate *point)
{
    Coordinate *u = Find_Set(core);
    Coordinate *v = Find_Set(point);
    
    if(u->rank == v->rank)
    {
        u->rank++;
        v->parent = u;
    }
    else if(u->rank > v->rank)
    {
        v->parent = u;
    }
    else
    {
        u->parent = v;
    }
}


Coordinate* DBSCAN::Find_Set(Coordinate* point)
{
    int num = 0;
    Coordinate *u = point;
    while(u->parent != u)
    {
        u->left = dummy->left;
        dummy->left = u;
        num++;
        u = u->parent;
    }
    Coordinate *temp = dummy->left;
    Coordinate *ltemp;
    if(temp)
    {
        for(int i = 0; i < num; i++)
        {
            ltemp = temp;
            temp->parent = u;
            temp = temp->left;
            ltemp->left = NULL;
        }
    }
    dummy->left = NULL;
    return u;
}
