CXX=g++
CPPFLAGS=-D_REENTRANT -I/usr/include/SDL2 -g -Wall
LDFLAGS=-L/usr/lib/x86_64-linux-gnu
RM=rm -f

SRCS=$(shell find src/ -name "*.cpp")
OBJS=$(SRCS:%.cpp=bin/%.o)

<<<<<<< HEAD
%.o: %.cpp
	$(CXX) $(CPPFLAGS) -c $< -o bin/$@
=======
bin/%.o: %.cpp
	$(CXX) $(CPPFLAGS) -c $< -o $@
>>>>>>> tristans

all: gravity

gravity: $(OBJS)
<<<<<<< HEAD
	$(CXX) $(LDFLAGS) -o bin/$@ bin/$(OBJS) -lSDL2

clean:
	$(RM) bin/$(OBJS) bin/gravity
=======
	$(CXX) $(LDFLAGS) -o bin/$@ $(OBJS) -lSDL2 -lSDL2_image

clean:
	$(RM) $(OBJS)
	$(RM) bin/gravity
>>>>>>> tristans

test:
	echo sources - $(SRCS)
	echo objects - $(OBJS)
