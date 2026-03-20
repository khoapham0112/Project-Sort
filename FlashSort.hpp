#include <iostream>
#include <vector>
#include <chrono>
#include <random>

void flashSort(std::vector<int> &a, unsigned long long &compCount)
{
    int n = a.size();
    if (n <= 1)
        return;

    compCount = 0;
    int max_idx = 0;
    int min_val = a[0];

    for (int i = 1; i < n; ++i)
    {
        compCount++; 
        if (a[i] < min_val)
        {
            min_val = a[i];
        }

        compCount++; 
        if (a[i] > a[max_idx])
        {
            max_idx = i;
        }
    }

    if (a[max_idx] == min_val)
        return; 

    int m = 0.45 * n;
    std::vector<int> l(m, 0);
    double c1 = (double)(m - 1) / (a[max_idx] - min_val);

    for (int i = 0; i < n; ++i)
    {
        int k = c1 * (a[i] - min_val);
        l[k]++;
    }

    for (int i = 1; i < m; ++i)
    {
        l[i] += l[i - 1];
    }

    std::swap(a[max_idx], a[0]);

    int nmove = 0;
    int j = 0;
    int k = m - 1;
    int flash;

    while (nmove < n - 1)
    {
        while (j > l[k] - 1)
        {
            j++;
            k = c1 * (a[j] - min_val);
        }
        flash = a[j];
        while (j != l[k])
        {
            k = c1 * (flash - min_val);
            int hold = a[l[k] - 1];
            a[l[k] - 1] = flash;
            flash = hold;
            l[k]--;
            nmove++;
        }
    }

    for (int i = 1; i < n; ++i)
    {
        int hold = a[i];
        int j = i - 1;

        if (j >= 0)
            compCount++; 
        while (j >= 0 && a[j] > hold)
        {
            a[j + 1] = a[j];
            j--;
            if (j >= 0)
                compCount++; 
        }
        a[j + 1] = hold;
    }
}

std::pair<long long, double> runFlashSort(std::vector<int> data)
{
    unsigned long long comparisons = 0;

    auto start = std::chrono::high_resolution_clock::now();

    flashSort(data, comparisons);

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> duration_ms = end - start;

    return { comparisons, duration_ms.count() };
}