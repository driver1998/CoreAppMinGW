#include "ListItem.h"

namespace winrt::CoreAppMinGW::implementation {
    ListItem::ListItem(hstring const &name, hstring const &value) {
        Name.value = name;
        Value.value = value;
    }
} // namespace winrt::CoreAppMinGW::implementation