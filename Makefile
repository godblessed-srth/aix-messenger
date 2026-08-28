CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17
LDFLAGS = -lsqlite3

TARGET = aix

$(TARGET): main.o user.o database.o message.o
	$(CXX) $(CXXFLAGS) main.o user.o message.o database.o -o $(TARGET) $(LDFLAGS)

main.o: main.cpp user.hpp
	$(CXX) $(CXXFLAGS) -c main.cpp

user.o: user.cpp user.hpp
	$(CXX) $(CXXFLAGS) -c user.cpp

message.o: message.cpp message.hpp
	$(CXX) $(CXXFLAGS) -c message.cpp

database.o: database.cpp database.hpp
	$(CXX) $(CXXFLAGS) -c database.cpp

clean:
	rm -f *.o $(TARGET)
