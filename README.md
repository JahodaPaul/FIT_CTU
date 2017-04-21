to start this project
you need to download and install libpqxx, libpq(for database communication) and ncurses (for UI)
-----------------------------
sudo apt-get install libpq-dev

git clone https://github.com/jtv/libpqxx
cd libpqxx
./configure --disable-documentation
make
sudo make install

-----------------------------
for ncurses:
sudo apt-get install ncurses-dev

or if you have fedore:
yum install ncurses-*


Unfortunatly it is not possible to run this program on windows, yet.