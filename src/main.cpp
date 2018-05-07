#include <iostream>

#include "View/Player.hpp"
#include "Controller/GameController.hpp"
#include "common.hpp"
#include "Util/Logger.hpp"

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <pwd.h>
#include <dirent.h>
#include <experimental/filesystem>

RG::CLogger mainLog(RG::CLogger::INFO, " ", 50000);

int main() {
    struct passwd *pw = getpwuid(getuid());
    std::string homedir{ pw->pw_dir };

    std::string run_dir_name = homedir + "/.RG";


    DIR* run_dir = opendir(run_dir_name.c_str());
    if ( !run_dir ) {
        //mainLog.Info("Creating run_dir - \"" + run_dir_name + "\"" );
        mkdir( run_dir_name.c_str(), 0700 );
        //mainLog.Info("Copying default files to run dir.");
        std::experimental::filesystem::copy("/usr/share/RG/defaults/", run_dir_name, std::experimental::filesystem::copy_options::recursive);
    }

    chdir( run_dir_name.c_str() );

    mainLog.SetFlags(RG::CLogger::FLAGS::FILE);
    mainLog.SetLogFile( "./log.txt" );
    mainLog.SetLimit(RG::CLogger::INFO, RG::CLogger::STREAM::BOTH);

    mainLog.Info("Changed current directory to: \"" + run_dir_name + "\"");
    

    RG::GameController g;
    g.Run();
}
