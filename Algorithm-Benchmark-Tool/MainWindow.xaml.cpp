#include "pch.h"
#include "MainWindow.xaml.h"
#if __has_include("MainWindow.g.cpp")
#include "MainWindow.g.cpp"
#endif

#include "SortingAlgorithms.h"
#include <string>
#include <vector>
#include <random>
#include <algorithm>
#include <winrt/Windows.Foundation.Collections.h>

using namespace winrt;
using namespace Microsoft::UI::Xaml;

namespace winrt::Algorithm_Benchmark_Tool::implementation
{
    // ── Helper ───────────────────────────────────────────────────
    static Windows::Foundation::Collections::IVector<int32_t>
        ToIVector(std::vector<int> const& v)
    {
        return winrt::single_threaded_vector<int32_t>(
            std::vector<int32_t>(v.begin(), v.end()));
    }

    // ── Constructor ──────────────────────────────────────────────
    MainWindow::MainWindow()
    {
        InitializeComponent();

        HeaderCtrl().StartRequested(
            [this](auto&&, bool) { OnStartRequested(nullptr, true); });
        HeaderCtrl().PauseRequested(
            [this](auto&&, bool) { OnPauseRequested(nullptr, true); });
        HeaderCtrl().ResetRequested(
            [this](auto&&, bool) { OnResetRequested(nullptr, true); });

        Sidebar().RandomDataRequested(
            [this](auto&&, bool) { OnRandomDataRequested(nullptr, true); });
        Sidebar().StartRequested(
            [this](auto&&, bool) { OnStartRequested(nullptr, true); });
    }

    // ── Start ────────────────────────────────────────────────────
    void MainWindow::OnStartRequested(Windows::Foundation::IInspectable const&, bool)
    {
        auto manualText = Sidebar().ManualDataText();
        if (!manualText.empty())
        {
            m_data = ParseManualInput(manualText);
        }

        if (m_data.empty())
        {
            m_data = GenerateRandom(50);
        }

        RunBenchmark();
    }

    // ── Pause ────────────────────────────────────────────────────
    void MainWindow::OnPauseRequested(Windows::Foundation::IInspectable const&, bool)
    {
        // placeholder
    }

    // ── Reset ────────────────────────────────────────────────────
    void MainWindow::OnResetRequested(Windows::Foundation::IInspectable const&, bool)
    {
        m_data.clear();
        ResetCards();
    }

