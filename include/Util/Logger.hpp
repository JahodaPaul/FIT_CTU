#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <chrono>
#include <ctime>
#include <sstream>

#define Info(msg) _Info(__FILE__,__LINE__,msg)
#define Warning(msg) _Warning(__FILE__,__LINE__,msg)
#define Error(msg) _Error(__FILE__,__LINE__,msg)

/**
 * \brief
 * Logger class provides the service of storing application logs into the specific log file.
 * */

/**
 * <pre>
 * It provides several options for configuring the logging.
 * (e.g.: Setting if logs should be sent to stdout, log file or both.
 *        Setting the weight limit of logs sent to the output.
 *        Formatting logs sent to output.
 *        etc.
 * )
 * </pre>
 * */

namespace RG {
    class CLogger
    {

        public:

            ///Class constants for representing log weight
            enum TYPE { INFO, WARNING, ERROR };

            ///Class constants for representing class flags
            enum FLAGS { DATETIME = 1, FILE = 2, LINE = 4, LIMIT = 8 };

            ///Class constants for representing outputs
            enum STREAM { STD_ONLY, FILE_ONLY, BOTH };

            /** Logger class constructor */
            CLogger(TYPE type = TYPE::WARNING, const std::string & delimiter = "\t", unsigned int logsMax = 1000);

            /** Logger class destructor */
            ~CLogger();

            /** Method for opening stream to the log file */
            bool Open();

            /** Method for closing the stream to the log file */
            bool Close();

            /** Method for logging info logs */
            void _Info( const char * file, int line, const std::string & message );

            /** Method for logging warning logs */
            void _Warning( const char * file, int line, const std::string & message );

            /** Method for logging error logs */
            void _Error( const char * file, int line, const std::string & message );

            /** Method for setting limit of logs sent to the output */
            void SetLimit(TYPE type, STREAM streamType);

            /** Method for setting the logger class flags */
            void SetFlags(unsigned char flags);

            /** Method for setting the log file directory */
            void SetLogDir(const std::string &logDir);

            /** Method for settign the log file name */
            void SetLogFile(const std::string &logFile);

            /** Method for setting log data delimiter */
            void SetDelimiter(const std::string &logDelimiter);

            /** Method for setting maximal number of stored logs in the log file */
            void SetLogsMax(unsigned int max);

            /** Method for cutting logs in the log file to the set limit */
            void CutLogFile();

        private:

            /** Method for logging. */
            void Log(const char * file, int line, const std::string & msg, TYPE type );

            ///Member variable for holding stdout logging limit.
            TYPE m_StdLim;

            ///Member variable for holding file output logging limit.
            TYPE m_FileLim;

            ///Member variable for holding the class flags.
            unsigned char m_Flags;

            ///Member variable for holding log data delimiter.
            std::string m_Delimiter;

            ///Member variable for holding output stream to the log file.
            std::ofstream m_Stream;

            ///Member variables for holding number of logs in the log file.
            unsigned int m_LogsInFile;

            ///Membe variable for holding limit of logs in the log file.
            unsigned int m_logsMax;

            ///Member variable for log file directory
            std::string m_LogDir = "./";

            ///Member variable for log file name
            std::string m_LogFile = "log.log";

    };
}
