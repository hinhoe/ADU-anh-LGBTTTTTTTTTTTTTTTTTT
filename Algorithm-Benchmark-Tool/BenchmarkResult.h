#pragma once
#include <vector>

struct BenchmarkResult
{
    int comparisons = 0;
    int swaps = 0;
    double elapsedMs = 0;
    std::vector<int> sortedData;   // ← THÊM: lưu mảng sau khi sắp xếp
};