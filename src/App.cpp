#define WIN32_MEAN_AND_LEAN
#include <windows.h>

#ifdef GetCurrentTime
#undef GetCurrentTime
#endif

#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.UI.Xaml.Controls.h>
#include <winrt/Windows.UI.Xaml.h>
#include <winrt/base.h>

#include "MainWindowView.h"

namespace winrt {
    using namespace Windows::UI::Xaml;
    using namespace Windows::ApplicationModel::Activation;
    using namespace Windows::UI::Xaml::Controls;
} // namespace winrt

namespace winrt::CoreAppMinGW::implementation {
    struct App : ApplicationT<App> {
        void OnLaunched(LaunchActivatedEventArgs const &args) {
            auto window = Window::Current();
            auto view = winrt::make<MainWindowView>();
            window.Content(view);
            window.Activate();
        }
    };
} // namespace winrt::CoreAppMinGW::implementation

int WINAPI wWinMain(HINSTANCE, HINSTANCE, PWSTR, int) {
    winrt::init_apartment();
    winrt::Application::Start(
        [](auto &&) { winrt::make<winrt::CoreAppMinGW::implementation::App>(); });
    return 0;
}
