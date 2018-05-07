FLAGS=-Wall -pedantic -std=c++14 -I '../../../include'
DEPENDENCY=../../../src/Util/Logger.cpp
OUT=logger.out

$(OUT): Logger_main.cpp $(DEPENDENCY)
	$(CXX) $^ -o $@ $(FLAGS)

.PHONY: clean

clean:
	rm -rf $(OUT)