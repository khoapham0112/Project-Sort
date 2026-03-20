#include <iostream>
#include <chrono>
using namespace std;

int binarySearch(int a[], int item, int low, int high, double& compare)
{
    if (high <= low)
    {
        compare++;
        return (item > a[low]) ? (low + 1) : low;
    }  

    int mid = (low + high) / 2;

    compare++;

    if (item == a[mid])
        return mid + 1;

    compare++;

    if (item > a[mid])
        return binarySearch(a, item, mid + 1, high, compare);
    return binarySearch(a, item, low, mid - 1, compare);
}

std::pair<double, double> binaryInsertionSort(int a[], int n)
{
    auto start = chrono::high_resolution_clock::now();
    int i, locate, j, selected;
    double compare = 0;

    for (i = 1; i < n; ++i)
    {
        j = i - 1;
        selected = a[i];

        locate = binarySearch(a, selected, 0, j, compare);

        while (j >= locate)
        {
            a[j + 1] = a[j];
            j--;
        }
        a[j + 1] = selected;
    }
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);

    return { compare, duration.count() };
}