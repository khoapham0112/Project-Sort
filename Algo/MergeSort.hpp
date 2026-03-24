#include <iostream>
#include <chrono>

using namespace std;

void merge(int a[], int left, int mid, int right, double& compare)
{
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int* L = new int[n1];
    int* R = new int[n2];

    for (int i = 0; i < n1; i++)
    {
        compare++;
        L[i] = a[left + i];
    }
    compare++;
    for (int j = 0; j < n2; j++)
    {
        compare++;
        R[j] = a[mid + 1 + j];
    }
    compare++;
    int i = 0; 
    int j = 0; 
    int k = left; 

    while (i < n1 && j < n2)
    {
        compare+=3; 
        if (L[i] <= R[j])
        {
            a[k] = L[i];
            i++;
        }
        else
        {
            a[k] = R[j];
            j++;
        }
        k++;
    }
    compare += 2;
    while (i < n1)
    {
        compare++;
        a[k] = L[i];
        i++;
        k++;
    }
    compare++;
    while (j < n2)
    {
        compare++;
        a[k] = R[j];
        j++;
        k++;
    }
    compare++;
    delete[] L;
    delete[] R;
}

void mergeSortRecursive(int a[], int left, int right, double& compare)
{
    if (left >= right)
    {
        compare++;
        return;
    }

    int mid = left + (right - left) / 2;

    mergeSortRecursive(a, left, mid, compare);
    mergeSortRecursive(a, mid + 1, right, compare);

    merge(a, left, mid, right, compare);
}

std::pair<double, double> mergeSort(int a[], int n)
{
    auto start = chrono::high_resolution_clock::now();
    double compare = 0;

    mergeSortRecursive(a, 0, n - 1, compare);

    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);

    return { compare, duration.count() };
}