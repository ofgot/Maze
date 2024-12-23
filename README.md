# Infinite Maze

Do you like mazes?‏𖦹<br>
<br>
Well, aren't you lucky! This game is just for you! <br> <br>
Here, you can explore endless paths, trying to find your way out — because who doesn't enjoy a good challenge?<br><br>
And for the ultimate fun, it’s **INFINITE**, so you can play it **FOREVER**! <br>

## Warnings
This game is only for Mac 🤷
##
![Mazegif](https://github.com/user-attachments/assets/b7f69d3f-0d40-4a91-add3-f8d1b9c35415) <br>


## How to run file
### Just run it in cmd <br>

The first thing you need is to install **raylib** library: <br>
```
brew install raylib
```
After go to the Maze/build directory and sequentially write it: <br>
```
mkdir build 
```
```
cd build 
```
``` 
cmake .. 
```
```
cmake --build . 
```
And finaly this: <br>
```
./Maze
```
Enjoy the game!!!

**ADDITIONALLY** add --help to find more about the game
```
./Maze --help
```

## Controlls
* W: Move up
* A: Move left
* S: Move down
* D: Move right

## Tests 

This game was tested using the Catch2 unit testing framework. The main focus of the testing was the Field class, which is responsible for maze generation and pathfinding. <br>

The following tests were performed: <br>

* Maze Creation: Ensuring that mazes are generated correctly with varying sizes. <br>

* Maze Validation: Verifying that the generated mazes are valid and that there are no errors in their structure. <br>

* Longest Path Finding: Testing the ability to correctly identify and track the longest path in the maze. <br>

Unfortunately, memory leak detection could not be performed using Valgrind or Dr. Memory, as they do not support the chip architecture of the development environment. 
