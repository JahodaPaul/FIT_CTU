//
// Created by pjahoda on 1.5.18.
//
#include <string>
#include <map>
#include <map>
#include <fstream>
#include <sstream>
#include <vector>

#ifndef GAME_ROOMHISTORY_H
#define GAME_ROOMHISTORY_H

namespace RG{
    namespace View{
        class RoomHistory{
        public:
            RoomHistory();
            virtual ~RoomHistory();
        protected:
            std::map<std::string,std::string> roomHistory;
        private:
            void LoadHistory();
            void SaveHistoroy();
            bool FileToMap(const std::string &filename, std::map<std::string,std::string> &);
            bool MapToFile(const std::string &filename,const std::map<std::string,std::string> &);
            std::vector<std::string> Split(std::string strToSplit, char delimeter);

            const std::string historyFileName = "../assets/history.txt";
        };
    }
}

#endif //GAME_ROOMHISTORY_H
