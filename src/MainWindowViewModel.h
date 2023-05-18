#pragma once
#include <winrt/base.h>
#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.Foundation.Collections.h>
#include <winrt/Windows.UI.Xaml.Data.h>

#include "ListItem.h"

namespace winrt
{
    using namespace winrt::Windows::Foundation::Collections;
    using namespace winrt::Windows::UI::Xaml::Data;
    using namespace winrt::Windows::UI::Xaml::Input;
    using namespace winrt::Windows::UI::Xaml::Interop;
}

namespace winrt::CoreAppMinGW::implementation
{
    struct MainWindowViewModel : winrt::implements<MainWindowViewModel, ICustomPropertyProvider, INotifyPropertyChanged>
    {
        MainWindowViewModel();

        hstring Message();
        void Message(hstring const& value);
        hstring UserName();
        void UserName(hstring const& value);
        ICommand GreetingCommand();
        IObservableVector<IInspectable> Items();

        winrt::event_token PropertyChanged(PropertyChangedEventHandler const& handler);
        void PropertyChanged(winrt::event_token const& token) noexcept;

        ICustomProperty GetCustomProperty(hstring const& name);
        ICustomProperty GetIndexedProperty(hstring const& name, TypeName const& type);
        hstring GetStringRepresentation();
        TypeName Type();

        private:
        hstring m_message;
        hstring m_userName;
        ICommand m_greetingCommand{ nullptr };
        winrt::event<PropertyChangedEventHandler> m_propertyChangedEvent;
        IObservableVector<IInspectable> m_items{ nullptr };
        
        static std::map<hstring, ICustomProperty> m_propertyMap;
    };
}
