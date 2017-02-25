For Makefile: 
make creates .o files in ./bin/src/
make creates executable gravity in ./bin/

16:9 vertical aspect ratio

TODO:
Sprite map
Drawable class - rectangles - rectangles - spritemap location coords - frame coods
    method setVelocity
    position update methods
    possible player update static method
Backgroud consists of rendering all frame space not occupied by Drawable objects
Drawable player - instance of type object - fixed y
    needs acceleration for gratiy update, as opposed to fixed velocity for other Drawable objects
Queue<Drawable> - all onscreen objects excluding player
user input - possible static method, most likely in main game loop though
    toggle state of global boolean gravity variable - left right
    relies on global acceleration variable


