Hi!
Tristan here, just some notes on getting this working.

1. Make sure that the location your SDL2 library is located
in the same place as in the makefile. In the future we can
look into using the `shell sdl2-config --cflags` and the
`shell sdl2-config --libs` commands in the makefiles to get
the specific flags dependent on the system.

2. There is a small problem I have found in the makefile i threw
together. While it is building for me currently, if the "bin/" is
removed from the "bin/%.o: %.cpp" line in the makefile I start
getting errors. I am not quite sure why there is this behavior so
it may need to be something that is looked into.

3. Lets get crackin! I will try to get sprite sheets working in
the short term. Getting the update loop with user input, updating
the state, and redrawing will be the next step.
