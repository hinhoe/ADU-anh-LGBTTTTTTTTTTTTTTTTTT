#pragma once
#include "HeaderControl.g.h"

namespace winrt::Algorithm_Benchmark_Tool::implementation
{
    struct HeaderControl : HeaderControlT<HeaderControl>
    {
        HeaderControl();

        // Events để MainWindow lắng nghe
        winrt::event_token StartRequested(Windows::Foundation::EventHandler<bool> const& handler)
        {
            return m_startEvent.add(handler);
        }
        void StartRequested(winrt::event_token const& token)
        {
            m_startEvent.remove(token);
        }

        winrt::event_token PauseRequested(Windows::Foundation::EventHandler<bool> const& handler)
        {
            return m_pauseEvent.add(handler);
        }
        void PauseRequested(winrt::event_token const& token)
        {
            m_pauseEvent.remove(token);
        }

        winrt::event_token ResetRequested(Windows::Foundation::EventHandler<bool> const& handler)
        {
            return m_resetEvent.add(handler);
        }
        void ResetRequested(winrt::event_token const& token)
        {
            m_resetEvent.remove(token);
        }

        // Button click handlers (khai báo trong XAML)
        void btnStart_Click(Windows::Foundation::IInspectable const&, Microsoft::UI::Xaml::RoutedEventArgs const&);
        void btnPause_Click(Windows::Foundation::IInspectable const&, Microsoft::UI::Xaml::RoutedEventArgs const&);
        void btnReset_Click(Windows::Foundation::IInspectable const&, Microsoft::UI::Xaml::RoutedEventArgs const&);

    private:
        winrt::event<Windows::Foundation::EventHandler<bool>> m_startEvent;
        winrt::event<Windows::Foundation::EventHandler<bool>> m_pauseEvent;
        winrt::event<Windows::Foundation::EventHandler<bool>> m_resetEvent;
    };
}

namespace winrt::Algorithm_Benchmark_Tool::factory_implementation
{
    struct HeaderControl : HeaderControlT<HeaderControl, implementation::HeaderControl> {};
}