CC=g++
CFLAGS=-Wall -g -std=c++11

SRC=$(wildcard src/*.cpp)
OBJ=$(addprefix obj/, $(notdir $(SRC:.cpp=.o)))

LIBSFML=-lsfml-graphics -lsfml-window -lsfml-system
LIBYAML=-lyaml-cpp

VALFLAGS=--leak-check=full --track-origins=yes

TARGET=app

all: obj ${TARGET}

obj/%.o: src/%.cpp
	${CC} ${CFLAGS} -c -o $@ $<

obj/CAnimationHandler.o: src/CAnimationHandler.cpp obj/CMovement.o
	${CC} ${CFLAGS} -c -o $@ $<

${TARGET}: main.cpp ${OBJ}
	${CC} ${CFLAGS} -o $@ $^ ${LIBSFML} ${LIBYAML}

clean:
	@rm -f obj/*.o

mrproper: clean
	@rm -f ${TARGET}

obj:
	@mkdir $@

l: ${TARGET}
	@./${TARGET}

v: ${TARGET}
	@valgrind ${VALFLAGS} ./${TARGET}
