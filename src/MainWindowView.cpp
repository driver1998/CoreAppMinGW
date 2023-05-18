#include <sstream>
#define WIN32_MEAN_AND_LEAN
#include <windows.h>

#ifdef GetCurrentTime
#undef GetCurrentTime
#endif

#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.Foundation.Collections.h>
#include <winrt/Windows.UI.Core.h>
#include <winrt/Windows.UI.Xaml.h>
#include <winrt/Windows.UI.Xaml.Controls.h>
#include <winrt/Windows.UI.Xaml.Controls.Primitives.h>
#include <winrt/Windows.UI.Xaml.Input.h>

#include "MainWindowView.h"
#include "MainWindowViewModel.h"
#include "NegativeDoubleConverter.h"

#include <string>
#include <sstream>

namespace winrt
{
    using namespace winrt::Windows::Foundation;
    using namespace winrt::Windows::UI::Xaml;
    using namespace winrt::Windows::UI::Xaml::Controls;
}

namespace winrt::CoreAppMinGW::implementation
{
    void MainWindowView::InitializeComponent()
    {
        Resources().Insert(
            winrt::box_value(L"NegativeDoubleConverter"), 
            winrt::make<NegativeDoubleConverter>()
        );

        Uri uri(L"ms-appx:///MainWindowView.xaml");
        Application::LoadComponent(*this, uri);

        auto viewModel = winrt::make_self<MainWindowViewModel>();
        viewModel->UserName(L"MinGW");
        DataContext(viewModel.as<IInspectable>());
        viewModel->GreetingCommand().Execute(nullptr);

        auto btn2 = this->FindName(L"btn2").as<Button>();
        if (btn2)
        {
            btn2.Click([](IInspectable const& sender, RoutedEventArgs const& args) -> winrt::fire_and_forget {
                ContentDialog dialog;
                dialog.Title(winrt::box_value(L"MinGW UWP Demo"));

                bool isAppContainer = false;
                bool isCoreWindow = Windows::UI::Core::CoreWindow::GetForCurrentThread() != nullptr;
                std::ostringstream oss;                

                {
                    HANDLE hProcess = GetCurrentProcess();
                    HANDLE hToken;
                    OpenProcessToken(hProcess, TOKEN_QUERY, &hToken);

                    DWORD infoLength = 0, returnLength = 0;
                    GetTokenInformation(hToken, TokenIsAppContainer, nullptr, 0, &infoLength);

                    void* info = malloc(infoLength);
                    GetTokenInformation(hToken, TokenIsAppContainer, info, infoLength, &returnLength);
                    
                    isAppContainer = (*(DWORD*)info) > 0;
                    free(info);
                    CloseHandle(hToken);
                }

                oss << std::boolalpha;
                oss << "IsCoreWindow: " << isCoreWindow << "\n";
                oss << "IsAppContainer: " << isAppContainer << "\n";

                #if defined(__GNUC__) && !defined(__clang__)
                    oss << "Compiler: GCC " << __GNUC__ << "." << __GNUC_MINOR__ << "." << __GNUC_PATCHLEVEL__ << "\n";
                #endif

                #if defined(__clang__)
                    oss << "Compiler: Clang " __clang_version__ "\n";
                #endif

                #ifdef __MINGW32__
                    oss << "SDK: MinGW-w64 " __MINGW64_VERSION_STR "\n";
                #endif

                dialog.Content(winrt::box_value(winrt::to_hstring(oss.str())));
                dialog.CloseButtonText(L"OK");
                co_await dialog.ShowAsync();
            });
        }
    }
}
