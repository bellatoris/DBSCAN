

//
//  Coordinate_Set.cpp
//  DBSCAN
//
//  Created by Doogie's mac on 2015. 11. 25..
//  Copyright © 2015년 Doogie's mac. All rights reserved.
//

#include "median_finding.h"
#include <algorithm>

//utility
inline float squared(const float x)
{
    return (x*x);
}


//class Coordinate
Coordinate::Coordinate()
{
}

Coordinate::Coordinate(int dimension):dimension(dimension)
{
    lower = new float[dimension];
    upper = new float[dimension];
}

Coordinate::~Coordinate()
{
    if(left)
    {
        delete left;
    }
    if(right)
    {
        delete right;
    }
    if(lower)
    {
        delete []lower;
    }
    if(upper)
    {
        delete []upper;
    }
}

void Coordinate::set_lower_and_upper_bound()
{
    if(!right && left)
    {
        for(int i = 0; i < dimension; i++)
        {
            upper[i] = left->upper[i];
            lower[i] = left->lower[i];
        }
        cut_val_right = cut_val_left = axis_data;
    }
    else if(!left && right)
    {
        for(int i = 0; i < dimension; i++)
        {
            upper[i] = right->upper[i];
            lower[i] = right->lower[i];
        }
        cut_val_right = cut_val_left = axis_data;
    }
    else if(right && left)
    {
        cut_val_right = right->lower[ref_axis];
        cut_val_left = left->upper[ref_axis];
        //
        // now recompute true bounding box as union of subtree boxes.
        // This is now faster having built the tree, being logarithmic in
        // N, not linear as would be from naive method.
        //
        for(int i = 0; i < dimension; i++)
        {
            upper[i] = std::max(left->upper[i], right->upper[i]);
            lower[i] = std::min(left->lower[i], right->lower[i]);
        }
    }
    return;
}


void Coordinate::search(Coordinate_Set *container, Coordinate &query, float epslion)
// the core search routine.
// This uses true distance to bounding box as the
// criterion to search the secondary node.
//
// This results in somewhat fewer searches of the secondary nodes
// than 'search', which uses the vdiff vector,  but as this
// takes more computational time, the overall performance may not
// be improved in actual run time.
//
{
    if(!left && !right)
        //we are on a leaf node
    {
        process_leaf_node_fixed_sphere(container, query, epslion);
    }
    else
    {
        Coordinate *ncloser, *nfarther;
        
        float extra;
        float qval = query.point[ref_axis];
        // value of the wall boundary on the cut dimension.
        //        float left_extra, right_extra;
        //        left_extra = qval - cut_val_left;
        //        right_extra = cut_val_right - qval;
        //
        //        if(left && squared(left_extra) < squared(epslion))
        //        {
        //            if(left->box_in_search_range(query, epslion))
        //                left->search(container, query, epslion);
        //        }
        //
        //        if(right && squared(right_extra) < squared(epslion))
        //        {
        //            if(right->box_in_search_range(query, epslion))
        //                right->search(container, query, epslion);
        //        }
        
        if (qval <= axis_data)
        {
            ncloser = left;
            nfarther = right;
            extra = cut_val_right-qval;
        }
        else
        {
            ncloser = right;
            nfarther = left;
            extra = qval-cut_val_left;
        }
        
        if (ncloser != NULL)
            ncloser->search(container, query, epslion);
        
        if ((nfarther != NULL) && (squared(extra) <= squared(epslion)))
        {
            // first cut
            if (nfarther->box_in_search_range(query, epslion))
            {
                nfarther->search(container, query, epslion);
            }
        }
    }
}

void Coordinate::process_leaf_node_fixed_sphere(Coordinate_Set *container, Coordinate &query, float epslion)
{
    float sum = 0;
    for(int i = 0; i < dimension; i++)
    {
        sum += squared(point[i] - query.point[i]);
        if(sum > squared(epslion))
            return;
    }
    if(sum)
        container->push_element(this);
}

inline float dis_from_bnd(float x, float amin, float amax)
{
    if(x > amax)
    {
        return(x - amax);
    }
    else if (x < amin)
    {
        return (amin - x);
    }
    else
        return 0;
}

inline bool Coordinate::box_in_search_range(Coordinate &query, float epslion)
{
    float dis2 = 0;
    for(int i = 0; i < dimension; i++)
    {
        dis2 += squared(dis_from_bnd(query.point[i], lower[i], upper[i]));
        if(dis2 > squared(epslion))
            return false;
    }
    return true;
}







Coordinate_Set::Coordinate_Set():num_of_neighbor(0)
{
    head = new Coordinate();
}

Coordinate_Set::~Coordinate_Set()
{
    if(head)
    {
        if(head->next)
            head->next = NULL;
        delete head;
    }
}


void Coordinate_Set::push_element(Coordinate *data)
{
    data->next = head->next;
    head->next = data;
    num_of_neighbor++;
}



void Coordinate_Set::print()
{
    Coordinate *temp = head->next;
    //for negihbor sort by ID
    Coordinate **quick_container = new Coordinate*[num_of_neighbor];
    if(temp)
    {
        int dimension = temp->dimension;
        for(int i = 0; i < num_of_neighbor; i++)
        {
            quick_container[i] = temp;
            temp = temp->next;
        }
        quick_sort(quick_container, num_of_neighbor);
        for(int i = 0; i < num_of_neighbor; i++)
        {
            std::cout << quick_container[i]->ID <<"\t(";
            for(int j = 0; j < dimension - 1; j++)
            {
                std::cout << quick_container[i]->point[j] << ", ";
            }
            std::cout << quick_container[i]->point[dimension - 1] << ")\n";
        }
    }
    delete [] quick_container;
}






