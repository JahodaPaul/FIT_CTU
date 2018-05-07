#!/bin/bash

SetupLibraries() {
    echo ""
    echo ""
    echo -e "\t\tLibraries setup"
    echo ""
    if [ -d 'imgui' -o -d 'imgui-sfml' ]; then
        echo "'imgui' or 'imgui-sfml' directory found, should I delete it and create new one? [y/n]"
        read -s -n 1 ans; echo "$ans"
        if [ "$ans" == "n" ]; then
            return 0
        else
            rm -rf 'imgui' 'imgui-sfml'
        fi fi
    echo ""
    echo ""
    echo "Cloning imgui..."
    echo ""
    git clone https://github.com/ocornut/imgui.git

    echo ""
    echo ""
    echo "Cloning imgui SFML binding..."
    echo ""
    git clone https://github.com/eliasdaler/imgui-sfml.git

    echo ""
    echo ""
    echo "Updating imgui code..."
    echo ""
    cat 'imgui-sfml/imconfig-SFML.h' >> 'imgui/imconfig.h'
    return 0
}

DownloadAssets() {
    echo ""
    echo ""
    echo -e "\t\tAssets setup"
    echo ""
    echo " Will Reguest root acces"
    if [ -d '/usr/share/RG' ]; then
        echo "'/usr/share/RG' directory found, should I delete it and create new one? [y/n]"
        read -s -n 1 ans; echo "$ans"
        if [ "$ans" == "n" ]; then
            return 0
        else
            sudo rm -rf '/usr/share/RG'
        fi
    fi
    echo "Creating 'assets' directory..."
    sudo mkdir -p /usr/share/RG/assets 2> /dev/null

    echo "Creating 'defaults' directory..."
    sudo mkdir -p '/usr/share/RG/defaults'
    sudo cp './ListOfMusic.txt' './ListOfSound.txt' '/usr/share/RG/defaults'

    sudo chmod -R 555 '/usr/share/RG/'
    cd /usr/share/RG
    echo ""
    echo ""
    echo ""
    echo ""
    echo ""
    echo "Downloading assets..."
    echo ""
    sudo curl 'ftp://mybestcloud.xyz/pub/assets-20180506T223100Z-001.zip' --output 'graphics.zip' 2>/dev/null
    sudo unzip 'graphics.zip'
    sudo rm 'graphics.zip'
    sudo chmod -R 555 '/usr/share/RG/'
    sudo find . -type f -exec chmod 444 {} \;
    cd -
    return 0
}

SetupBuildDir() {
    echo ""
    echo ""
    echo -e "\t\tBuild directory setup"
    echo ""
    if [ -d 'build' ]; then
        echo "'build' directory found, should I delete it and create new one? [y/n]"
        read -s -n 1 ans; echo "$ans"
        if [ "$ans" == "n" ]; then
            return 0
        else
            rm -rf 'build'
        fi
    fi

    echo "Choose build type [1/2]:"
    echo -e "\t1) Debug ( recomended )"
    echo -e "\t2) Release"
    read -s -n 1 ans; echo "$ans"
    if [ "$ans" == "2" ]; then
        TYPE='Release'
    else
        TYPE='Debug'
    fi
    echo "Build type chosen: ${TYPE}"
    mkdir 'build'
    cd 'build'
    cmake -DCMAKE_BUILD_TYPE="${TYPE}" ..
    ret=$?
    cd ..
    return $ret
}

CreateConfigDir() {
    echo ""
    echo ""
    echo -e "\t\tCreating config dir: /home/$USER/.RG."

    if [ -d "/home/$USER/.RG" ]; then
        echo "/home/$USER/.RG directory found, should I delete it and create new one? [y/n]"
        read -s -n 1 ans; echo "$ans"
        if [ "$ans" == "n" ]; then
            return 0
        else
            rm -rf "/home/$USER/.RG/"
        fi
    fi

    mkdir "/home/$USER/.RG"
    cp 'ListOfMusic.txt' "/home/$USER/.RG/"
    cp 'ListOfSound.txt' "/home/$USER/.RG/"
}

PostSetup() {
    echo ""
    echo ""
    echo -e "\t\tSetup finished, now you can build game."
    echo ""
    echo "To build game use:"
    echo ""
    echo "cd build"
    echo "make game"
    echo ""
    echo "Or 'make' to make it with doxygen documntation"
}

clear
SetupLibraries
DownloadAssets
SetupBuildDir
CreateConfigDir
PostSetup
