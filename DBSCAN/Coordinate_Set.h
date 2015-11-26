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
    float axis_data;
    float *point = NULL;

public:
    
    float cut_val_left, cut_val_right; //cut value
    
    float *lower, *upper;//[min, max] of the box enclosing all points
    
    //left, right for child //parent for Disjoint set //next for Coordinate set
    Coordinate *left = NULL, *right = NULL, *parent = NULL, *next = NULL;
    
    
    void set_lower_and_upper_bound();
    //set lower and upper bound of sub tree
    
    void search(Coordinate_Set *container, Coordinate *query, float radius);
    // recursive innert ost cor routine for searching..
    
    void process_leaf_node_fixed_sphere(Coordinate_Set *container, Coordinate *query, float radius);
    
    bool box_in_search_range(Coordinate *query, float radius);
    // return true if the bounding vox for this node is within the
    // search range giveb by the searchvector and maximum ballsize in 'sr'.
    
};

//skip list of Coordinate. cuz skip list is very easy but also powerful data structure
class Coordinate_Set
{
public:
    Coordinate_Set(int dimension);
    ~Coordinate_Set();
    
    // add one new element to the list of results
    void push_element(Coordinate *data);
    
    void quick_sort(int num_of_element);
    
    void qsort_recur(int start, int end);
    
    //print all element in Coordinate_Set in ID order.
    void print();
    
    //
    Coordinate *head;

    
    //quicksort
    Coordinate **quick_container;
    
    
    int dimension;
    int num_of_element;
};

#endif /* Coordinate_Set_h */
