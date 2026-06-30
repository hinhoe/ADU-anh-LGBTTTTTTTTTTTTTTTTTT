#pragma once
#include "AlgorithmCardControl.g.h"
#include <winrt/Windows.Foundation.Collections.h>
#include <vector>

namespace winrt::Algorithm_Benchmark_Tool::implementation
{
    struct AlgorithmCardControl : AlgorithmCardControlT<AlgorithmCardControl>
    {
        AlgorithmCardControl();

        winrt::hstring AlgorithmName() { return m_algorithmName; }
        void AlgorithmName(winrt::hstring const& v)
        {
            m_algorithmName = v;
            txtAlgorithm().Text(v);
        }

        int32_t Comparisons() { return m_comparisons; }
        void Comparisons(int32_t v)
        {
            m_comparisons = v;
            ComparisonsText().Text(winrt::to_hstring(v));
        }

        int32_t Swaps() { return m_swaps; }
        void Swaps(int32_t v)
        {
            m_swaps = v;
            txtSwaps().Text(winrt::to_hstring(v));
        }

        winrt::hstring TimeText() { return m_timeText; }
        void TimeText(winrt::hstring const& v)
        {
            m_timeText = v;
            txtTime().Text(v);
        }

        winrt::hstring StatusText() { return m_statusText; }
        void StatusText(winrt::hstring const& v)
        {
            m_statusText = v;
            txtStatus().Text(v);
        }

        void DrawBars(
            Windows::Foundation::Collections::IVector<int32_t> const& data,
            int32_t highlightIndex);

        void DrawBars(std::vector<int> const& data, int highlightIndex = -1)
        {
            auto v = winrt::single_threaded_vector<int32_t>(
                std::vector<int32_t>(data.begin(), data.end()));
            DrawBars(v, (int32_t)highlightIndex);
        }

    private:
        winrt::hstring m_algorithmName{ L"Algorithm" };
        winrt::hstring m_timeText{ L"0 ms" };
        winrt::hstring m_statusText{ L"Idle" };
        int32_t        m_comparisons{ 0 };
        int32_t        m_swaps{ 0 };
    };
}

namespace winrt::Algorithm_Benchmark_Tool::factory_implementation
{
    struct AlgorithmCardControl
        : AlgorithmCardControlT<AlgorithmCardControl, implementation::AlgorithmCardControl> {
    };
}