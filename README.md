Semestral project for subject Programming and Algorithmics 2 ( BI-PA2 ) at Czech Technical University in Prague, FIT [![contributions welcome](https://img.shields.io/badge/contributions-welcome-brightgreen.svg?style=flat)](https://github.com/dwyl/esta/issues) [![ghit.me](https://ghit.me/badge.svg?repo=JahodaPavel/Recipe_Manager)](https://ghit.me/repo/JahodaPavel/Recipe_Manager)
--------------------------------------------------------------------------------
Graded maximum amount of points -> 12 out of 12.

Semestrální práce na předmět Programování a algoritmizace 2 ( BI-PA2 ) na ČVUT, FIT
--------------------------------------------------------------------------------
Ohodnoceno maximálním počtem bodů -> 12 z 12.

-------------------------------------------------------------------------------

to run this project
go to project folder and type "make install" which will hopefully install all necessary libraries

if make install does not do the work you
need to download and install libpq(for database communication) and ncurses (for UI)
--------------------------------------------------------------------------------

sudo apt-get install libpq-dev

--------------------------------------------------------------------------------
for ncurses: 

sudo apt-get install ncurses-dev

or if you have fedora:

yum install ncurses-*


--------------------------------------------------------------------------------
make count -> calculates number of lines in code

make install -> installs necessary libraries

make compile -> compiles project

make run -> runs project

make doc -> creates documentation using doxygen

make/make all -> compiles project and documentation

make clean -> deletes everything that could be created by make all.

--------------------------------------------------------------------------------
It is now possible to run it on windows. However, I do recommend using

Bash on Ubuntu on Windows and installing libraries as if you were on ubuntu

and running from bash using "make clean && make compile && make run"
