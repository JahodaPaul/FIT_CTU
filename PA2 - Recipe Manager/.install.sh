#!/bin/bash

#get files from libraries libpq and curses
wget -O ./lib/libpq.zip https://www.dropbox.com/sh/tnd0jhnh4mdcbd0/AABEqRNhapunJPZCOxmKSrqKa?dl=1
unzip ./lib/libpq.zip -d ./lib/libpq

wget -O ./lib/curses.zip https://www.dropbox.com/sh/p1e3ntdt7hkmww9/AABsHWERn4wjV7csCCSAkxqja?dl=1
unzip ./lib/curses.zip -d ./lib/curses

rm ./lib/curses.zip
rm ./lib/libpq.zip

#fedora
fedora=$(grep "edora$" /etc/*-release | wc -l)
centos=$(grep "entos$" /etc/*-release | wc -l)

if (($fedora>0 || $centos>0))
then
yum install postgresql-devel
yum install ncurses-*

else
sudo apt-get install libpq-dev
sudo apt-get install ncurses-dev

fi
