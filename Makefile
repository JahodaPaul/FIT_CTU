CXXFLAGS = -std=c++1y -Ilib/libpqxx-5.0/include -lpqxx -lpq -lncurses
STRICTFLAGS = -std=c++1y -Wall -pedantic -Wno-long-long -O0 -ggdb -c

all: build/Connection.o build/Recipe.o build/Data.o build/Frontend.o build/Screen.o build/ScreenLogin.o build/ScreenLoginPassword.o build/ScreenIngredients.o build/ScreenRecipes.o build/ScreenSingleRecipe.o build/ScreenUserMenu.o build/User.o build/main.o compile doc

compile: build/main.o build/Connection.o build/User.o build/Recipe.o build/Data.o build/Frontend.o build/Screen.o build/ScreenLogin.o build/ScreenLoginPassword.o build/ScreenIngredients.o build/ScreenRecipes.o build/ScreenSingleRecipe.o build/ScreenUserMenu.o
	cd build;$(CXX) main.o Connection.o Recipe.o User.o Data.o Frontend.o Screen.o ScreenLogin.o ScreenLoginPassword.o ScreenIngredients.o ScreenRecipes.o ScreenSingleRecipe.o ScreenUserMenu.o -o jahodpa1 $(CXXFLAGS)
	mv build/jahodpa1 jahodpa1


build/Connection.o: src/Backend/Connection.cpp src/Backend/Connection.h
	$(CXX) $(STRICTFLAGS) src/Backend/Connection.cpp -o build/Connection.o

build/Recipe.o: src/Backend/Recipe.cpp src/Backend/Recipe.h
	$(CXX) $(STRICTFLAGS) src/Backend/Recipe.cpp -o build/Recipe.o

build/Data.o: src/Backend/Data.cpp src/Backend/Data.h
	$(CXX) $(STRICTFLAGS) src/Backend/Data.cpp -o build/Data.o

build/Frontend.o: src/Frontend/Frontend.cpp src/Frontend/Frontend.h
	$(CXX) $(STRICTFLAGS) src/Frontend/Frontend.cpp -o build/Frontend.o

build/Screen.o: src/Frontend/Screen.cpp src/Frontend/Screen.h
	$(CXX) $(STRICTFLAGS) src/Frontend/Screen.cpp -o build/Screen.o

build/ScreenLogin.o: src/Frontend/ScreenLogin.cpp src/Frontend/ScreenLogin.h
	$(CXX) $(STRICTFLAGS) src/Frontend/ScreenLogin.cpp -o build/ScreenLogin.o

build/ScreenLoginPassword.o: src/Frontend/ScreenLoginPassword.cpp src/Frontend/ScreenLoginPassword.h
	$(CXX) $(STRICTFLAGS) src/Frontend/ScreenLoginPassword.cpp -o build/ScreenLoginPassword.o

build/ScreenIngredients.o: src/Frontend/ScreenIngredients.cpp src/Frontend/ScreenIngredients.h
	$(CXX) $(STRICTFLAGS) src/Frontend/ScreenIngredients.cpp -o build/ScreenIngredients.o

build/ScreenRecipes.o: src/Frontend/ScreenRecipes.cpp src/Frontend/ScreenRecipes.h
	$(CXX) $(STRICTFLAGS) src/Frontend/ScreenRecipes.cpp -o build/ScreenRecipes.o

build/ScreenSingleRecipe.o: src/Frontend/ScreenSingleRecipe.cpp src/Frontend/ScreenSingleRecipe.h
	$(CXX) $(STRICTFLAGS) src/Frontend/ScreenSingleRecipe.cpp -o build/ScreenSingleRecipe.o

build/ScreenUserMenu.o: src/Frontend/ScreenUserMenu.cpp src/Frontend/ScreenUserMenu.h
	$(CXX) $(STRICTFLAGS) src/Frontend/ScreenUserMenu.cpp -o build/ScreenUserMenu.o

build/User.o: src/Backend/User.cpp src/Backend/User.h
	$(CXX) $(STRICTFLAGS) src/Backend/User.cpp -o build/User.o

build/main.o: src/main.cpp
	$(CXX) $(STRICTFLAGS) src/main.cpp -o build/main.o

clean:	
	rm -rf build/*.o jahodpa1 doc
run:
	./jahodpa1
count:
	./src/.countNumberOfLines.sh

doc:
	mkdir -p doc
	doxygen Doxyfile
install:
	./.install.sh
