#include "ColorValue.h"

namespace winrt::CoreAppMinGW::implementation {
    ColorValue::ColorValue(uint8_t r, uint8_t g, uint8_t b) {
        Red.value = r;
        Green.value = g;
        Blue.value = b;
        Value.value = Color{255, r, g, b};
    }

    ColorValue::ColorValue(Color c) {
        Red.value = c.R;
        Green.value = c.G;
        Blue.value = c.B;
        Value.value = c;
    }

    void ColorValue::OnPropertyChanged(hstring const &name) {
        if (name == L"Value") {
            Red.value = Value.value.R;
            Green.value = Value.value.G;
            Blue.value = Value.value.B;
            PropertyChanged.event(*this, PropertyChangedEventArgs{Red.Name()});
            PropertyChanged.event(*this, PropertyChangedEventArgs{Green.Name()});
            PropertyChanged.event(*this, PropertyChangedEventArgs{Blue.Name()});
        } else {
            Value.value = Color{255, (uint8_t)Red.value, (uint8_t)Green.value, (uint8_t)Blue.value};
            PropertyChanged.event(*this, PropertyChangedEventArgs{Value.Name()});
        }
        PropertyChanged.event(*this, PropertyChangedEventArgs{name});
    }
} // namespace winrt::CoreAppMinGW::implementation