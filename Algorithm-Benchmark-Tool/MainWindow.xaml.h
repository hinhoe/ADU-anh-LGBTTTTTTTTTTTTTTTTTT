#pragma once
#include "MainWindow.g.h"
#include "SortingAlgorithms.h"
#include <vector>
#include <string>
#include <sstream>

namespace winrt::Algorithm_Benchmark_Tool::implementation
{
    struct MainWindow : MainWindowT<MainWindow>
    {
        MainWindow();

    private:
        std::vector<int> m_data;

        void OnStartRequested(Windows::Foundation::IInspectable const&, bool);
        void OnPauseRequested(Windows::Foundation::IInspectable const&, bool);
        void OnResetRequested(Windows::Foundation::IInspectable const&, bool);
        void OnRandomDataRequested(Windows::Foundation::IInspectable const&, bool);

        void RunBenchmark();
        void ResetCards();
        std::vector<int> ParseManualInput(winrt::hstring const& text);
        std::vector<int> GenerateRandom(int size);
    };
}

namespace winrt::Algorithm_Benchmark_Tool::factory_implementation
{
    struct MainWindow : MainWindowT<MainWindow, implementation::MainWindow> {};
}