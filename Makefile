CXX=g++
CPPFLAGS=-D_REENTRANT -I/usr/include/SDL2 -g -Wall
LDFLAGS=-L/usr/lib/x86_64-linux-gnu
RM=rm -f

SRCS=$(shell find src/ -name "*.cpp")
OBJS=$(SRCS:%.cpp=%.o)

bin/%.o: %.cpp
	echo $(input) $(output)
	$(CXX) $(CPPFLAGS) -c $(input) -o $(output)

all: gravity

gravity: $(OBJS)
	$(CXX) $(LDFLAGS) -o bin/$@ $(OBJS) -lSDL2

clean:
	$(RM) $(OBJS)

test:
	echo sources - $(SRCS)
	echo objects - $(OBJS)
