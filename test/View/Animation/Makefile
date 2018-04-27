LIBS=-l sfml-window -l sfml-system -l sfml-graphics
CXXFLAGS=-Wall -pedantic -fsanitize=address -g -std=c++14
INC=-I "../../../include"
FILES=main.cpp ../../../src/View/Animation.cpp
TARGET=animation.out

.PHONY: clean

${TARGET}: ${FILES}
	${CXX} ${CXXFLAGS} $^ ${LIBS} ${INC} -o ${TARGET}

clean:
	rm -f ${TARGET}
