CXXFLAGS = -std=c++11 -lpqxx -lpq -Ilibpqxx-5.0/include

all: Connection.o main.o output

output: main.o Connection.o
	$(CXX) main.o Connection.o -o output $(CXXFLAGS)
Connection.o: Connection.cpp Connection.h
	$(CXX) -c Connection.cpp -o Connection.o
main.o: main.cpp
	$(CXX) -c main.cpp -o main.o
clean:	
	rm -rf *.o output
