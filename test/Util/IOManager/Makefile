FLAGS=-Wall -pedantic -std=c++14 -lsfml-graphics -lsfml-window -lsfml-system -I '../../../include' -fsanitize=address
DEPENDENCY=../../../src/Util/IOManager.cpp
OUT=iomanager.out

$(OUT): IOManager_main.cpp $(DEPENDENCY)
	$(CXX) $^ -o $@ $(FLAGS)

.PHONY: clean

clean:
	rm -rf $(OUT)

