#include <iostream>
#include <chrono>

using namespace std;

std::pair<double, double> shellSort(int a[], int n){
    auto start = chrono::high_resolution_clock::now();
    double compare = 0;

    for (int gap = n / 2; gap > 0; gap /= 2){
        for (int i = gap; i < n; i++){
            int temp = a[i];
            int j;

            for (j = i; j >= gap; j -= gap){
                compare++; 
                if (a[j - gap] > temp){
                    a[j] = a[j - gap];
                }
                else{
                    break;
                }
            }
            a[j] = temp;
        }
    }

    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);

    return { compare, duration.count() };
}