#include <iostream>
#include <vector>
#include <chrono>
#include <random>

void selectionSort(std::vector<int> &a, unsigned long long &compCount)
{
    int n = a.size();
    compCount = 0;

    for (int i = 0; i < n - 1; ++i)
    {
        int min_idx = i;

        for (int j = i + 1; j < n; ++j)
        {
            compCount++; 
            if (a[j] < a[min_idx])
            {
                min_idx = j;
            }
        }
        if (min_idx != i)
        {
            std::swap(a[i], a[min_idx]);
        }
    }
}

std::pair<long long, double> runSelectionSort(std::vector<int> data)
{
    unsigned long long comparisons = 0;

    auto start = std::chrono::high_resolution_clock::now();

    selectionSort(data, comparisons);

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);

    return { comparisons, duration.count() };
}