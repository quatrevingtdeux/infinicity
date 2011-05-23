MAIN_SRC=main.cpp
VIEWER_SRC=$(wildcard Viewer/*.cpp)
CITY_SRC=$(wildcard City/*.cpp)
EXPORT_SRC=$(wildcard ExportObj/*.cpp)
SRC=$(VIEWER_SRC) $(MAIN_SRC) $(CITY_SRC) $(EXPORT_SRC)
#FLAGS=-Wall -Wextra
LIBFLAGS=-lGL -lglut -lGLU


all:
	g++ $(SRC) $(FLAGS) $(LIBFLAGS)
