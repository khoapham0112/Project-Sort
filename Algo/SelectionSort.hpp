#include <iostream>
#include <vector>
#include <chrono>
#include <random>

void selectionSort(std::vector<int> &a, double &compCount)
{
    int n = a.size();
    compCount = 0;

    for (int i = 0; i < n - 1; ++i)
    {
        compCount++;
        int min_idx = i;

        for (int j = i + 1; j < n; ++j)
        {
            compCount++; 
            if (a[j] < a[min_idx])
            {
                min_idx = j;
            }
            compCount++;
        }
        compCount++;
        if (min_idx != i)
        {
            std::swap(a[i], a[min_idx]);
        }
    }
}

std::pair<double, double> runSelectionSort(std::vector<int> data)
{
    double comparisons = 0;

    auto start = std::chrono::high_resolution_clock::now();

    selectionSort(data, comparisons);

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<chrono::milliseconds>(end - start);

    return { comparisons, duration.count() };
}
