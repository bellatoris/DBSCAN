//
//  median_finding.cpp
//  DBSCAN
//
//  Created by Doogie's mac on 2015. 11. 25..
//  Copyright © 2015년 Doogie's mac. All rights reserved.
//

#include "median_finding.h"
#include <iostream>
#include <stdlib.h>

using namespace std;


void quick_sort(Coordinate **dataset, int num_of_element)
{
    qsort_recur(dataset, 0, num_of_element - 1);
}

void qsort_recur(Coordinate **dataset, int start, int end)
{
    if(start < end)
    {
        int median = median_finding(dataset, -1, start, end, (end - start)/2 + start);
        qsort_recur(dataset, start, median);
        qsort_recur(dataset, median + 1, end);
    }
}


int median_finding(Coordinate **dataset, int ref_axis, int left, int right, int n)
{
    if(left == right)
        return left;
    while(1)
    {
        int pivotIndex = pivot(dataset, ref_axis, left, right);
        pivotIndex = partition(dataset, ref_axis, left, right, pivotIndex);
        if (n == pivotIndex)
            return n;
        else if( n < pivotIndex)
            right = pivotIndex - 1;
        else
            left = pivotIndex + 1;
    }
    return 0;
}

//same as quick sort
int partition(Coordinate **dataset, int ref_axis, int left, int right, int pivotIndex)
{
    //partition with index
    if(ref_axis == -1)
    {
        float pivotValue = dataset[pivotIndex]->ID;
        swap(dataset[pivotIndex], dataset[right]);  // Move pivot to end
        int storeIndex = left;
        for(int i = left; i < right; i++)
            if(dataset[i]->ID < pivotValue)
                swap(dataset[storeIndex++], dataset[i]);
        swap(dataset[right], dataset[storeIndex]); // Move pivot to its final place
        return storeIndex;
    }
    else
    {
        float pivotValue = dataset[pivotIndex]->point[ref_axis];
        swap(dataset[pivotIndex], dataset[right]);  // Move pivot to end
        int storeIndex = left;
        for(int i = left; i < right; i++)
            // "<=" important!! if you use "<" it may be make error!! cuz i make left node less or same than parent node
            if(dataset[i]->point[ref_axis] <= pivotValue)
                swap(dataset[storeIndex++], dataset[i]);
        swap(dataset[right], dataset[storeIndex]); // Move pivot to its final place
        return storeIndex;
    }
}


int pivot(Coordinate **dataset, int ref_axis, int left, int right)
{
    // for 5 or less elements just get median
    if (right - left < 5)
        return get_median_and_sort(dataset, ref_axis, left, right);
    //for compute n/5 size
    int size = 0;
    // otherwise move the medians of five-element subgroups to the first n/5 positions
    for(int i = left; i < right; i += 5)
    {   // get the median of the i'th five-element subgroup
        int subRight = i + 4;
        if (subRight > right)
            subRight = right;
        int median5 = get_median_and_sort(dataset, ref_axis, i, subRight);
        swap(dataset[median5],dataset[left + (i - left)/5]);
        size++;
    }
    // compute the median of the n/5 medians-of-five
    return median_finding(dataset, ref_axis, left, left + size - 1, left + (right - left)/10);
}

//insertion sort and get median of array which size is less than 5
int get_median_and_sort(Coordinate **dataset, int ref_axis, int left, int right)
{
    //insertion sort with index
    if(ref_axis == -1)
    {
        for(int p = left + 1; p < right + 1; p++)
        {
            int j;
            Coordinate *tmp = dataset[p];
            // Move right the elements in S that are greater than tmp
            for(j = p; j > left && dataset[j - 1]->ID > tmp->ID; j--)
            {
                dataset[j] = dataset[j - 1];
            }
            // “insert” into the right position
            dataset[j] = tmp;
        }
        //return median
        return (right - left)/2 + left;
    }
    else
    {
        for(int p = left + 1; p < right + 1; p++)
        {
            int j;
            Coordinate *tmp = dataset[p];
            // Move right the elements in S that are greater than tmp
            for(j = p; j > left && dataset[j - 1]->point[ref_axis] > tmp->point[ref_axis]; j--)
            {
                dataset[j] = dataset[j - 1];
            }
            // “insert” into the right position
            dataset[j] = tmp;
        }
        //return median
        return (right - left)/2 + left;
    }
}





