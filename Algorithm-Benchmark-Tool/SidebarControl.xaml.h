#pragma once
#include "SidebarControl.g.h"

namespace winrt::Algorithm_Benchmark_Tool::implementation
{
    struct SidebarControl : SidebarControlT<SidebarControl>
    {
        SidebarControl();

        // Getters để MainWindow đọc
        winrt::hstring ArraySizeText() { return intArrayInput().Text(); }
        winrt::hstring ManualDataText() { return intDataInput().Text(); }

        bool UseBubble() { return chkOption1().IsChecked().GetBoolean(); }
        bool UseInsertion() { return chkOption2().IsChecked().GetBoolean(); }
        bool UseQuick() { return chkOption3().IsChecked().GetBoolean(); }
        bool UseMerge() { return chkOption4().IsChecked().GetBoolean(); }
        bool UseShell() { return chkOption5().IsChecked().GetBoolean(); }

        // Events
        winrt::event_token RandomDataRequested(Windows::Foundation::EventHandler<bool> const& h)
        {
            return m_randomEvent.add(h);
        }
        void RandomDataRequested(winrt::event_token const& t)
        {
            m_randomEvent.remove(t);
        }

        winrt::event_token StartRequested(Windows::Foundation::EventHandler<bool> const& h)
        {
            return m_startEvent.add(h);
        }
        void StartRequested(winrt::event_token const& t)
        {
            m_startEvent.remove(t);
        }

        // Button handlers
        void btnRandomData_Click(Windows::Foundation::IInspectable const&, Microsoft::UI::Xaml::RoutedEventArgs const&);
        void btnStart_Click(Windows::Foundation::IInspectable const&, Microsoft::UI::Xaml::RoutedEventArgs const&);

    private:
        winrt::event<Windows::Foundation::EventHandler<bool>> m_randomEvent;
        winrt::event<Windows::Foundation::EventHandler<bool>> m_startEvent;
    };
}

namespace winrt::Algorithm_Benchmark_Tool::factory_implementation
{
    struct SidebarControl : SidebarControlT<SidebarControl, implementation::SidebarControl> {};
}