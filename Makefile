CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17

TARGET = aix

$(TARGET): main.o user.o
	$(CXX) $(CXXFLAGS) main.o user.o -o $(TARGET)

main.o: main.cpp user.hpp
	$(CXX) $(CXXFLAGS) -c main.cpp

user.o: user.cpp user.hpp
	$(CXX) $(CXXFLAGS) -c user.cpp

clean:
	rm -f *.o $(TARGET)
