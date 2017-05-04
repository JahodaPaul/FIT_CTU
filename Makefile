CXXFLAGS = -lpqxx -lpq -Ilibpqxx-5.0/include -lncurses
STRICTFLAGS = -std=c++11 -Wall -pedantic -Wno-long-long -O0 -ggdb -c
LESSSTRICTFLAGS = -Wall -pedantic -Wno-long-long -O0 -ggdb -c

all: Connection.o Data.o Frontend.o Screen.o ScreenLogin.o ScreenIngredients.o User.o main.o output

compile: main.o Connection.o User.o Data.o Frontend.o Screen.o ScreenLogin.o ScreenIngredients.o
	cd jahodpa1;$(CXX) main.o Connection.o User.o Data.o Frontend.o Screen.o ScreenLogin.o ScreenIngredients.o -o output $(CXXFLAGS)



Connection.o: src/Backend/Connection.cpp src/Backend/Connection.h
	$(CXX) $(LESSSTRICTFLAGS) src/Backend/Connection.cpp -o jahodpa1/Connection.o

Data.o: src/Backend/Data.cpp src/Backend/Data.h
	$(CXX) $(STRICTFLAGS) src/Backend/Data.cpp -o jahodpa1/Data.o

Frontend.o: src/Frontend/Frontend.cpp src/Frontend/Frontend.h
	$(CXX) $(STRICTFLAGS) src/Frontend/Frontend.cpp -o jahodpa1/Frontend.o

Screen.o: src/Frontend/Screen.cpp src/Frontend/Screen.h
	$(CXX) $(STRICTFLAGS) src/Frontend/Screen.cpp -o jahodpa1/Screen.o

ScreenLogin.o: src/Frontend/ScreenLogin.cpp src/Frontend/ScreenLogin.h
	$(CXX) $(STRICTFLAGS) src/Frontend/ScreenLogin.cpp -o jahodpa1/ScreenLogin.o

ScreenIngredients.o: src/Frontend/ScreenIngredients.cpp src/Frontend/ScreenIngredients.h
	$(CXX) $(STRICTFLAGS) src/Frontend/ScreenIngredients.cpp -o jahodpa1/ScreenIngredients.o

User.o: src/Backend/User.cpp src/Backend/User.h
	$(CXX) $(STRICTFLAGS) src/Backend/User.cpp -o jahodpa1/User.o

main.o: src/main.cpp
	$(CXX) $(STRICTFLAGS) src/main.cpp -o jahodpa1/main.o

clean:	
	rm -rf jahodpa1/*.o jahodpa1/output
run:
	./jahodpa1/output
count:
	cat src/*.cpp src/*.h src/Backend/*.cpp src/Backend/*.h src/Frontend/*.cpp src/Frontend/*.h 2>/dev/null | wc -l
