#include <algorithm>
#include <chrono>


int getMax(int arr[], int n, double& comp) {
    int mx = arr[0];
    for (int i = 1; i < n; i++) {
        comp += 2;
        if (arr[i] > mx) {
            mx = arr[i];
        }
    }
    comp++;
    return mx;
}


void countSortForRadix(int arr[], int n, int exp, double& comp) {
    int* output = new int[n];
    int i, count[10] = { 0 };

    for (i = 0; i < n; i++) {
        comp++;
        count[(arr[i] / exp) % 10]++;
    }
    comp++;
    for (i = 1; i < 10; i++) {
        comp++;
        count[i] += count[i - 1];
    }
    comp++;
    for (i = n - 1; i >= 0; i--) {
        comp++;
        output[count[(arr[i] / exp) % 10] - 1] = arr[i];
        count[(arr[i] / exp) % 10]--;
    }
    comp++;
    for (i = 0; i < n; i++) {
        comp++;
        arr[i] = output[i];
    }
    comp++;
    delete[] output;
}

std::pair<double, double> radixSort(int arr[], int n) {
    double comp = 0;
    auto start = std::chrono::high_resolution_clock::now();
    comp++;
    if (n <= 1) return { 0, 0 };

    int m = getMax(arr, n, comp);

    for (int exp = 1; m / exp > 0; exp *= 10) {
        countSortForRadix(arr, n, exp, comp);
    }
    std::chrono::duration<double, std::milli> duration = std::chrono::high_resolution_clock::now() - start;

    return { comp, duration.count() };
}