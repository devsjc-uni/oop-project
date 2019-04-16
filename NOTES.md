#oop-project
## notes from coding my project

### lamda and template functions
I used lambda and template functions in Tiles.h to create a more compact way to write out a double nested for loop. This was done since looping over all squares in the grid was an often required task in the program, and by creating a template function for it I could save a line of code every time it was initialised. The lambda function captures _this_ in order to enable usage of TileLists' member functions within the template function.

### bool onSpace function
It may be worth combining the "edge" and "wall" options, since both are for wall placements in Tiles.cpp : TileList::onSpace

### <random> include
I have used the <random> include and its associated methods to generate random integers between 0 and 9 in order to create a random box placement at the start of the board, as opposed to using rand() and srand(). This is because the pre c++11 random methods were slightly flawed.

### make_shared
make_shared<Derived>(); is effectively equivalent to new Derived(); from the non smart pointer days of old. In this way, a vector of smart pointers to base classes can be initialised via make_shared<Tile> and then these can be set to derived class pointers.

### playerVector and deques
It may be a sensible option to move the playerVector out of the TileList class into a seperate container class, and instead of making it a vector, making it a deque could be more space efficient.

### destructors
should delete elements of and class vectors in destructors!

### TileList.explodeBomb
TODO: CORRECT what happens when a bomb explodes onto another bomb!!