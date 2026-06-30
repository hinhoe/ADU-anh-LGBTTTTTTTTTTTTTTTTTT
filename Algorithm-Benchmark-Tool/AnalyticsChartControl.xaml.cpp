#include "pch.h"
#include "AnalyticsChartControl.xaml.h"
#if __has_include("AnalyticsChartControl.g.cpp")
#include "AnalyticsChartControl.g.cpp"
#endif

#include <winrt/Microsoft.UI.Xaml.Shapes.h>
#include <winrt/Microsoft.UI.Xaml.Media.h>
#include <winrt/Microsoft.UI.Xaml.Controls.h>

using namespace winrt;
using namespace Microsoft::UI::Xaml;
using namespace Microsoft::UI::Xaml::Controls;
using namespace Microsoft::UI::Xaml::Media;
using namespace Windows::UI;

// Không dùng "using namespace Shapes" — dùng alias để tránh ambiguous
namespace MUIShapes = Microsoft::UI::Xaml::Shapes;

namespace winrt::Algorithm_Benchmark_Tool::implementation
{
    AnalyticsChartControl::AnalyticsChartControl()
    {
        InitializeComponent();
    }

    void AnalyticsChartControl::UpdateCharts(
        int32_t bubbleComp, int32_t bubbleSwap,
        int32_t insertComp, int32_t insertSwap,
        int32_t quickComp, int32_t quickSwap,
        int32_t mergeComp, int32_t mergeSwap,
        int32_t shellComp, int32_t shellSwap)
    {
        Color cBubble = { 255,  59, 130, 246 };
        Color cInsertion = { 255, 139,  92, 246 };
        Color cQuick = { 255,  34, 197,  94 };
        Color cMerge = { 255, 250, 204,  21 };
        Color cShell = { 255, 239,  68,  68 };

        std::vector<ChartEntry> compEntries =
        {
            { L"Bubble",    bubbleComp, cBubble    },
            { L"Insertion", insertComp, cInsertion },
            { L"Quick",     quickComp,  cQuick     },
            { L"Merge",     mergeComp,  cMerge     },
            { L"Shell",     shellComp,  cShell     },
        };

        std::vector<ChartEntry> swapEntries =
        {
            { L"Bubble",    bubbleSwap, cBubble    },
            { L"Insertion", insertSwap, cInsertion },
            { L"Quick",     quickSwap,  cQuick     },
            { L"Merge",     mergeSwap,  cMerge     },
            { L"Shell",     shellSwap,  cShell     },
        };

        DrawBarChart(ComparisonsCanvas(), compEntries);
        DrawBarChart(SwapsCanvas(), swapEntries);
    }

    void AnalyticsChartControl::DrawBarChart(
        Canvas const& canvas,
        std::vector<ChartEntry> const& entries)
    {
        canvas.Children().Clear();

        double W = canvas.ActualWidth();
        double H = canvas.ActualHeight();
        if (W <= 0 || H <= 0) return;

        int32_t maxVal = 1;
        for (auto& e : entries)
            if (e.value > maxVal) maxVal = e.value;

        int    n = (int)entries.size();
        double padding = 8.0;
        double barW = (W - padding * (n + 1)) / n;
        double labelH = 18.0;

        for (int i = 0; i < n; i++)
        {
            double barH = (double)entries[i].value / maxVal * (H - labelH - 4);
            double x = padding + i * (barW + padding);
            double y = H - labelH - barH;

            // Cột — dùng MUIShapes::Rectangle tránh ambiguous
            MUIShapes::Rectangle rect;
            rect.Width(barW);
            rect.Height(barH < 1 ? 1 : barH);
            rect.Fill(SolidColorBrush{ entries[i].color });
            rect.RadiusX(3);
            rect.RadiusY(3);
            Canvas::SetLeft(rect, x);
            Canvas::SetTop(rect, y);
            canvas.Children().Append(rect);

            // Label tên
            TextBlock tb;
            tb.Text(winrt::hstring{ entries[i].label });
            tb.FontSize(10);
            tb.Foreground(SolidColorBrush{ Color{ 255, 148, 163, 184 } });
            tb.Width(barW);
            tb.TextAlignment(Microsoft::UI::Xaml::TextAlignment::Center);
            Canvas::SetLeft(tb, x);
            Canvas::SetTop(tb, H - labelH + 2);
            canvas.Children().Append(tb);

            // Giá trị trên đỉnh cột
            if (entries[i].value > 0)
            {
                TextBlock val;
                val.Text(winrt::to_hstring(entries[i].value));
                val.FontSize(9);
                val.Foreground(SolidColorBrush{ Color{ 255, 255, 255, 255 } });
                val.Width(barW);
                val.TextAlignment(Microsoft::UI::Xaml::TextAlignment::Center);
                Canvas::SetLeft(val, x);
                Canvas::SetTop(val, y - 14);
                canvas.Children().Append(val);
            }
        }
    }

} // namespace winrt::Algorithm_Benchmark_Tool::implementation