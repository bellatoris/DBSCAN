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

int median_finding(float list[], int left, int right, int n)
{
    if(left == right)
        return left;
    while(1)
    {
        int pivotIndex = pivot(list, left, right);
        pivotIndex = partition(list, left, right, pivotIndex);
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
int partition(float list[], int left, int right, int pivotIndex)
{
    int pivotValue = list[pivotIndex];
    swap(list[pivotIndex],list[right]);  // Move pivot to end
    int storeIndex = left;
    for(int i = left; i < right; i++)
        if(list[i] < pivotValue)
            swap(list[storeIndex++], list[i]);
    swap(list[right], list[storeIndex]) ; // Move pivot to its final place
    return storeIndex;
}


int pivot(float list[], int left, int right)
{
    // for 5 or less elements just get median
    if (right - left < 5)
        return get_median_and_sort(list, left, right);
    //for compute n/5 size
    int size = 0;
    // otherwise move the medians of five-element subgroups to the first n/5 positions
    for(int i = left; i < right; i += 5)
    {      // get the median of the i'th five-element subgroup
        int subRight = i + 4;
        if (subRight > right)
            subRight = right;
        int median5 = get_median_and_sort(list, i, subRight);
        swap(list[median5],list[left + (i - left)/5]);
        size++;
    }
    // compute the median of the n/5 medians-of-five
    return median_finding(list, left, left + size - 1, left + (right - left)/10);
}

//insertion sort and get median of array which size is less than 5
int get_median_and_sort(float list[], int left, int right)
{
    for (int p = left + 1; p < right + 1; p++)
    {
        int j;
        float tmp = list[p];
        // Move right the elements in S that are greater than tmp
        for(j = p; j > left && list[j - 1] > tmp; j--)
        {
            list[j] = list[j - 1];
        }
        // “insert” into the right position
        list[j] = tmp;
    }
    //return median
    return (right - left)/2 + left;
}





