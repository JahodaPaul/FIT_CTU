## Final project for _Programming and Algorithmics 2_ course ( BI-PA2 2017)<br/>
## [![License: MIT](https://img.shields.io/badge/License-MIT-green.svg)](https://opensource.org/licenses/MIT)

## About
First year final project. Database application which allows you to <br/>
search for recipes by ingredients they contain, like and unlike them <br/>
and even add them to your menu. <br/>
__Maximum amount of points awarded (12 out of 12).__

## Installation
Go to project folder and type
```
 make install
```
which will hopefully install all necessary libraries


If make install does not do the work, you need to download and install <br/>
libpq(for database communication) and ncurses (for UI) using following commands:<br/>
```
 sudo apt-get install libpq-dev
```

ncurses (ubuntu): 
```
 sudo apt-get install ncurses-dev
```
ncurses (fedora):
```
 yum install ncurses-*
```
## How to start
Go to project folder and type:
```
 make compile && make run
```

## Options
```
 make count (calculates number of lines in code)
 make install (installs necessary libraries)
 make compile (compiles project)
 make run (runs project)
 make doc (creates documentation using doxygen)
 make/make all (compiles project and documentation)
 make clean (deletes everything that could be created by make all)
```

## Windows support
It is now possible to run it on windows. However, I do recommend using<br/>
Bash on Ubuntu on Windows and installing libraries as if you were on ubuntu<br/>
and running from bash using "make clean && make compile && make run"
