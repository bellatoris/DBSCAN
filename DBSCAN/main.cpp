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

    float **a;
    a = new float*[100];
    for(int i = 0; i < 100; i++)
    {
        cout << "ID:";
        if(i < 10)
            cout <<"0";
         cout << i << "\t\t";
        a[i] = new float[2];
        float k = rng()%100;
        float y = k/100;
        for(int j = 0; j < 1; j++)
        {
//            a[i][j] = 50 + y + rng()%30;
            a[i][j] = rng()%30;
            cout << a[i][j] << ", ";
        }
//        a[i][1] = 50 + y + rng()%30;
        a[i][1] = rng()%30;
        cout << a[i][1] << "\n";
    }
    
//    for(int i = 0; i < 4; i++)
//    {
//        a[i] = new float[2];
//    }
//
//    a[0][0] = 0;
//    a[0][1] = 1;
//    a[1][0] = 1;
//    a[1][1] = 1;
//    a[2][0] = 1;
//    a[2][1] = 1;
//    a[3][0] = 1;
//    a[3][1] = 0;

    
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

    
    KD_Tree x = KD_Tree(a, 3, 100);
    DBSCAN myDBSCAN = DBSCAN(x, 2, 2);
    myDBSCAN.run();
    
//    for(int i = 0; i < 100; i++)
//    {
//        cout << x.dataset[i]->ID << "\t(";
//        for(int j = 0; j < 3; j++)
//        {
//            cout << x.dataset[i]->point[j] << ", ";
//        }
//        cout << x.dataset[i]->point[3] << ")\n";
//    }
//    cout << endl << endl;
//    cout << x.dataset[0]->ID << endl;
//    Coordinate_Set k = x.getNeighbors(*x.dataset[0], 100);
//    k.print();
//    

//    KD_Tree x = KD_Tree(a, 5, 100);
//    
//    for(int i = 0; i < 100; i++)
//    {
//        cout << "ID: " << x.dataset[i]->ID << "\t\t(";
//        for(int j = 0; j < 5; j++)
//        {
//            cout << "\t" << x.dataset[i]->point[j];
//        }
//        cout << "\t)" << endl;
//    }
//    cout << endl << endl;
//    Coordinate_Set k = x.getNeighbors(*x.dataset[0], 1000);
//    k.print();
    
    for(int i = 0; i < 100; i++)
    {
        if(a[i])
            delete a[i];
        a[i] = NULL;
    }
    delete []a;
    a = NULL;


    return 0;
    
}
