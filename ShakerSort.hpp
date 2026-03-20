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
        for (i = Left; i < Right; i++)
        {
            compare++;
            if (a[i] > a[i + 1])
            {
                std::swap(a[i], a[i + 1]);
                k = i;
            }
        }
        Right = k;
        for (i = Right; i > Left; i--)
        {
            compare++;
            if (a[i] < a[i - 1])
            {
                std::swap(a[i], a[i - 1]);
                k = i;
            }
        }
        Left = k;
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::milliseconds duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    return { compare, duration.count() };
}