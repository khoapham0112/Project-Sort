#include <iostream>
#include <vector>
#include <chrono>
#include <random>

// Flash Sort algorithm with comparison tracking
void flashSort(std::vector<int> &a, unsigned long long &compCount)
{
    int n = a.size();
    if (n <= 1)
        return;

    compCount = 0;
    int max_idx = 0;
    int min_val = a[0];

    // Phase 1: Classification
    for (int i = 1; i < n; ++i)
    {
        compCount++; // Counting min comparison
        if (a[i] < min_val)
        {
            min_val = a[i];
        }

        compCount++; // Counting max comparison
        if (a[i] > a[max_idx])
        {
            max_idx = i;
        }
    }

    if (a[max_idx] == min_val)
        return; // All elements are the same

    // Number of classes (heuristically set to 0.45 * n)
    int m = 0.45 * n;
    std::vector<int> l(m, 0);
    double c1 = (double)(m - 1) / (a[max_idx] - min_val);

    // Count elements in each class
    for (int i = 0; i < n; ++i)
    {
        int k = c1 * (a[i] - min_val);
        l[k]++;
    }

    // Calculate starting positions of classes
    for (int i = 1; i < m; ++i)
    {
        l[i] += l[i - 1];
    }

    std::swap(a[max_idx], a[0]);

    // Phase 2: Permutation
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

    // Phase 3: Straight Insertion Sort
    for (int i = 1; i < n; ++i)
    {
        int hold = a[i];
        int j = i - 1;

        if (j >= 0)
            compCount++; // Initial comparison for the while loop
        while (j >= 0 && a[j] > hold)
        {
            a[j + 1] = a[j];
            j--;
            if (j >= 0)
                compCount++; // Subsequent comparisons in the while loop
        }
        a[j + 1] = hold;
    }
}

// Orchestrator function to handle setup, execution, and the exact requested output
void runFlashSort()
{
    const int SIZE = 100000;
    std::vector<int> data(SIZE);

    // Setup random number generation
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(1, 1000000);

    // Populate the vector
    for (int i = 0; i < SIZE; ++i)
    {
        data[i] = distrib(gen);
    }

    unsigned long long comparisons = 0;

    // Start timer
    auto start = std::chrono::high_resolution_clock::now();

    // Run sort
    flashSort(data, comparisons);

    // Stop timer
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> duration_ms = end - start;

    // Output formatted exactly like the provided image example
    // (Note: Kept the exact spelling "Comparisions" from your image)
    std::cout << "Running time (if required): " << duration_ms.count() << " ms\n";
    std::cout << "Comparisions (if required): " << comparisons << "\n";
}

// Main function only calls the orchestrator
int main()
{
    runFlashSort();
    return 0;
}