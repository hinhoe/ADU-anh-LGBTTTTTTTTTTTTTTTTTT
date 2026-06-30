#include "pch.h"
#include "HeaderControl.xaml.h"
#if __has_include("HeaderControl.g.cpp")
#include "HeaderControl.g.cpp"
#endif

using namespace winrt;
using namespace Microsoft::UI::Xaml;

namespace winrt::Algorithm_Benchmark_Tool::implementation
{
    HeaderControl::HeaderControl()
    {
        InitializeComponent();
    }

    void HeaderControl::btnStart_Click(
        Windows::Foundation::IInspectable const&,
        RoutedEventArgs const&)
    {
        m_startEvent(*this, true);
    }

    void HeaderControl::btnPause_Click(
        Windows::Foundation::IInspectable const&,
        RoutedEventArgs const&)
    {
        m_pauseEvent(*this, true);
    }

    void HeaderControl::btnReset_Click(
        Windows::Foundation::IInspectable const&,
        RoutedEventArgs const&)
    {
        m_resetEvent(*this, true);
    }
}