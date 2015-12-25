//
//  Coordinate_Set.h
//  DBSCAN
//
//  Created by Doogie's mac on 2015. 11. 25..
//  Copyright © 2015년 Doogie's mac. All rights reserved.
//

#ifndef Coordinate_Set_h
#define Coordinate_Set_h

#include <iostream>

class Coordinate_Set;

//this is not only container for coordinate data of point but also kd_tree node
//so it has left child and right child
//ans so on it is disjoint set for DBSCAN
class Coordinate
{
public:
    // default constructor
    Coordinate();
    // constructor make lower and upper
    Coordinate(int dimension);
    // destructor
    ~Coordinate();
    
    //point ID
    int ID;
    
    
    //tree depth
    int depth;
    
    //point dimension
    int dimension;
    
    int ref_axis;
    //for internal vertex
    float axis_data;
    //for leaf
    float *point;
    
    //for disjoint set // if thie point is core then core_or_member = 1, else if this point is cluster member then core_or_member = 0
    int core_or_member;
    int rank;
    

public:
    
    float cut_val_left, cut_val_right; //cut value
    
    float *lower = NULL, *upper = NULL;//[min, max] of the box enclosing all points
    
    //left, right for child //parent for Disjoint set //next for Coordinate set
    Coordinate *left = NULL, *right = NULL, *parent = NULL, *next;
        
    
    void set_lower_and_upper_bound();
    //set lower and upper bound of sub tree
    
    void search(Coordinate_Set *container, Coordinate &query, float epslion);
    //recursive search algorithm
    
    void process_leaf_node_fixed_sphere(Coordinate_Set *container, Coordinate &query, float epslion);
    
    bool box_in_search_range(Coordinate &query, float epslion);
    // return true if the bounding box for this node is within the
    // search range given by the searchvector and maximum radius in 'epsilon'.
    
};

class Coordinate_Set
{
public:
    Coordinate_Set();
    ~Coordinate_Set();
    
    // add one new element to the list of results
    void push_element(Coordinate *data);
    
    //print all element in Coordinate_Set in ID order.
    void print();
    
    //for neighbor collecting
    Coordinate *head = NULL;
    
    //number of neighbor
    int num_of_neighbor;
};

#endif /* Coordinate_Set_h */
