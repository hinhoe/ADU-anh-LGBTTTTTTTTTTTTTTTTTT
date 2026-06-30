#pragma once
#include "AnalyticsChartControl.g.h"
#include <vector>
#include <string>

namespace winrt::Algorithm_Benchmark_Tool::implementation
{
    struct ChartEntry
    {
        std::wstring label;
        int32_t      value;
        Windows::UI::Color color;
    };

    struct AnalyticsChartControl : AnalyticsChartControlT<AnalyticsChartControl>
    {
        AnalyticsChartControl();

        void UpdateCharts(
            int32_t bubbleComp, int32_t bubbleSwap,
            int32_t insertComp, int32_t insertSwap,
            int32_t quickComp, int32_t quickSwap,
            int32_t mergeComp, int32_t mergeSwap,
            int32_t shellComp, int32_t shellSwap);

    private:
        void DrawBarChart(
            Microsoft::UI::Xaml::Controls::Canvas const& canvas,
            std::vector<ChartEntry> const& entries);
    };
}

namespace winrt::Algorithm_Benchmark_Tool::factory_implementation
{
    struct AnalyticsChartControl
        : AnalyticsChartControlT<AnalyticsChartControl, implementation::AnalyticsChartControl> {
    };
}