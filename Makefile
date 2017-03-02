CXX=g++
CPPFLAGS=-D_REENTRANT -I/usr/include/SDL2 -g -Wall
LDFLAGS=-L/usr/lib/x86_64-linux-gnu
RM=rm -f

SRCS=$(shell find src/ -name "*.cpp")
OBJS=$(SRCS:%.cpp=bin/%.o)

bin/%.o: %.cpp
	$(CXX) $(CPPFLAGS) -c $< -o $@

all: gravity

gravity: $(OBJS)
	$(CXX) $(LDFLAGS) -o bin/$@ $(OBJS) -lSDL2 -lSDL2_image

clean:
	$(RM) $(OBJS)
	$(RM) bin/gravity

test:
	echo sources - $(SRCS)
	echo objects - $(OBJS)
