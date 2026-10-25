So lets make a game about some samurai frogs, shouldn't we?

## Compiling
### Compiling the raylib library
This step is a bit of a pain, but it is well described here:
[Install raylib for linux](https://github.com/raysan5/raylib/wiki/Working-on-GNU-Linux)

### Compiling and playing the game

Once you have compiled (and installed) the raylib library you can use the provided Makefile to compile the game.
The following commands are available:
- make: (or make all) compiles the game
- make clean: deletes the objects files (.o)
- make fclean: deletes the executable (aFrogsTale) and the object files (.o)
- make re: performs fclean and the recompiles everything

## Playing
The game can be played by launching the linux executable with ```./aFrogsTale ```
- Use WASD keys to move our samurai frog.
- Close the game by pressing Esc or the 'x' button on the window
- Collect all the coins and head to the door to win the game!

The games reads and loads the map called "default.map" in the maps folder. Feel free to play with it :)

Ps: Now you can directly load your own game map by passing its path when executing the game like this: ``` ./aFrogsTale "path/to/your/map" ``` If you don't provide any map, the default one will be loaded.

Go and have some fun!
