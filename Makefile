CC=g++
LD=g++
BIN = city
SRCS=$(wildcard *.cpp)
OBJS = $(SRCS:.cpp=.o)
DEPS = $(SRCS:.cpp=.d)
CFLAGS = -ansi -pedantic -lGL -lGLU -lglut

all: $(BIN)

$(BIN): $(OBJS)
	$(LD) -o $@ $(OBJS) $(CFLAGS)

%.o: %.cpp
	$(CC) -o $@ -c $< $(CFLAGS)
%.d: %.cpp
	$(CC) $(CFLAGS) -MM -MD -o $@ $<

-include $(DEPS)

.PHONY: clean distclean

clean:
	rm -rf $(OBJS) $(DEPS)
distclean: clean
	rm -rf $(BIN)
