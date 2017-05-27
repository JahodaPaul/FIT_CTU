Semestral project for subject Programming and Algorithmics 2 ( BI-PA2 ) at Czech Technical University in Prague, FIT
--------------------------------------------------------------------------------


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