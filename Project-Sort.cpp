#include <iostream>
#include <cstring>
#include <filesystem>
#include <string>
#include <stdexcept>
#include <chrono>
#include <vector>

int flag = 0;

#include "DataGenerator.hpp"
#include "SelectionSort.hpp"
#include "InsertionSort.hpp"
#include "BinaryInsertionSort.hpp"
#include "BubbleSort.hpp"
#include "ShakerSort.hpp"
#include "ShellSort.hpp"
#include "HeapSort.hpp"
#include "MergeSort.hpp"
//#include "QuickSort.hpp"
#include "CountingSort.hpp"
//#include "RadixSort.hpp"
#include "FlashSort.hpp"

using namespace std;

bool isInteger(const std::string& s) {
    try {
        std::size_t pos;
        std::stoi(s, &pos);
        return pos == s.length();
    }
    catch (const std::invalid_argument& e) {
        return false;
    }
    catch (const std::out_of_range& e) {
        return false;
    }
}

int main(int argc, char** argv)
{
    if (argc > 6) return 1;

    if (strcmp(argv[1], "-a") == 0)
    {
        string algo = argv[2];
        string input = argv[3];
        string order = "";
        string outParam = "";
        int range = 4;

        if (argc == 5)
        {
            outParam = argv[4];
        }
        else if (argc == 6)
        {
            range = 1;
            order = argv[4];
            outParam = argv[5];
        }

        if (outParam == "-time") flag = 1;
        if (outParam == "-comp") flag = 2;
        if (outParam == "-both") flag = 3;

        vector<vector<int>> arr(4);

        if (isInteger(input))
        {
            int n = stoi(input);
            for (int i = 0; i < 4; ++i)
            {
                arr[i].resize(n);
                GenerateData(arr[i].data(), n, i);
            }
        }
        else {
            arr.resize(1);
            vector<int>& a = arr[0];
            int n;
            range = 1;

            if (std::filesystem::exists(input))
            {
                fstream fs(input, ios::in);
                
                fs >> n;
                while (n--)
                {
                    int tmp;
                    fs >> tmp;
                    a.push_back(tmp);
                }
            }
            else {
                cout << "Invalid input file!\n";
                return 2;
            }
        }
        cout << "ALGORITHM MODE\nAlgorithm: ";
        string strorder[] = { "Randomize", "Sorted", "Reversed", "Nearly Sorted" };
        if (algo == "selection-sort") cout << "Selection Sort\n";
        if (algo == "insertion-sort") cout << "Insertion Sort\n";
        if (algo == "binary-insertion-sort") cout << "Binary Insertion Sort\n";
        if (algo == "bubble-sort") cout << "Bubble Sort\n";
        if (algo == "shaker-sort") cout << "Shaker Sort\n";
        if (algo == "shell-sort") cout << "Shell Sort\n";
        if (algo == "heap-sort") cout << "Heap Sort\n";
        if (algo == "merge-sort") cout << "Merge Sort\n";
        if (algo == "quick-sort") cout << "Quick Sort\n";
        if (algo == "counting-sort") cout << "Counting Sort\n";
        if (algo == "radix-sort") cout << "Radix Sort\n";
        if (algo == "flash-sort") cout << "Flash Sort\n";
        cout << "\n";
        for (int i = 0; i < range; ++i)
        {
            vector<int>& a = arr[i];
            int n = a.size();
            if (range != 1)
            {
                cout << "Input order: " << strorder[i] << "\n";
                cout << "-----------------------------------\n";
            }
            if (algo == "selection-sort") runSelectionSort(a);
            if (algo == "insertion-sort") InsertionSort(a.data(), n);
            if (algo == "binary-insertion-sort") binaryInsertionSort(a.data(), n);
            if (algo == "bubble-sort") BubbleSort(a.data(), n);
            if (algo == "shaker-sort") ShakerSort(a.data(), n);
            if (algo == "shell-sort") shellSort(a.data(), n);
            if (algo == "heap-sort") runHeapSort(a);
            if (algo == "merge-sort") mergeSort(a.data(), n);
            if (algo == "quick-sort") (a.data(), n);
            if (algo == "counting-sort") countingSort(a.data(), n);
            if (algo == "radix-sort") (a.data(), n);
            if (algo == "flash-sort") runFlashSort(a);
            cout << "\n";
        }
    }
    else if (strcmp(argv[1], "-c") == 0)
    {
        string algo1 = argv[2];
        string algo2 = argv[3];
        string input = argv[4]; // Can be either file name or input size
        string order = "";

        if (argc == 6)
        {
            order = argv[5];
        }

        cout << "COMPARE MODE\n";

        // Helper lambda to easily print the formatted algorithm names
        auto getAlgoName = [](string a) {
            if (a == "selection-sort") return "Selection Sort";
            if (a == "insertion-sort") return "Insertion Sort";
            if (a == "binary-insertion-sort") return "Binary Insertion Sort";
            if (a == "bubble-sort") return "Bubble Sort";
            if (a == "shaker-sort") return "Shaker Sort";
            if (a == "shell-sort") return "Shell Sort";
            if (a == "heap-sort") return "Heap Sort";
            if (a == "merge-sort") return "Merge Sort";
            if (a == "quick-sort") return "Quick Sort";
            if (a == "counting-sort") return "Counting Sort";
            if (a == "radix-sort") return "Radix Sort";
            if (a == "flash-sort") return "Flash Sort";
            return "";
            };

        cout << "Algorithm: " << getAlgoName(algo1) << " | " << getAlgoName(algo2) << "\n";

        vector<int> a1, a2;
        int n = 0;

        if (!isInteger(input))
        {
            cout << "Input file: " << input << "\n";
            if (std::filesystem::exists(input))
            {
                fstream fs(input, ios::in);
                fs >> n;
                int temp_n = n;
                while (temp_n--)
                {
                    int tmp;
                    fs >> tmp;
                    a1.push_back(tmp);
                }
                a2 = a1;
                cout << "Input size: " << n << "\n";
            }
            else {
                cout << "Invalid input file!\n";
                return 2;
            }
        }
        else
        {
            n = stoi(input);
            cout << "Input size: " << n << "\n";

            int orderIdx = 0;
            string strOrder = "";
            if (order == "-rand") { strOrder = "Randomize"; orderIdx = 0; }
            else if (order == "-sorted") { strOrder = "Sorted"; orderIdx = 1; }
            else if (order == "-rev") { strOrder = "Reversed"; orderIdx = 2; }
            else if (order == "-nsorted") { strOrder = "Nearly Sorted"; orderIdx = 3; }

            cout << "Input order: " << strOrder << "\n";

            a1.resize(n);
            GenerateData(a1.data(), n, orderIdx);
            a2 = a1;
        }

        cout << "-----------------------------------\n";

        double time1 = 0.0, time2 = 0.0;
        long long comp1 = 0, comp2 = 0;

        auto runAlgorithm = [&](string algo, vector<int>& a, double& time, long long& comp) {
            int n = a.size();

            // If you are using a global variable for comparisons, reset it here:
            // global_comp_count = 0; 

            auto start = std::chrono::high_resolution_clock::now();

            if (algo == "selection-sort") runSelectionSort(a);
            else if (algo == "insertion-sort") InsertionSort(a.data(), n);
            else if (algo == "binary-insertion-sort") binaryInsertionSort(a.data(), n);
            else if (algo == "bubble-sort") BubbleSort(a.data(), n);
            else if (algo == "shaker-sort") ShakerSort(a.data(), n);
            else if (algo == "shell-sort") shellSort(a.data(), n);
            else if (algo == "heap-sort") runHeapSort(a);
            else if (algo == "merge-sort") mergeSort(a.data(), n);
            else if (algo == "quick-sort") /* replace with your quick sort call */;
            else if (algo == "counting-sort") countingSort(a.data(), n);
            else if (algo == "radix-sort") /* replace with your radix sort call */;
            else if (algo == "flash-sort") runFlashSort(a);

            auto end = std::chrono::high_resolution_clock::now();

            // Calculate duration in milliseconds
            std::chrono::duration<double, std::milli> duration = end - start;
            time = duration.count();

            // Assign the tracked comparisons
            // comp = global_comp_count; // (Or however you are returning the count)
            };

        // Run both algorithms
        runAlgorithm(algo1, a1, time1, comp1);
        runAlgorithm(algo2, a2, time2, comp2);

        // Outputting the final comparison metrics
        cout << "Running time: " << time1 << " | " << time2 << "\n";
        cout << "Comparisions: " << comp1 << " | " << comp2 << "\n";
    }

    return 0;
}