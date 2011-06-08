BIN=infinicity
MAIN_SRC=main.cpp
CITY_SRC=$(wildcard City/*.cpp)
OBJ_SRC=$(wildcard ObjManager/*.cpp)
GEOM_SRC=$(wildcard Geom/*.cpp)
MISC_SRC=$(wildcard Misc/*.cpp)
SRC=$(GEOM_SRC) $(MAIN_SRC) $(CITY_SRC) $(OBJ_SRC) $(MISC_SRC)
FLAGS=-Wall -Wextra -g
LIBFLAGS=-lm

all:
	g++ -o $(BIN) $(SRC) $(FLAGS) $(LIBFLAGS)

run: all
	./$(BIN)
