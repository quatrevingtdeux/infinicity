MAIN_SRC=main.cpp
VIEWER_SRC=$(wildcard Viewer/*.cpp)
CITY_SRC=$(wildcard City/*.cpp)
EXPORT_SRC=$(wildcard ExportObj/*.cpp)
GEOM_SRC=$(wildcard Geom/*.cpp)
SRC=$(GEOM_SRC) $(VIEWER_SRC) $(MAIN_SRC) $(CITY_SRC) $(EXPORT_SRC)
FLAGS=-Wall -Wextra
LIBFLAGS=-lGL -lglut -lGLU -lm

all:
	g++ $(SRC) $(FLAGS) $(LIBFLAGS)
