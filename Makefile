CXX=g++
CPPFLAGS=-D_REENTRANT -I/usr/include/SDL2 -g -Wall
LDFLAGS=-L/usr/lib/x86_64-linux-gnu
RM=rm -f

SRCS=$(shell find src/ -name "*.cpp")
OBJS=$(SRCS:%.cpp=%.o)
MOBJS=$(SRCS:%.cpp=bin/%.mo)


MAC_CFLAGS=-std=c++11 -I/usr/local/include/SDL2 -D_GNU_SOURCE=1 -D_THREAD_SAFE
MAC_LIBS=-L/usr/local/lib -lSDL2main -lSDL2 -lSDL2_image -Wl,-framework,Cocoa

%.o: %.cpp
	$(CXX) $(CPPFLAGS) -c $< -o bin/$@

bin/%.mo: %.cpp
		$(CXX) $(MAC_CFLAGS) -c $< -o $@

all: gravity

mac: gravity-mac

gravity: $(OBJS)
	$(CXX) $(LDFLAGS) -o bin/$@ $(OBJS:%.o=bin/%.o) -lSDL2 -lSDL2_image

gravity-mac: $(MOBJS)
		$(CXX) $(MAC_LIBS) -o bin/$@ $(MOBJS)

clean:
	$(RM) $(OBJS:%.o=bin/%.o) $(MOBJS) bin/gravity-mac

