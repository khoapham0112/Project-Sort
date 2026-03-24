#include <iostream>
#include <cstring>
#include <filesystem>
#include <string>
#include <stdexcept>
#include <chrono>
#include <vector>

#include "DataGenerator.hpp"
#include "../Algo/Algo.hpp"

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

void outputFile(vector<int>& arr, string name)
{
    fstream fs(name, ios::out | ios::trunc);

    for (int a : arr) fs << a << " ";

    fs.close();
}

int main(int argc, char** argv)
{
    if (argc > 6) return 1;

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

    auto runAlgorithm = [&](string algo, vector<int>& a, double& time, double& comp) {
        int n = a.size();

        std::pair<double, double> res;

        if (algo == "selection-sort") res = runSelectionSort(a);
        else if (algo == "insertion-sort") res = InsertionSort(a.data(), n);
        else if (algo == "binary-insertion-sort") res = binaryInsertionSort(a.data(), n);
        else if (algo == "bubble-sort") res = BubbleSort(a.data(), n);
        else if (algo == "shaker-sort") res = ShakerSort(a.data(), n);
        else if (algo == "shell-sort") res = shellSort(a.data(), n);
        else if (algo == "heap-sort") res = runHeapSort(a);
        else if (algo == "merge-sort") res = mergeSort(a.data(), n);
        else if (algo == "quick-sort") res = quickSort(a.data(), n);
        else if (algo == "counting-sort") res = countingSort(a.data(), n);
        else if (algo == "radix-sort") res = radixSort(a.data(), n);
        else if (algo == "flash-sort") res = runFlashSort(a);

        comp = res.first;
        time = res.second;
        };

    if (strcmp(argv[1], "-a") == 0)
    {
        string algo = argv[2];
        string input = argv[3];
        string order = "";
        string outParam = "";
        int range = 4;
        int flag = 0;

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

        cout << "ALGORITHM MODE\nAlgorithm: " << getAlgoName(algo) << "\n";

        if (isInteger(input))
        {
            int n = stoi(input);
            for (int i = 0; i < 4; ++i)
            {
                arr[i].resize(n);
                GenerateData(arr[i].data(), n, i);
            }

            string strorder[] = { "Randomize", "Sorted", "Reversed", "Nearly Sorted" };

            cout << "Input size: " << arr[0].size() << "\n";

            for (int i = 0; i < range; ++i)
            {
                int orderIdx = i;
                if (range == 1)
                {
                    if (order == "-rand") orderIdx = 0;
                    else if (order == "-sorted") orderIdx = 1;
                    else if (order == "-rev") orderIdx = 2;
                    else if (order == "-nsorted") orderIdx = 3;
                    i = orderIdx;
                    outputFile(arr[i], "input.txt");
                } else outputFile(arr[i], "input_"+ to_string(i + 1) + ".txt");

                cout << "Input order: " << strorder[orderIdx] << "\n";
                cout << "-----------------------------------\n";
                vector<int>& a = arr[i];
                int n = a.size();

                double time;
                double comp;

                runAlgorithm(algo, a, time, comp);

                if (range == 1) outputFile(a, "output.txt");

                if (flag & 1) cout << "Running time: " << time << "ms\n";
                if (flag & 2) cout << "Comparisions: " << comp << "\n";
                cout << "\n";
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

            if (range != 1) cout << "Input file: " << input << "\n";
            cout << "Input size: " << arr[0].size() << "\n";
            cout << "-----------------------------------\n";

            double time;
            double comp;

            runAlgorithm(algo, a, time, comp);

            outputFile(a, "output.txt");

            if (flag & 1) cout << "Running time: " << time << "ms\n";
            if (flag & 2) cout << "Comparisions: " << comp << "\n";
        }
    }
    else if (strcmp(argv[1], "-c") == 0)
    {
        string algo1 = argv[2];
        string algo2 = argv[3];
        string input = argv[4]; // Can be either file name or input size
        string order = "-rand";

        if (argc == 6)
        {
            order = argv[5];
        }

        cout << "COMPARE MODE\n";
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
                outputFile(a1, "input.txt");
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
        double comp1 = 0, comp2 = 0;

        runAlgorithm(algo1, a1, time1, comp1);
        runAlgorithm(algo2, a2, time2, comp2);

        cout << "Running time: " << time1 << "ms | " << time2 << "ms\n";
        cout << "Comparisions: " << comp1 << " | " << comp2 << "\n";
    }

    return 0;
}