cmake_minimum_required(VERSION 3.5.0)
project(CoreAppMinGW VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

if(CMAKE_SYSTEM_PROCESSOR MATCHES "x86|AMD64")
    set(CMAKE_CXX_FLAGS "-mcx16")
endif()

set(CMAKE_EXE_LINKER_FLAGS "-mwindows -municode -static")

set(CPPWINRT_INPUT "references/Windows.winmd")
set(CPPWINRT_OUTPUT_DIR "${CMAKE_BINARY_DIR}/cppwinrt")

add_custom_target(CppWinRT_HeaderGen
    COMMAND
        cppwinrt.exe -pch . -input ${CPPWINRT_INPUT} -output ${CPPWINRT_OUTPUT_DIR}
    WORKING_DIRECTORY
        ${CMAKE_CURRENT_SOURCE_DIR}
    COMMENT
        "Generating C++/WinRT Headers...")

file(COPY Images AppxManifest.xml MainWindowView.xaml DESTINATION ${CMAKE_BINARY_DIR})

set(SOURCES
    App.cpp
    Property.hpp
    MainWindowView.cpp
    MainWindowView.h
    MainWindowViewModel.cpp
    MainWindowViewModel.h
    ListItem.cpp
    ListItem.h
    NegativeDoubleConverter.cpp
    NegativeDoubleConverter.h
    SimpleCommand.cpp
    SimpleCommand.h)

add_executable(${PROJECT_NAME} ${SOURCES})
add_dependencies(${PROJECT_NAME} CppWinRT_HeaderGen)
include_directories(${CPPWINRT_OUTPUT_DIR})

target_link_libraries(${PROJECT_NAME} ole32 oleaut32 ucrtapp windowsapp winstorecompat)
