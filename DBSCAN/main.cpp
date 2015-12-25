//
//  main.cpp
//  DBSCAN
//
//  Created by Doogie's mac on 2015. 11. 25..
//  Copyright © 2015년 Doogie's mac. All rights reserved.
//



//you need to solve same point node problem

#include <iostream>
#include <random>
#include "DBSCAN.h"


using namespace std;

int main(int argc, const char * argv[]) {
    
    random_device rng;
    FILE *testset = fopen("/Users/Bellatoris/Documents/MATLAB/testset", "w");
    float **a;
    a = new float*[8000];
    for(int i = 0; i < 8000; i++)
    {
        cout << "ID:";
        if(i < 10)
            cout <<"0";
         cout << i << "\t\t";
        a[i] = new float[5];
        for(int j = 0; j < 4; j++)
        {
            float y = rng()%1000;
            y = y/1000;
            a[i][j] = y + rng()%70;
            cout << a[i][j] << ", ";
            fprintf(testset, "%f ", a[i][j]);
        }
        float y = rng()%1000;
        y = y/1000;
        a[i][4] = 50 + y + rng()%30;
        cout << a[i][4] << "\n";
        fprintf(testset, "%f\n", a[i][4]);
    }
    fclose(testset);
    
//    for(int i = 0; i < 11; i++)
//    {
//        a[i] = new float[2];
//    }
//    a[0][0] = 0;
//    a[0][1] = 5;
//    a[1][0] = 1;
//    a[1][1] = 6;
//    a[2][0] = 2;
//    a[2][1] = 7;
//    a[3][0] = 2;
//    a[3][1] = 4;
//    a[4][0] = 2;
//    a[4][1] = 2;
//    a[5][0] = 3;
//    a[5][1] = 2;
//    a[6][0] = 4;
//    a[6][1] = 9;
//    a[7][0] = 4;
//    a[7][1] = 1;
//    a[8][0] = 5;
//    a[8][1] = 3;
//    a[9][0] = 6;
//    a[9][1] = 4;
//    a[10][0] = 7;
//    a[10][1] = 1;

    //KD_Tree(float **, dimension, num of data)
    KD_Tree x = KD_Tree(a, 5, 8000);
    //DBSCAN(&KD_Tree, epslion, minpoints)
    DBSCAN myDBSCAN = DBSCAN(x, 7, 2);
    myDBSCAN.run();
    
    for(int i = 0; i < 8000; i++)
    {
        if(a[i])
            delete a[i];
        a[i] = NULL;
    }
    delete []a;
    a = NULL;


    return 0;
    
}
