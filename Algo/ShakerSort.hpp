#include <iostream>
#include <chrono>
#include <vector>

std::pair<double, double> ShakerSort(int a[], int n)
{
    double compare = 0;
    auto startTime = std::chrono::high_resolution_clock::now();
    bool swapped = true;
    int start = 0;
    int end = n - 1;
    while (swapped) {
        compare++;
        swapped = false;
        for (int i = start; i < end; ++i) {
            compare+=2;
            if (a[i] > a[i + 1]) {
                swap(a[i], a[i + 1]);
                swapped = true;
            }
        }
        compare++;
        if (!swapped)
        {
            compare--;
            break;
        }
        swapped = false;
        --end;
        for (int i = end - 1; i >= start; --i) {
            compare+=2;
            if (a[i] > a[i + 1]) {
                swap(a[i], a[i + 1]);
                swapped = true;
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
