#include <iostream>
#include <chrono>
#include <vector>

std::pair<double, double> InsertionSort(int a[], int n)
{
    double compare = 0;

    auto start = std::chrono::high_resolution_clock::now();

    for (int i = 1; i < n; i++)
    {
        compare++;
        int key = a[i];
        int j = i - 1;

        while (j >= 0)
        {
            compare += 2;

            if (a[j] > key)
            {
                compare++;
                a[j + 1] = a[j];
                j--;
            }
            else
                break;
        }
        compare++;

        a[j + 1] = key;
    }
    compare++;

    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::milliseconds duration =
        std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    return { compare, duration.count() };
}
