#!/bin/bash

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
