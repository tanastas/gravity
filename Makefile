CXX=g++
CPPFLAGS=-D_REENTRANT -I/usr/include/SDL2 -g -Wall
LDFLAGS=-L/usr/lib/x86_64-linux-gnu
RM=rm -f

SRCS=$(shell find src/ -name "*.cpp")
OBJS=$(SRCS:%.cpp=%.o)

%.o: %.cpp
	$(CXX) $(CPPFLAGS) -c $< -o bin/$@

all: gravity

gravity: $(OBJS)
	$(CXX) $(LDFLAGS) -o bin/$@ bin/$(OBJS) -lSDL2

clean:
	$(RM) bin/$(OBJS)
	$(RM) bin/gravity

test:
	echo sources - $(SRCS)
	echo objects - $(OBJS)
