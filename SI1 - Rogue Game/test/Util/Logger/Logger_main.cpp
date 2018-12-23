#include "Util/Logger.hpp"

using namespace RG::Util;

int main() {
    CLogger logger(CLogger::TYPE::INFO);
    logger.SetLimit(CLogger::TYPE::INFO);
    logger.SetFlags(CLogger::FLAGS::LEVEL | CLogger::FLAGS::DATETIME | CLogger::FLAGS::FILE | CLogger::FLAGS::LINE | CLogger::FLAGS::LIMIT);
    //logger.SetDelimiter("|");
    //logger.SetLogFile( "./log.txt" );
    //logger.SetLogsMax(100);

    logger.Info("Some info message. 1");
    logger.Error("Error has occurred. 2");
}