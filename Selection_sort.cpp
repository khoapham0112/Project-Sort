#include <iostream>
#include <vector>
#include <chrono>
#include <random>

// Selection Sort algorithm with comparison tracking
void selectionSort(std::vector<int> &a, unsigned long long &compCount)
{
    int n = a.size();
    compCount = 0;

    for (int i = 0; i < n - 1; ++i)
    {
        int min_idx = i;

        // Find the minimum element in the unsorted array
        for (int j = i + 1; j < n; ++j)
        {
            compCount++; // Track every comparison
            if (a[j] < a[min_idx])
            {
                min_idx = j;
            }
        }

        // Swap the found minimum element with the first element
        if (min_idx != i)
        {
            std::swap(a[i], a[min_idx]);
        }
    }
}

// Orchestrator function to handle setup, execution, and the exact requested output
void runSelectionSort()
{
    // Note: Selection Sort is O(N^2). Sorting 100,000 elements will take
    // significantly longer (a few seconds) compared to Flash Sort.
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
    selectionSort(data, comparisons);

    // Stop timer
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> duration_ms = end - start;

    // Output formatted exactly like the provided image example
    std::cout << "Running time (if required): " << duration_ms.count() << " ms\n";
    std::cout << "Comparisions (if required): " << comparisons << "\n";
}

// Main function only calls the orchestrator
int main()
{
    runSelectionSort();
    return 0;
}