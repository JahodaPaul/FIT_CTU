CXXFLAGS = -std=c++11 -lpqxx -lpq -Ilibpqxx-5.0/include
STRICTFLAGS = -std=c++11 -Wall -pedantic -Wno-long-long -O2 -c 

all: Connection.o main.o output

output: main.o Connection.o
	$(CXX) main.o Connection.o -o output $(CXXFLAGS)
Connection.o: Connection.cpp Connection.h
	$(CXX) $(STRICTFLAGS) Connection.cpp -o Connection.o
main.o: main.cpp
	$(CXX) $(STRICTFLAGS) main.cpp -o main.o
clean:	
	rm -rf *.o output
