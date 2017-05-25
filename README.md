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


Unfortunately it is not possible to run this program on windows, yet.

--------------------------------------------------------------------------------
make count -> calculates number of lines in code

make install -> installs necessary libraries

make compile -> compiles project

make run -> runs project

make doc -> creates documentation using doxygen

make/make all -> compiles project and documentation

make clean -> deletes everything that could be created by make all.
