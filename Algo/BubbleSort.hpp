#include <iostream>
#include <chrono>
#include <vector>

std::pair<double, double> BubbleSort(int a[], int n)
{
    double compare = 0;
   
    auto start = std::chrono::high_resolution_clock::now();
    bool swapped = false;
    for (int i = 0; i < n - 1; i++)
    {
        compare++;
        swapped = false;
        for (int j = 0; j < n - i - 1; j++)
        {
            compare += 2;

            if (a[j] > a[j + 1])
            {
                std::swap(a[j], a[j + 1]);
                swapped = true;
            }
        }
        
        compare++;

        if (!swapped) {
            break;
        }
    }
    compare++;

    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::milliseconds duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    return { compare, duration.count() };
}