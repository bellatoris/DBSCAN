//
//  KD_Tree.cpp
//  DBSCAN
//
//  Created by Doogie's mac on 2015. 11. 25..
//  Copyright © 2015년 Doogie's mac. All rights reserved.
//

#include "KD_Tree.h"

inline bool same_array(float *array1, float* array2, int dimension)
{
    for(int i = 0; i < dimension; i++)
    {
        if(array1[i] != array2[i])
            return false;
    }
    return true;
}


KD_Tree::KD_Tree(float **points, int dimension, int numOfPoints): dimension(dimension), num_of_ponint(numOfPoints)
{
    int depth = 0;
    dataset = new Coordinate*[numOfPoints];
    for(int i = 0; i < numOfPoints; i++)
    {
        dataset[i] = new Coordinate(dimension);
        dataset[i]->ID = i;
        dataset[i]->point = points[i];
        for(int j = 0; j < dimension; j++)
        {
            dataset[i]->upper[j] = dataset[i]->point[j];
            dataset[i]->lower[j] = dataset[i]->point[j];
        }
    }
    root = Build_KD_Tree(dataset, 0, numOfPoints - 1, depth, dimension);
}

KD_Tree::~KD_Tree()
{
    if(root)
        delete root;
    
    if(dataset)
    {
        delete []dataset;
    }
}

Coordinate* KD_Tree::Build_KD_Tree(Coordinate **dataset, int left, int right, int depth, int dimension)
{
    if(!(left < right))
    {
        return dataset[left];
    }
   //code optimization and same value problem remain
    else
    {
        Coordinate *temp = new Coordinate(dimension);
        //split point. i think it will be good to make this by using constructor
        temp->axis_data = dataset[median_finding(dataset, depth%dimension, left, right, left + (right - left)/2)]->point[depth%dimension];
        temp->ref_axis = depth%dimension;
        temp->depth = depth;

//        //for that median data is duplicate data
        int i = 1;
        //find real split point that has median data
        while(left + (right - left)/2 + i <= right)
        {
            if(dataset[left+(right-left)/2]->point[depth%dimension] < dataset[left + (right - left)/2 + i]->point[depth%dimension])
                break;
            i++;
        }
        //if split point is right ---> no split
        if(left + (right -left)/2 + (i - 1) == right)
        {
            //this case is rare, therefore searching all dimension will be not cost much
            int storeIndex = left;
            //discard same point
            while((i - 1) >= 0)
            {
                for(int j = storeIndex; j < left + (right - left)/2 + (i - 1); j++)
                {
                    if(same_array(dataset[j]->point, dataset[left + (right -left)/2 + (i - 1)]->point, dimension))
                    {
                        swap(dataset[storeIndex++], dataset[j]);
                        delete dataset[storeIndex - 1];
                        dataset[storeIndex - 1] = NULL;
                    }
                }
                i--;
            }
            if(storeIndex == right)
                temp->left = dataset[right];
//            else if(storeIndex + 1 == right)
//            {
//                temp->left = dataset[storeIndex];
//                temp->right = dataset[right];
//            }
            else
            {
                temp->left = Build_KD_Tree(dataset, storeIndex, storeIndex + (right - storeIndex)/2, depth + 1, dimension);
                temp->right = Build_KD_Tree(dataset, storeIndex + (right - storeIndex)/2 + 1, right, depth + 1, dimension);
            }
        }
        else
        {
            temp->left = Build_KD_Tree(dataset, left, left + (right - left)/2 + (i - 1), depth + 1, dimension);
            temp->right = Build_KD_Tree(dataset, left + (right - left)/2 + i, right, depth + 1, dimension);
        }
//        temp->left = Build_KD_Tree(dataset, left, left + (right - left)/2 , depth + 1, dimension);
//        temp->right = Build_KD_Tree(dataset, left + (right - left)/2 + 1, right, depth + 1, dimension);

        temp->set_lower_and_upper_bound();
        
        return temp;
    }
}


Coordinate_Set* KD_Tree::getNeighbors(Coordinate &querypoint, float epslion)
{
    Coordinate_Set *container = new Coordinate_Set();

    root->search(container, querypoint, epslion);
    
    return container;
}



