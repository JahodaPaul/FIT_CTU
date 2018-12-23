//
// Created by pjahoda on 1.5.18.
//

#include "View/RoomHistory.hpp"
#include <iostream>

namespace RG {
    namespace View {

        RG::View::RoomHistory::RoomHistory() {
            LoadHistory();
        }

        RG::View::RoomHistory::~RoomHistory() {
            SaveHistoroy();
        }

        void RG::View::RoomHistory::LoadHistory() {
            if(this->FileToMap(this->historyFileName,this->roomHistory) == false){
                std::cout << "File not found" << std::endl;
            }
        }

        void RG::View::RoomHistory::SaveHistoroy() {
            if(this->MapToFile(this->historyFileName,this->roomHistory) == false){
                std::cout << "could not save into file" << std::endl;
            }
        }


        bool RG::View::RoomHistory::MapToFile(const std::string & filename,const std::map<std::string,std::string> & fileMap)     //Write Map
        {
            std::ofstream ofile;
            ofile.open(filename.c_str());
            if(!ofile)
            {
                return false;           //file does not exist and cannot be created.
            }
            for(std::map<std::string,std::string>::const_iterator iter= fileMap.begin(); iter!=fileMap.end(); ++iter)
            {
                ofile<<iter->first<<"|"<<iter->second;
                ofile<<"\n";
            }
            return true;
        }

        std::vector<std::string> RG::View::RoomHistory::Split(std::string strToSplit, char delimeter)
        {
            std::istringstream ss(strToSplit);
            std::string item;
            std::vector<std::string> splittedStrings;
            while (std::getline(ss, item, delimeter))
            {
                splittedStrings.push_back(item);
            }
            //delete '\n'
            if (splittedStrings[splittedStrings.size()-1][splittedStrings[splittedStrings.size()-1].length()-1] == '\n'){
                std::string tmp = "";
                for(int i=0;i<(int)splittedStrings[splittedStrings.size()-1].length()-1;i++){
                    tmp += splittedStrings[splittedStrings.size()-1][i];
                }
                splittedStrings[splittedStrings.size()-1] = tmp;
            }
            return splittedStrings;
        }

        bool RG::View::RoomHistory::FileToMap(const std::string & filename, std::map<std::string,std::string> & fileMap)  //Read Map
        {
            std::ifstream ifile;
            ifile.open(filename.c_str());
            if(!ifile)
                return false;   //could not read the file.
            std::string line;
            std::string key;
            std::vector<std::string> v_str;
            while(ifile>>line)
            {
                v_str = this->Split(line,'|');
                fileMap.insert(std::make_pair(v_str[0],v_str[1]));
            }
            return true;
        }
    }
}