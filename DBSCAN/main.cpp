//
//  main.cpp
//  DBSCAN
//
//  Created by Doogie's mac on 2015. 11. 25..
//  Copyright © 2015년 Doogie's mac. All rights reserved.
//

#include <iostream>
#include <random>
#include "median_finding.h"

using namespace std;

int main(int argc, const char * argv[]) {
    
    random_device rng;
    
    float **test;
    
    test = new float*[100];
    for(int i = 0; i < 100; i++)
    {
        test[i] = new float[100];
    }
    
    for(int i = 0; i < 100; i++)
    {
        for(int j = 0; j< 100; j++)
        {
            float x = rng()%100;
            test[i][j] = rng()%100 + (x)/100;
            //        cout << test[i] << endl;
        }
    }
    
    cout << median_finding(test[1], 0, 99, 50) << endl;
//    cout << get_median_and_sort(test, 0, 19);
    return 0;
    
}
