CC=g++
CFLAGS=-Wall -O2 -g

SRC=$(wildcard src/*.cpp)
OBJ=$(addprefix obj/, $(notdir $(SRC:.cpp=.o)))

LIBSFML=-lsfml-graphics -lsfml-window -lsfml-system
LIBYAML=-lyaml-cpp

VALFLAGS=--leak-check=full 

TARGET=app

all: ${TARGET}

obj/%.o: src/%.cpp
	${CC} ${CFLAGS} -c -o $@ $<

${TARGET}: main.cpp ${OBJ}
	${CC} ${CFLAGS} -o $@ $^ ${LIBSFML} ${LIBYAML}

clean:
	@rm -f obj/*.o

mrproper: clean
	@rm -f ${TARGET}

l: ${TARGET}
	@./${TARGET}

v: ${TARGET}
	@valgrind ${VALFLAGS} ./${TARGET}