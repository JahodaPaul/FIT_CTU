#!/bin/bash

#fedora
fedora=$(grep "edora$" /etc/*-release | wc -l)
centos=$(grep "entos$" /etc/*-release | wc -l)

if (($fedora>0 || $centos>0))
then
yum install postgresql-devel
cd lib/libpqxx-5.0/
./configure --disable-documentation
su make
su make install
yum install ncurses-*

else
sudo apt-get install libpq-dev libpqxx-dev
cd lib/libpqxx-5.0/
./configure --disable-documentation
sudo make
sudo make install
sudo apt-get install ncurses-dev

fi
