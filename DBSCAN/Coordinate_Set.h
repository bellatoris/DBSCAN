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

class Coordinate
{
public:
    Coordinate();
    ~Coordinate();
    
    int ID;
    int depth;
    float parent_data;
    float *point;
    Coordinate *next;
};

class Coordinate_Set
{
public:
    Coordinate_Set();
    ~Coordinate_Set();
    void print();
};

#endif /* Coordinate_Set_h */
