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
    if [ -d 'assets' ]; then
        echo "'assets' directory found, should I delete it and create new one? [y/n]"
        read -s -n 1 ans; echo "$ans"
        if [ "$ans" == "n" ]; then
            return 0
        else
            rm -rf 'assets'
        fi
    fi
    echo ""
    echo ""
    echo "Creating 'assets' directory..."
    echo ""
    mkdir 'assets'

    echo ""
    echo ""
    echo "Downloading assets..."
    echo ""
    cd 'assets'
    curl 'ftp://mybestcloud.xyz/pub/assets-20180506T223100Z-001.zip' --output 'graphics.zip' 2>/dev/null
    unzip 'graphics.zip'
    rm 'graphics.zip'
    cd ..
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
PostSetup
