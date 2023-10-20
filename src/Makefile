CXX=c++
WINDRES=windres
CXXFLAGS=-std=c++20 -mcx16
INCLUDES=-Icppwinrt -Iinclude
LIBS=-lole32 -loleaut32 -lucrtapp -lwindowsapp -lwinstorecompat 
LDFLAGS=-mwindows -municode -static

all: CoreAppMinGW.exe

HEADERS= Property.hpp

cppwinrt-headers:
	cppwinrt -pch . -input references/Windows.winmd -output cppwinrt
	touch cppwinrt-headers

%.o: %.cpp %.h ${HEADERS} cppwinrt-headers
	${CXX} -c ${CXXFLAGS} ${INCLUDES} $< -o $@

App.o: App.cpp cppwinrt-headers
	${CXX} -c ${CXXFLAGS} ${INCLUDES} $< -o $@

CoreAppMinGW.exe: App.o MainWindowView.o MainWindowViewModel.o SimpleCommand.o NegativeDoubleConverter.o ListItem.o
	${CXX} $^ ${LIBS} ${LDFLAGS} -o $@

clean:
	rm -rf *.exe *.o cppwinrt cppwinrt-headers
