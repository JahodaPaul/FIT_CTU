to start this project you
need to download and install libpqxx, libpq(for database communication) and ncurses (for UI)
--------------------------------------------------------------------------------
sudo apt-get install libpq-dev

git clone https://github.com/jtv/libpqxx

cd libpqxx

./configure --disable-documentation

make

sudo make install

--------------------------------------------------------------------------------
for ncurses: 

sudo apt-get install ncurses-dev

or if you have fedora:

yum install ncurses-*


Unfortunately it is not possible to run this program on windows, yet.

--------------------------------------------------------------------------------
make count -> calculates number of lines in code

make compile -> compiles project

make run -> runs project

make doc -> creates documentation using doxygen

make/make all -> compiles project and documentation

make clean -> deletes everything that could be created by make all.
