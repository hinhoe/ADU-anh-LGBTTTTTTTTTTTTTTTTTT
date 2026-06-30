#include "pch.h"
#include "SortingAlgorithms.h"

#include <chrono>

using namespace std;
using namespace std::chrono;

BenchmarkResult BubbleSort(vector<int> arr)
{
    BenchmarkResult result;

    auto start = high_resolution_clock::now();

    for (int i = 0; i < arr.size() - 1; i++)
    {
        for (int j = 0; j < arr.size() - i - 1; j++)
        {
            result.comparisons++;

            if (arr[j] > arr[j + 1])
            {
                swap(arr[j], arr[j + 1]);
                result.swaps++;
            }
        }
    }

    auto end = high_resolution_clock::now();

    result.elapsedMs =
        duration<double, milli>(end - start).count();

    result.sortedData = arr;
    return result;
}

BenchmarkResult InsertionSort(vector<int> arr)
{
    BenchmarkResult result;

    auto start = high_resolution_clock::now();

    for (int i = 1; i < arr.size(); i++)
    {
        int key = arr[i];
        int j = i - 1;

        while (j >= 0)
        {
            result.comparisons++;

            if (arr[j] > key)
            {
                arr[j + 1] = arr[j];
                result.swaps++;
                j--;
            }
            else
                break;
        }

        arr[j + 1] = key;
    }

    auto end = high_resolution_clock::now();

    result.elapsedMs =
        duration<double, milli>(end - start).count();

    result.sortedData = arr;
    return result;
}
static int Partition(std::vector<int>& arr, int low, int high, BenchmarkResult& result)
{
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++)
    {
        result.comparisons++;

        if (arr[j] < pivot)
        {
            i++;
            std::swap(arr[i], arr[j]);
            result.swaps++;
        }
    }

    std::swap(arr[i + 1], arr[high]);
    result.swaps++;

    return i + 1;
}

static void QuickSortRecursive(std::vector<int>& arr,
    int low,
    int high,
    BenchmarkResult& result)
{
    if (low < high)
    {
        int pi = Partition(arr, low, high, result);

        QuickSortRecursive(arr, low, pi - 1, result);
        QuickSortRecursive(arr, pi + 1, high, result);
    }
}

BenchmarkResult QuickSort(std::vector<int> arr)
{
    BenchmarkResult result;

    auto start = std::chrono::high_resolution_clock::now();

    if (!arr.empty())
    {
        QuickSortRecursive(arr, 0, arr.size() - 1, result);
    }

    auto end = std::chrono::high_resolution_clock::now();

    result.elapsedMs =
        std::chrono::duration<double, std::milli>(end - start).count();

    result.sortedData = arr;
    return result;
}
static void Merge(std::vector<int>& arr,
    int left,
    int mid,
    int right,
    BenchmarkResult& result)
{
    std::vector<int> temp;

    int i = left;
    int j = mid + 1;

    while (i <= mid && j <= right)
    {
        result.comparisons++;

        if (arr[i] <= arr[j])
            temp.push_back(arr[i++]);
        else
            temp.push_back(arr[j++]);

        result.swaps++;
    }

    while (i <= mid)
        temp.push_back(arr[i++]);

    while (j <= right)
        temp.push_back(arr[j++]);

    for (int k = 0; k < temp.size(); k++)
        arr[left + k] = temp[k];
}

static void MergeSortRecursive(std::vector<int>& arr,
    int left,
    int right,
    BenchmarkResult& result)
{
    if (left >= right)
        return;

    int mid = (left + right) / 2;

    MergeSortRecursive(arr, left, mid, result);
    MergeSortRecursive(arr, mid + 1, right, result);

    Merge(arr, left, mid, right, result);
}

BenchmarkResult MergeSort(std::vector<int> arr)
{
    BenchmarkResult result;

    auto start = std::chrono::high_resolution_clock::now();

    if (!arr.empty())
    {
        MergeSortRecursive(arr, 0, arr.size() - 1, result);
    }

    auto end = std::chrono::high_resolution_clock::now();

    result.elapsedMs =
        std::chrono::duration<double, std::milli>(end - start).count();

    result.sortedData = arr;
    return result;
}
BenchmarkResult ShellSort(std::vector<int> arr)
{
    BenchmarkResult result;

    auto start = std::chrono::high_resolution_clock::now();

    int n = arr.size();

    for (int gap = n / 2; gap > 0; gap /= 2)
    {
        for (int i = gap; i < n; i++)
        {
            int temp = arr[i];
            int j = i;

            while (j >= gap)
            {
                result.comparisons++;

                if (arr[j - gap] > temp)
                {
                    arr[j] = arr[j - gap];
                    result.swaps++;
                    j -= gap;
                }
                else
                    break;
            }

            arr[j] = temp;
        }
    }

    auto end = std::chrono::high_resolution_clock::now();

    result.elapsedMs =
        std::chrono::duration<double, std::milli>(end - start).count();
    result.sortedData = arr;
    return result;
}
