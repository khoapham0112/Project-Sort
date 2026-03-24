#include <algorithm>
#include <chrono>


int partitionFirstPivot(int arr[], int low, int high, double& comp) {
    int pivot = arr[low];
    int i = low + 1;

    for (int j = low + 1; j <= high; j++) {
        comp++;
        comp++;
        if (arr[j] < pivot) {
            std::swap(arr[i], arr[j]);
            i++;
        }
    }
    std::swap(arr[low], arr[i - 1]);

    return i - 1;
}

void quickSortRec(int arr[], int low, int high, double& comp) {
    comp++;
    if (low < high) {
        int pi = partitionFirstPivot(arr, low, high, comp);

        quickSortRec(arr, low, pi - 1, comp);
        quickSortRec(arr, pi + 1, high, comp);
    }
}

std::pair<double, double> quickSort(int arr[], int n) {
    double comp = 0;
    auto start = std::chrono::high_resolution_clock::now();
    if (n > 1) {
        quickSortRec(arr, 0, n - 1, comp);
    }
    std::chrono::duration<double, std::milli> duration = std::chrono::high_resolution_clock::now() - start;

    return { comp, duration.count() };
}