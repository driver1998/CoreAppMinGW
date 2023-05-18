#include "MainWindowViewModel.h"
#include "CustomProperty.h"
#include "SimpleCommand.h"

#include <cwchar>
#include <string>

namespace winrt::CoreAppMinGW::implementation
{
    MainWindowViewModel::MainWindowViewModel()
    {
        m_greetingCommand = winrt::make<SimpleCommand>([this](IInspectable parameter) {
            std::wstring str;
            str += L"Hello, ";
            str += this->UserName().c_str();
            this->Message(str.c_str());
        });

        m_items = winrt::single_threaded_observable_vector<IInspectable>({
            winrt::make<ListItem>(L"WinRT meets MinGW", L"it really works"),
            winrt::make<ListItem>(L"FOSS Rocks", L"always have been"),
        });
    }
    hstring MainWindowViewModel::Message()
    {
        return m_message;
    }
    void MainWindowViewModel::Message(hstring const& value)
    {
        m_message = value;
        m_propertyChangedEvent(*this, PropertyChangedEventArgs{L"Message"});
    }
    hstring MainWindowViewModel::UserName()
    {
        return m_userName;
    }
    void MainWindowViewModel::UserName(hstring const& value)
    {
        m_userName = value;
        m_propertyChangedEvent(*this, PropertyChangedEventArgs{L"UserName"});
    }
    ICommand MainWindowViewModel::GreetingCommand()
    {
        return m_greetingCommand;
    }
    IObservableVector<IInspectable> MainWindowViewModel::Items()
    {
        return m_items;
    }

    /* INotifyPropertyChanged*/
    winrt::event_token MainWindowViewModel::PropertyChanged(PropertyChangedEventHandler const& handler)
    {
        return m_propertyChangedEvent.add(handler);
    }
    void MainWindowViewModel::PropertyChanged(winrt::event_token const& token) noexcept
    {
        m_propertyChangedEvent.remove(token);
    }

    /* ICustomPropertyProvider */
    ICustomProperty MainWindowViewModel::GetCustomProperty(hstring const& name)
    {
        _putws(name.c_str());
        if (m_propertyMap.contains(name))
        {
            return m_propertyMap[name];
        }
        else
        {
            return nullptr;
        }
    }
    ICustomProperty MainWindowViewModel::GetIndexedProperty(hstring const& name, TypeName const& type)
    {
        throw hresult_not_implemented();
    }
    hstring MainWindowViewModel::GetStringRepresentation()
    {
        return L"CoreAppMinGW.MainWindowViewModel";
    }
    TypeName MainWindowViewModel::Type()
    {
        return TypeName {
            .Name = L"CoreAppMinGW.MainWindowViewModel",
            .Kind = TypeKind::Custom
        };
    }

    std::map<hstring, ICustomProperty> MainWindowViewModel::m_propertyMap
    {
        {
            L"Message",
            winrt::make<CustomProperty>(
                CustomPropertyMetaData {
                    .CanRead = true,
                    .CanWrite = true,
                    .Name = L"Message",
                    .Type = TypeName {
                        .Name = L"String",
                        .Kind = TypeKind::Primitive
                    },
                    .Getter = [](IInspectable obj) -> IInspectable
                    { 
                        return winrt::box_value(obj.as<MainWindowViewModel>()->Message());
                    },
                    .Setter = [](IInspectable obj, IInspectable value)
                    { 
                        obj.as<MainWindowViewModel>()->Message(winrt::unbox_value<winrt::hstring>(value));
                    }
                }
            )
        },
        {
            L"UserName",
            winrt::make<CustomProperty>(
                CustomPropertyMetaData {
                    .CanRead = true,
                    .CanWrite = true,
                    .Name = L"UserName",
                    .Type = TypeName {
                        .Name = L"String",
                        .Kind = TypeKind::Primitive
                    },
                    .Getter = [](IInspectable obj) -> IInspectable
                    { 
                        return winrt::box_value(obj.as<MainWindowViewModel>()->UserName());
                    },
                    .Setter = [](IInspectable obj, IInspectable value)
                    { 
                        obj.as<MainWindowViewModel>()->UserName(winrt::unbox_value<winrt::hstring>(value));
                    }
                }
            )
        },
        {
            L"GreetingCommand",
            winrt::make<CustomProperty>(
                CustomPropertyMetaData {
                    .CanRead = true,
                    .CanWrite = false,
                    .Name = L"GreetingCommand",
                    .Type = TypeName {
                        .Name = L"Windows.UI.Xaml.Input.ICommand",
                        .Kind = TypeKind::Metadata
                    },
                    .Getter = [](IInspectable obj) -> IInspectable
                    { 
                        return obj.as<MainWindowViewModel>()->GreetingCommand();
                    }
                }
            )
        },
        {
            L"Items",
            winrt::make<CustomProperty>(
                CustomPropertyMetaData {
                    .CanRead = true,
                    .CanWrite = false,
                    .Name = L"Items",
                    .Type = TypeName {
                        .Name = L"Windows.Foundation.Collections.IObservableVector",
                        .Kind = TypeKind::Metadata
                    },
                    .Getter = [](IInspectable obj) -> IInspectable
                    { 
                        return obj.as<MainWindowViewModel>()->Items();
                    }
                }
            )
        },
    };
}
