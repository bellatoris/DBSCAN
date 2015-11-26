//
//  main.cpp
//  DBSCAN
//
//  Created by Doogie's mac on 2015. 11. 25..
//  Copyright © 2015년 Doogie's mac. All rights reserved.
//

#include <iostream>
#include <random>
#include "KD_Tree.h"

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
         cout << i << "\t\t(";
        a[i] = new float[4];
        float k = rng()%100;
        float y = k/100;
        for(int j = 0; j < 3; j++)
        {
            a[i][j] = 50 + y + rng()%10;
            cout << a[i][j] << ", ";
        }
        a[i][3] = 50 + y + rng()%10;
        cout << a[i][3] << ")\n";
    }
    cout << endl;
    
//    for(int i = 0; i < 10; i++)
//    {
//        a[i] = new float[2];
//    }
//    a[0][0] = 3;
//    a[0][1] = 2;
//    a[1][0] = 1;
//    a[1][1] = 0;
//    a[2][0] = 1;
//    a[2][1] = 1;
//    a[3][0] = 3;
//    a[3][1] = 2;
//    a[4][0] = 1;
//    a[4][1] = 2;
//    a[5][0] = 0;
//    a[5][1] = 2;
//    a[6][0] = 1;
//    a[6][1] = 1;
//    a[7][0] = 3;
//    a[7][1] = 0;
//    a[8][0] = 0;
//    a[8][1] = 1;
//    a[9][0] = 3;
//    a[9][1] = 3;
    
    KD_Tree x = KD_Tree(a, 4, 100);
    
    for(int i = 0; i < 100; i++)
    {
        cout << x.dataset[i]->ID << "\t(";
        for(int j = 0; j < 3; j++)
        {
            cout << x.dataset[i]->point[j] << ", ";
        }
        cout << x.dataset[i]->point[3] << ")\n";
    }
    cout << endl << endl;
    Coordinate_Set k = x.getNeighbors(*x.dataset[0], 5);
    k.print();
    

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
    return 0;

}
