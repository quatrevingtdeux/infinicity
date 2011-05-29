MAIN_SRC=main.cpp
VIEWER_SRC=$(wildcard Viewer/*.cpp)
CITY_SRC=$(wildcard City/*.cpp)
EXPORT_SRC=$(wildcard ExportObj/*.cpp)
GEOM_SRC=$(wildcard Geom/*.cpp)
MISC_SRC=$(wildcard Misc/*.cpp)
SRC=$(GEOM_SRC) $(VIEWER_SRC) $(MAIN_SRC) $(CITY_SRC) $(EXPORT_SRC) $(MISC_SRC)
FLAGS=-Wall -Wextra
LIBFLAGS=-lGL -lglut -lGLU -lm -g

all:
	g++ $(SRC) $(FLAGS) $(LIBFLAGS)
