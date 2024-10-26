# CPPND: Capstone Snake Game

This is a capstone project. This project focuses on utilizing all the concepts learnt before, in building a Snake game.

<img src="snake_game.gif"/>

## Dependencies for Running Locally

* cmake >= 3.7
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* SDL2 >= 2.0
  * All installation instructions can be found [here](https://wiki.libsdl.org/Installation)
  >Note that for Linux, an `apt` or `apt-get` installation is preferred to building from source.
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools](https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)

## Basic Build Instructions

1. Clone this repo.
2. Make a build directory in the top level directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./SnakeGame`

## Features added to the game

1. The player can now input their name through the terminal.
2. The game reads the stored score file to retrieve the highest score for the player, if they have previously played under the same name.
3. Various food types have been introduced, each with its own expiration time constraint.
4. After the player completes the game, their highest score is saved to the file.

## Concepts used from Rubic Points

* ## Loops, Functions, I/O

    1. File Read/Write operations:
        * File: `game.cpp`, lines: (`148`, `166`)
    2. Input from User:
        * File: `main.cpp`, lines: (`16`)

* ## Object Oriented Programming

    1. One or more classes are added:
        * File: `game.h`, lines: (`56`, `109`)
    2. Class constructors utilize member initializaion lists:
        * File: `player.cpp`, lines: (`4`)
    3. Function names specifies its usages
        * File: `game.h`, lines: (`88`)

* ## Memory Management

    1. Use of references in function declarations:
        * File: `game.h`, lines: (`74`, `84`)
    2. Uses destructors appropriately:
        * File: `game.cpp`, lines: (`20`)
    3. Use of smart pointers
        * File: `game.h`, lines: (`132`)

* ## Concurrency

    1. Multithreading:
        * File: `game.cpp`, lines: (`39`)
    2. Mutex and lock:
        * File: `game.cpp`, lines: (`77`, `116`)
