#include "pch.h"
#include "AlgorithmCardControl.xaml.h"
#if __has_include("AlgorithmCardControl.g.cpp")
#include "AlgorithmCardControl.g.cpp"
#endif

#include <algorithm>
#include <winrt/Windows.Foundation.Collections.h>

using namespace winrt;
using namespace Microsoft::UI::Xaml;
using namespace Microsoft::UI::Xaml::Controls;
using namespace Microsoft::UI::Xaml::Media;
using namespace Windows::UI;
namespace MUIShapes = Microsoft::UI::Xaml::Shapes;

namespace winrt::Algorithm_Benchmark_Tool::implementation
{
    AlgorithmCardControl::AlgorithmCardControl()
    {
        InitializeComponent();
    }

    void AlgorithmCardControl::DrawBars(
        Windows::Foundation::Collections::IVector<int32_t> const& data,
        int32_t highlightIndex)
    {
        auto canvas = SortingCanvas();
        canvas.Children().Clear();

        uint32_t n = data.Size();
        if (n == 0) return;

        double canvasW = canvas.ActualWidth();
        double canvasH = canvas.ActualHeight();
        if (canvasW <= 0 || canvasH <= 0) return;

        int32_t maxVal = 1;
        for (uint32_t i = 0; i < n; i++)
            if (data.GetAt(i) > maxVal) maxVal = data.GetAt(i);

        double barW = canvasW / n;

        for (uint32_t i = 0; i < n; i++)
        {
            double barH = (double)data.GetAt(i) / maxVal * (canvasH - 4);

            MUIShapes::Rectangle rect;
            rect.Width(barW - 1);
            rect.Height(barH < 1 ? 1 : barH);

            Color fillColor = ((int32_t)i == highlightIndex)
                ? Color{ 255, 250, 204, 21 }
            : Color{ 255,  59, 130, 246 };

            rect.Fill(SolidColorBrush{ fillColor });
            Canvas::SetLeft(rect, i * barW);
            Canvas::SetTop(rect, canvasH - barH);
            canvas.Children().Append(rect);
        }
    }

} // namespace winrt::Algorithm_Benchmark_Tool::implementation