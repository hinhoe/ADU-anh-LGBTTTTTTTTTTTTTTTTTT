#pragma once

#include <vector>
#include "BenchmarkResult.h"

BenchmarkResult BubbleSort(std::vector<int> arr);
BenchmarkResult InsertionSort(std::vector<int> arr);
BenchmarkResult QuickSort(std::vector<int> arr);
BenchmarkResult MergeSort(std::vector<int> arr);
BenchmarkResult ShellSort(std::vector<int> arr);