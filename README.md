to start this project(make communication with postges database possible) 
you need to download and install libpqxx and libpq
-----------------------------
sudo apt-get install libpq-dev

git clone https://github.com/jtv/libpqxx
cd libpqxx
./configure --disable-documentation
make
sudo make install



Unfortunatly it is not possible to run this program on windows, yet.