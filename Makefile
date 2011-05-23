MAIN_SRC=main.cpp
VIEWER_SRC=$(wildcard Viewer/*.cpp)
CITY_SRC=$(wildcard City/*.cpp)
SRC=$(VIEWER_SRC) $(MAIN_SRC) $(CITY_SRC)
FLAGS=-Wall -Wextra
LIBFLAGS=-lGL -lglut -lGLU


all:
	g++ $(SRC) $(FLAGS) $(LIBFLAGS)
