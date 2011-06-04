MAIN_SRC=main.cpp
VIEWER_SRC=$(wildcard Viewer/*.cpp)
CITY_SRC=$(wildcard City/*.cpp)
OBJ_SRC=$(wildcard ObjManager/*.cpp)
GEOM_SRC=$(wildcard Geom/*.cpp)
MISC_SRC=$(wildcard Misc/*.cpp)
MAPS_SRC=$(wildcard Maps/*.cpp)
SRC=$(GEOM_SRC) $(VIEWER_SRC) $(MAIN_SRC) $(CITY_SRC) $(OBJ_SRC) $(MISC_SRC) $(MAPS_SRC)
FLAGS=-Wall -Wextra
LIBFLAGS=-lGL -lglut -lGLU -lm -g

all:
	g++ $(SRC) $(FLAGS) $(LIBFLAGS)
