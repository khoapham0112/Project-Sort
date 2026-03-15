#include <iostream>
#include <vector>
#include <chrono>
#include <random>

// Helper function to maintain the max-heap property
void heapify(std::vector<int> &a, int n, int i, unsigned long long &compCount)
{
    int largest = i; // Initialize largest as root
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    // If left child is larger than root
    if (left < n)
    {
        compCount++; // Track comparison
        if (a[left] > a[largest])
        {
            largest = left;
        }
    }

    // If right child is larger than largest so far
    if (right < n)
    {
        compCount++; // Track comparison
        if (a[right] > a[largest])
        {
            largest = right;
        }
    }

    // If largest is not root
    if (largest != i)
    {
        std::swap(a[i], a[largest]);

        // Recursively heapify the affected sub-tree
        heapify(a, n, largest, compCount);
    }
}

// Heap Sort algorithm with comparison tracking
void heapSort(std::vector<int> &a, unsigned long long &compCount)
{
    int n = a.size();
    compCount = 0;

    // Build max heap
    for (int i = n / 2 - 1; i >= 0; i--)
    {
        heapify(a, n, i, compCount);
    }

    // Extract elements from heap one by one
    for (int i = n - 1; i > 0; i--)
    {
        // Move current root to end
        std::swap(a[0], a[i]);

        // Call max heapify on the reduced heap
        heapify(a, i, 0, compCount);
    }
}

// Orchestrator function to handle setup, execution, and the exact requested output
void runHeapSort()
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
    heapSort(data, comparisons);

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
    runHeapSort();
    return 0;
}
//MAX HEAP