#include "pch.h"
#include "SidebarControl.xaml.h"
#if __has_include("SidebarControl.g.cpp")
#include "SidebarControl.g.cpp"
#endif

using namespace winrt;
using namespace Microsoft::UI::Xaml;

namespace winrt::Algorithm_Benchmark_Tool::implementation
{
    SidebarControl::SidebarControl()
    {
        InitializeComponent();
    }

    void SidebarControl::btnRandomData_Click(
        Windows::Foundation::IInspectable const&,
        RoutedEventArgs const&)
    {
        m_randomEvent(*this, true);
    }

    void SidebarControl::btnStart_Click(
        Windows::Foundation::IInspectable const&,
        RoutedEventArgs const&)
    {
        m_startEvent(*this, true);
    }
}