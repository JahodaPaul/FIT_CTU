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

            ///calls FileToMap function
            void LoadHistory();

            ///calls MapToFile function
            void SaveHistoroy();

            /// loads room history - map where key is room ID and value is string path to background image
            bool FileToMap(const std::string &filename, std::map<std::string,std::string> &);

            /// saves room history - map where key is room ID and value is string path to background image
            bool MapToFile(const std::string &filename,const std::map<std::string,std::string> &);

            ///split string (line in a file) based on delimeter parameter
            std::vector<std::string> Split(std::string strToSplit, char delimeter);

            const std::string historyFileName = "./history.txt";
        };
    }
}

#endif //GAME_ROOMHISTORY_H
