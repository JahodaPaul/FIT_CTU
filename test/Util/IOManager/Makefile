FLAGS=-Wall -pedantic -std=c++14 -lsfml-graphics -lsfml-window -lsfml-system -I '../../../include' -fsanitize=address -g
DEPENDENCY=../../../src/Util/IOManager.cpp ../../../imgui/imgui.cpp ../../../imgui/imgui_draw.cpp
OUT=iomanager.out keys/* new_keys/*

$(OUT): IOManager_main.cpp $(DEPENDENCY)
	$(CXX) $^ -o $@ $(FLAGS)

.PHONY: clean

clean:
	rm -rf $(OUT)

