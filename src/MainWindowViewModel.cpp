#include "MainWindowViewModel.h"
#include "SimpleCommand.h"

#include <string>

namespace winrt::CoreAppMinGW::implementation {
    MainWindowViewModel::MainWindowViewModel() {
        GreetingCommand.value = winrt::make<SimpleCommand>([this](IInspectable parameter) {
            std::wstring str;
            str += L"Hello, ";
            str += this->UserName().c_str();
            this->Message(str.c_str());
        });

        Items.value = winrt::single_threaded_observable_vector<IInspectable>({
            winrt::make<ListItem>(L"WinRT meets MinGW", L"it really works"),
            winrt::make<ListItem>(L"FOSS Rocks", L"always have been"),
        });

        TextColor.value = winrt::make<ColorValue>(127, 255, 0);
    }
} // namespace winrt::CoreAppMinGW::implementation
