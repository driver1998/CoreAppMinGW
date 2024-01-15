#pragma once
#include <winrt/Windows.Foundation.Collections.h>
#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.UI.Xaml.Data.h>
#include <winrt/base.h>

#include "ListItem.h"
#include "ColorValue.h"
#include "Property.hpp"

namespace winrt {
    using namespace winrt::Windows::Foundation::Collections;
    using namespace winrt::Windows::UI::Xaml::Data;
    using namespace winrt::Windows::UI::Xaml::Input;
    using namespace winrt::Windows::UI::Xaml::Interop;
} // namespace winrt

namespace winrt::CoreAppMinGW::implementation {
    struct MainWindowViewModel
        : winrt::implements<MainWindowViewModel, ICustomPropertyProvider, INotifyPropertyChanged>,
          PropertyObject<MainWindowViewModel> {
        MainWindowViewModel();

        std::function<void(hstring const &name)> onPropertyChanged = [this](hstring const &name) {
            PropertyChanged.event(*this, PropertyChangedEventArgs{name});
        };

        Property<hstring> Message{L"Message", winrt::xaml_typename<hstring>(), onPropertyChanged};
        Property<hstring> UserName{L"UserName", winrt::xaml_typename<hstring>(), onPropertyChanged};
        Property<ICommand> GreetingCommand{L"GreetingCommand", winrt::xaml_typename<ICommand>(),
                                           onPropertyChanged};
        Property<IObservableVector<IInspectable>> Items{
            L"Items", winrt::xaml_typename<IObservableVector<IInspectable>>(), onPropertyChanged};
        Property<IInspectable> TextColor{L"TextColor", winrt::xaml_typename<IInspectable>(), onPropertyChanged};

        std::vector<IProperty *> PropertyList = {&Message, &UserName, &GreetingCommand, &Items, &TextColor};
        Event<PropertyChangedEventHandler> PropertyChanged;
    };
} // namespace winrt::CoreAppMinGW::implementation
