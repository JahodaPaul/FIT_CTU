CXXFLAGS = -std=c++11 -lpqxx -lpq -Ilibpqxx-5.0/include -lncurses
STRICTFLAGS = -std=c++11 -Wall -pedantic -Wno-long-long -O0 -ggdb -c 

all: Connection.o Data.o Frontend.o Screen.o ScreenLogin.o ScreenIngredients.o User.o main.o output

output: main.o Connection.o User.o Data.o Frontend.o Screen.o ScreenLogin.o ScreenIngredients.o
	$(CXX) main.o Connection.o User.o Data.o Frontend.o Screen.o ScreenLogin.o ScreenIngredients.o -o output $(CXXFLAGS)
Connection.o: Connection.cpp Connection.h
	$(CXX) $(STRICTFLAGS) Connection.cpp -o Connection.o
Data.o: Data.cpp Data.h
	$(CXX) $(STRICTFLAGS) Data.cpp -o Data.o
Frontend.o: Frontend.cpp Frontend.h
	$(CXX) $(STRICTFLAGS) Frontend.cpp -o Frontend.o
Screen.o: Screen.cpp Screen.h
	$(CXX) $(STRICTFLAGS) Screen.cpp -o Screen.o
ScreenLogin.o: ScreenLogin.cpp ScreenLogin.h
	$(CXX) $(STRICTFLAGS) ScreenLogin.cpp -o ScreenLogin.o
ScreenIngredients.o: ScreenIngredients.cpp ScreenIngredients.h
	$(CXX) $(STRICTFLAGS) ScreenIngredients.cpp -o ScreenIngredients.o
User.o: User.cpp User.h
	$(CXX) $(STRICTFLAGS) User.cpp -o User.o
main.o: main.cpp
	$(CXX) $(STRICTFLAGS) main.cpp -o main.o
clean:	
	rm -rf *.o output
