LIBS=-l sfml-window -l sfml-system -l sfml-graphics -l sfml-audio
CXXFLAGS=-Wall -pedantic -fsanitize=address -g -std=c++14
INC=-I "../../../include"
FILES=test.cpp ../../../src/View/SoundManager.cpp
TARGET=SoundManager.out

.PHONY: clean

${TARGET}: ${FILES}
	${CXX} ${CXXFLAGS} $^ ${LIBS} ${INC} -o ${TARGET}

clean:
	rm -f ${TARGET}