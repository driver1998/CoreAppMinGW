cmake_minimum_required(VERSION 3.5.0)
project(CoreAppMinGW VERSION 0.1.0)

include(CheckCSourceCompiles)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

if(MSVC)
    set(CMAKE_CXX_FLAGS "/EHsc")
    set(CMAKE_EXE_LINKER_FLAGS "/APPCONTAINER")
    add_definitions("-DUNICODE" "-D_UNICODE")
else()
    if(CMAKE_SYSTEM_PROCESSOR MATCHES "x86|AMD64")
        set(CMAKE_CXX_FLAGS "-mcx16")
    endif()
    set(CMAKE_EXE_LINKER_FLAGS "-municode -static")

    set(CMAKE_REQUIRED_FLAGS "-Wl,--appcontainer")
    check_c_source_compiles("int wWinMain(void) {return 0;}" LINKER_SUPPORTS_APPCONTAINER_FLAG)
    if(LINKER_SUPPORTS_APPCONTAINER_FLAG)
        set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS}  -Wl,--appcontainer")
    endif()
endif()

if(CMAKE_SYSTEM_PROCESSOR MATCHES "AMD64")
    set(APPX_ARCHITECTURE "x64")
elseif(CMAKE_SYSTEM_PROCESSOR MATCHES "x86")
    set(APPX_ARCHITECTURE "x86")
elseif(CMAKE_SYSTEM_PROCESSOR MATCHES "ARM64")
    set(APPX_ARCHITECTURE "arm64")
elseif(CMAKE_SYSTEM_PROCESSOR MATCHES "ARM")
    set(APPX_ARCHITECTURE "arm")
else()
    message(FATAL_ERROR "Invalid architecture ${CMAKE_SYSTEM_PROCESSOR}")
endif()

message(STATUS "Building for ${APPX_ARCHITECTURE}.")

file(COPY Images MainWindowView.xaml DESTINATION ${CMAKE_BINARY_DIR})
configure_file(AppxManifest.in AppxManifest.xml)

set(CPPWINRT_INPUT "references/Windows.winmd")
set(CPPWINRT_OUTPUT_DIR "${CMAKE_BINARY_DIR}/cppwinrt")

add_custom_command(
    OUTPUT
        ${CPPWINRT_OUTPUT_DIR}/winrt/base.h
    COMMAND
        cppwinrt -pch . -input ${CPPWINRT_INPUT} -output ${CPPWINRT_OUTPUT_DIR}
    WORKING_DIRECTORY
        ${CMAKE_CURRENT_SOURCE_DIR}
    COMMENT
        "Generating C++/WinRT Headers...")

set(SOURCES
    ${CPPWINRT_OUTPUT_DIR}/winrt/base.h
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

add_executable(${PROJECT_NAME} WIN32 ${SOURCES})
include_directories(${CPPWINRT_OUTPUT_DIR})

if(MSVC)
    target_link_libraries(${PROJECT_NAME} windowsapp)
else()
    target_link_libraries(${PROJECT_NAME} ucrtapp windowsapp winstorecompat)
endif()

add_custom_target(appx
    COMMAND
        ${CMAKE_COMMAND} -E make_directory "${CMAKE_BINARY_DIR}/appx/Images"
    COMMAND
        ${CMAKE_COMMAND} -E copy_if_different MainWindowView.xaml AppxManifest.xml "${PROJECT_NAME}.exe" "${CMAKE_BINARY_DIR}/appx"
    COMMAND
        ${CMAKE_COMMAND} -E copy_if_different Images/* "${CMAKE_BINARY_DIR}/appx/Images"
    COMMAND
        makemsix pack -d appx -p "${PROJECT_NAME}.appx"
    DEPENDS "${PROJECT_NAME}.exe"
)