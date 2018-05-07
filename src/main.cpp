#include <iostream>

#include "View/Player.hpp"
#include "../include/Controller/GameController.hpp"

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <pwd.h>
#include <dirent.h>
#include <experimental/filesystem>

int main() {
    struct passwd *pw = getpwuid(getuid());
    std::string homedir{ pw->pw_dir };

    std::string run_dir_name = homedir + "/.RG";


    DIR* run_dir = opendir(run_dir_name.c_str());
    if ( !run_dir ) {
        std::cout << "Creating run_dir - \"" << run_dir_name << "\"" << std::endl;
        mkdir( run_dir_name.c_str(), 0700 );
        std::cout << "Copying default files to run dir." << std::endl;
        std::experimental::filesystem::copy("/usr/share/RG/defaults/", run_dir_name, std::experimental::filesystem::copy_options::recursive);
    }

    chdir( run_dir_name.c_str() );

    std::cout << homedir << std::endl;

    std::cout << "main" << std::endl;
    RG::GameController g;
    g.Run();
}
