# MinGW Windows 8.1 Metro App Demo

This is a demo of Windows 8.1 Metro App on MinGW.

![demo](Images/demo.png)

## Why

To stress test the new C++/WinRT MinGW support mostly, also it is fun.

## Build

To build this, you'll need the following:

- CMake
- C++/WinRT `cppwinrt.exe` in `$PATH`
- Clang/LLVM MinGW toolchain, LLVM/Clang 17 from MSYS2 are tested.

The best way to get a working toolchain is install the following in MSYS2:

```
# CLANG64 Subsystem, with LLVM/Clang
pacman -S mingw-w64-clang-x86_64-{toolchain,cppwinrt,cmake,ninja}
```

With these, just build using CMake:
```
cd src/build
cmake ..
cmake --build .
```

## Deploy

Manual deploy is required for now, and you may need to package your app
in order to sideload on actual Windows 8.1 machines. 

## What works

- XAML layout (load in **runtime** only)
- `IValueConverter` (initialized in code-behind)
- Data binding with `ICustomPropertyProvider` (see `MainWindowViewModel.cpp` and `Property.hpp` on how to implement this, it sucks but eh)
- `ICommand`
- Setting events from code-behind

## What doesn't

- Compiled XAML and `x:Bind`
- Automatically generated control references via `x:Name` (so you'll need to crawl through the logical tree to get to your controls)
- Anything else? Feel free to hack around
