#include <iostream>
#include <chrono>
#include <vector>

std::pair<double, double> ShakerSort(int a[], int n)
{
    double compare = 0;
    auto start = std::chrono::high_resolution_clock::now();
    int Left = 0;
    int Right = n - 1;
    int k = 0;
    int i;
    while (Left < Right)
    {
        compare++;
        for (i = Left; i < Right; i++)
        {
            compare += 2;
            if (arr[i] > arr[i + 1]) 
            {
                std::swap(a[i], a[i + 1]);
                k = i;
            }
        }
        compare += 2;
        if (!is_swapped) 
        {
            break;
        }

        is_swapped = false;
        --end;

        for (int i = end - 1; i >= start; --i) 
        {
            compare+=2;
            if (arr[i] > arr[i + 1]) 
            {
                std::swap(a[i], a[i - 1]);
                k = i;
            }
        }
        compare++;
        ++start;
    }
    compare++;
    auto endTime = std::chrono::high_resolution_clock::now();
    std::chrono::milliseconds duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);
    return { compare, duration.count() };
}