    // ── Random Data ──────────────────────────────────────────────
    void MainWindow::OnRandomDataRequested(Windows::Foundation::IInspectable const&, bool)
    {
        auto manualText = Sidebar().ManualDataText();

        if (!manualText.empty())
        {
            // Có dữ liệu nhập tay → dùng đúng dữ liệu đó
            m_data = ParseManualInput(manualText);
        }
        else
        {
            // Không nhập gì → tạo ngẫu nhiên theo độ dài mảng
            int size = 50;
            auto sizeText = Sidebar().ArraySizeText();
            if (!sizeText.empty())
            {
                try { size = std::stoi(std::wstring(sizeText)); }
                catch (...) { size = 50; }
            }
            size = std::clamp(size, 2, 500);
            m_data = GenerateRandom(size);
        }

        // Vẽ dữ liệu CHƯA sắp xếp lên tất cả card để xem trước
        auto iv = ToIVector(m_data);
        BubbleCard().DrawBars(iv, -1);
        QuickCard().DrawBars(iv, -1);
        MergeCard().DrawBars(iv, -1);
        InsertionCard().DrawBars(iv, -1);
        ShellCard().DrawBars(iv, -1);
    }
    // ── RunBenchmark ─────────────────────────────────────────────
    void MainWindow::RunBenchmark()
    {
        bool runBubble = Sidebar().UseBubble();
        bool runInsertion = Sidebar().UseInsertion();
        bool runQuick = Sidebar().UseQuick();
        bool runMerge = Sidebar().UseMerge();
        bool runShell = Sidebar().UseShell();
        bool runAll = !runBubble && !runInsertion && !runQuick && !runMerge && !runShell;

        BenchmarkResult bubble{}, insertion{}, quick{}, merge{}, shell{};

        auto setRunning = [](auto& card, winrt::hstring name) {
            card.AlgorithmName(name);
            card.StatusText(L"Running");
            card.TimeText(L"...");
            };

        if (runAll || runBubble)
        {
            setRunning(BubbleCard(), L"Bubble Sort");
            bubble = BubbleSort(m_data);
            BubbleCard().Comparisons(bubble.comparisons);
            BubbleCard().Swaps(bubble.swaps);
            BubbleCard().TimeText(winrt::to_hstring((int)bubble.elapsedMs) + L" ms");
            BubbleCard().StatusText(L"Done");
        }

        if (runAll || runInsertion)
        {
            setRunning(InsertionCard(), L"Insertion Sort");
            insertion = InsertionSort(m_data);
            InsertionCard().Comparisons(insertion.comparisons);
            InsertionCard().Swaps(insertion.swaps);
            InsertionCard().TimeText(winrt::to_hstring((int)insertion.elapsedMs) + L" ms");
            InsertionCard().StatusText(L"Done");
        }

        if (runAll || runQuick)
        {
            setRunning(QuickCard(), L"Quick Sort");
            quick = QuickSort(m_data);
            QuickCard().Comparisons(quick.comparisons);
            QuickCard().Swaps(quick.swaps);
            QuickCard().TimeText(winrt::to_hstring((int)quick.elapsedMs) + L" ms");
            QuickCard().StatusText(L"Done");
        }

        if (runAll || runMerge)
        {
            setRunning(MergeCard(), L"Merge Sort");
            merge = MergeSort(m_data);
            MergeCard().Comparisons(merge.comparisons);
            MergeCard().Swaps(merge.swaps);
            MergeCard().TimeText(winrt::to_hstring((int)merge.elapsedMs) + L" ms");
            MergeCard().StatusText(L"Done");
        }

        if (runAll || runShell)
        {
            setRunning(ShellCard(), L"Shell Sort");
            shell = ShellSort(m_data);
            ShellCard().Comparisons(shell.comparisons);
            ShellCard().Swaps(shell.swaps);
            ShellCard().TimeText(winrt::to_hstring((int)shell.elapsedMs) + L" ms");
            ShellCard().StatusText(L"Done");
        }

        // Vẽ bar chart kết quả
// Vẽ bar chart kết quả — dùng sortedData riêng của từng thuật toán
        if (runAll || runBubble)
            BubbleCard().DrawBars(ToIVector(bubble.sortedData), -1);
        if (runAll || runInsertion)
            InsertionCard().DrawBars(ToIVector(insertion.sortedData), -1);
        if (runAll || runQuick)
            QuickCard().DrawBars(ToIVector(quick.sortedData), -1);
        if (runAll || runMerge)
            MergeCard().DrawBars(ToIVector(merge.sortedData), -1);
        if (runAll || runShell)
            ShellCard().DrawBars(ToIVector(shell.sortedData), -1);

        // Analytics chart
        Charts().UpdateCharts(
            bubble.comparisons, bubble.swaps,
            insertion.comparisons, insertion.swaps,
            quick.comparisons, quick.swaps,
            merge.comparisons, merge.swaps,
            shell.comparisons, shell.swaps);
    }

    // ── ResetCards ───────────────────────────────────────────────
    void MainWindow::ResetCards()
    {
        auto reset = [](auto& card, winrt::hstring name) {
            card.AlgorithmName(name);
            card.StatusText(L"Idle");
            card.TimeText(L"0 ms");
            card.Comparisons(0);
            card.Swaps(0);
            };
        reset(BubbleCard(), L"Bubble Sort");
        reset(InsertionCard(), L"Insertion Sort");
        reset(QuickCard(), L"Quick Sort");
        reset(MergeCard(), L"Merge Sort");
        reset(ShellCard(), L"Shell Sort");
    }

    // ── ParseManualInput ─────────────────────────────────────────
    std::vector<int> MainWindow::ParseManualInput(winrt::hstring const& text)
    {
        std::vector<int> result;
        std::wstring ws{ text };
        std::wstring token;
        size_t start = 0, pos = 0;
        while ((pos = ws.find(L',', start)) != std::wstring::npos)
        {
            token = ws.substr(start, pos - start);
            try { result.push_back(std::stoi(token)); }
            catch (...) {}
            start = pos + 1;
        }
        token = ws.substr(start);
        try { result.push_back(std::stoi(token)); }
        catch (...) {}
        return result;
    }

    // ── GenerateRandom ───────────────────────────────────────────
    std::vector<int> MainWindow::GenerateRandom(int size)
    {
        std::mt19937 rng{ std::random_device{}() };
        std::uniform_int_distribution<int> dist(1, 1000);
        std::vector<int> v(size);
        std::generate(v.begin(), v.end(), [&] { return dist(rng); });
        return v;
    }

} // namespace winrt::Algorithm_Benchmark_Tool::implementation