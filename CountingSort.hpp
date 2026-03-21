#include <iostream>
#include <chrono>
#include <vector> 
using namespace std;

std::pair<double, double> countingSort(int a[], int n){
    auto start = chrono::high_resolution_clock::now();
    double compare = 0;

    int max_val = a[0];
    for (int i = 1; i < n; i++){
        compare+=2; 
        if (a[i] > max_val)
        {
            max_val = a[i];
        }
    }
    compare++;
    vector<int> count(max_val + 1, 0);
    vector<int> output(n);

    for (int i = 0; i < n; i++){
        compare++;
        count[a[i]]++;
    }
    compare++;
    for (int i = 1; i <= max_val; i++){
        compare++;
        count[i] += count[i - 1];
    }
    compare++;
    for (int i = n - 1; i >= 0; i--){
        compare++;
        output[count[a[i]] - 1] = a[i];
        count[a[i]]--;
    }
    compare++;
    for (int i = 0; i < n; i++){
        compare++;
        a[i] = output[i];
    }
    compare++;
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::nanoseconds>(end - start);

    return { compare, duration.count() / 1000000.0 };
}
