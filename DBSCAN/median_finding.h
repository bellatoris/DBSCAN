//
//  median_finding.h
//  DBSCAN
//
//  Created by Doogie's mac on 2015. 11. 25..
//  Copyright © 2015년 Doogie's mac. All rights reserved.
//

#ifndef median_finding_h
#define median_finding_h

#include "Coordinate_Set.h"

int median_finding(Coordinate **dataset, int axis, int left, int right, int n);

int partition(Coordinate **dataset, int axis, int left, int right, int pivotIndex);

int pivot(Coordinate **dataset, int axis, int left, int right);

int get_median_and_sort(Coordinate **dataset, int axis, int left, int right);

#endif /* median_finding_h */

