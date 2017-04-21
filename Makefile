CXXFLAGS = -std=c++11 -lpqxx -lpq -Ilibpqxx-5.0/include -lncurses
STRICTFLAGS = -std=c++11 -Wall -pedantic -Wno-long-long -O2 -c 

all: Connection.o main.o output

output: main.o Connection.o User.o Data.o Frontend.o
	$(CXX) main.o Connection.o User.o Data.o Frontend.o -o output $(CXXFLAGS)
Connection.o: Connection.cpp Connection.h
	$(CXX) $(STRICTFLAGS) Connection.cpp -o Connection.o
Data.o: Data.cpp Data.h
	$(CXX) $(STRICTFLAGS) Data.cpp -o Data.o
Frontend.o: Frontend.cpp Frontend.h
	$(CXX) $(STRICTFLAGS) Frontend.cpp -o Frontend.o
User.o: User.cpp User.h
	$(CXX) $(STRICTFLAGS) User.cpp -o User.o
main.o: main.cpp
	$(CXX) $(STRICTFLAGS) main.cpp -o main.o
clean:	
	rm -rf *.o output
