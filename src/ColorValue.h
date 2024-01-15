#pragma once
#include <cstdint>
#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.UI.h>
#include <winrt/Windows.UI.Xaml.Data.h>
#include <winrt/Windows.UI.Xaml.Media.h>
#include <winrt/base.h>

#include "Property.hpp"

namespace winrt {
    using namespace winrt::Windows::UI;
    using namespace winrt::Windows::UI::Xaml::Data;
    using namespace winrt::Windows::UI::Xaml::Input;
    using namespace winrt::Windows::UI::Xaml::Interop;    
} // namespace winrt

namespace winrt::CoreAppMinGW::implementation {
    struct ColorValue : winrt::implements<ColorValue, ICustomPropertyProvider, INotifyPropertyChanged>,
                      PropertyObject<ColorValue> {
        ColorValue(uint8_t r, uint8_t g, uint8_t b);
        ColorValue(Color c);

        void OnPropertyChanged(hstring const& name);

        std::function<void(hstring const &name)> onPropertyChanged = [this](hstring const &name) {
            this->OnPropertyChanged(name);
        };

        Property<double> Red{L"Red", winrt::xaml_typename<double>(), onPropertyChanged};
        Property<double> Green{L"Green", winrt::xaml_typename<double>(), onPropertyChanged};
        Property<double> Blue{L"Blue", winrt::xaml_typename<double>(), onPropertyChanged};
        Property<Color> Value{L"Value", winrt::xaml_typename<Color>(), onPropertyChanged};

        std::vector<IProperty *> PropertyList = {&Red, &Green, &Blue, &Value};
        Event<PropertyChangedEventHandler> PropertyChanged;
    };
} // namespace winrt::CoreAppMinGW::implementation
