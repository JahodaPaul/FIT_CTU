CXXFLAGS = -std=c++11 -lpqxx -lpq -Ilibpqxx-5.0/include -lncurses
STRICTFLAGS = -std=c++11 -Wall -pedantic -Wno-long-long -O0 -ggdb -c

all: Connection.o Data.o Frontend.o Screen.o ScreenLogin.o ScreenIngredients.o User.o main.o output

compile: main.o Connection.o User.o Data.o Frontend.o Screen.o ScreenLogin.o ScreenIngredients.o
	cd jahodpa1;$(CXX) main.o Connection.o User.o Data.o Frontend.o Screen.o ScreenLogin.o ScreenIngredients.o -o output $(CXXFLAGS)

Connection.o: src/Connection.cpp src/Connection.h
	$(CXX) $(STRICTFLAGS) src/Connection.cpp -o jahodpa1/Connection.o
Data.o: src/Data.cpp src/Data.h
	$(CXX) $(STRICTFLAGS) src/Data.cpp -o jahodpa1/Data.o
Frontend.o: src/Frontend.cpp src/Frontend.h
	$(CXX) $(STRICTFLAGS) src/Frontend.cpp -o jahodpa1/Frontend.o
Screen.o: src/Screen.cpp src/Screen.h
	$(CXX) $(STRICTFLAGS) src/Screen.cpp -o jahodpa1/Screen.o
ScreenLogin.o: src/ScreenLogin.cpp src/ScreenLogin.h
	$(CXX) $(STRICTFLAGS) src/ScreenLogin.cpp -o jahodpa1/ScreenLogin.o
ScreenIngredients.o: src/ScreenIngredients.cpp src/ScreenIngredients.h
	$(CXX) $(STRICTFLAGS) src/ScreenIngredients.cpp -o jahodpa1/ScreenIngredients.o
User.o: src/User.cpp src/User.h
	$(CXX) $(STRICTFLAGS) src/User.cpp -o jahodpa1/User.o
main.o: src/main.cpp
	$(CXX) $(STRICTFLAGS) src/main.cpp -o jahodpa1/main.o
clean:	
	rm -rf jahodpa1/*.o jahodpa1/output
run:
	./jahodpa1/output
count:
	cat src/*.cpp src/*.h Backend/*.cpp Backend/*.h Frontend/*.cpp Frontend/*.h 2>/dev/null | wc -l
