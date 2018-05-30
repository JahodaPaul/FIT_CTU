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

#define RESET   "\033[0m"
#define BLACK   "\033[30m"      /* Black */
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define YELLOW  "\033[33m"      /* Yellow */
#define BLUE    "\033[34m"      /* Blue */
#define MAGENTA "\033[35m"      /* Magenta */
#define CYAN    "\033[36m"      /* Cyan */
#define WHITE   "\033[37m"      /* White */
#define BOLDBLACK   "\033[1m\033[30m"      /* Bold Black */
#define BOLDRED     "\033[1m\033[31m"      /* Bold Red */
#define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
#define BOLDYELLOW  "\033[1m\033[33m"      /* Bold Yellow */
#define BOLDBLUE    "\033[1m\033[34m"      /* Bold Blue */
#define BOLDMAGENTA "\033[1m\033[35m"      /* Bold Magenta */
#define BOLDCYAN    "\033[1m\033[36m"      /* Bold Cyan */
#define BOLDWHITE   "\033[1m\033[37m"      /* Bold White */

namespace RG { namespace Util {
    //! \class CLogger
    /*!
     * \brief
     * Logger class provides the service of storing application logs into the specific log file.
     * <pre>
     * It provides several options for configuring the logging.
     * (e.g.: Setting if logs should be sent to stdout, log file or both.
     *        Setting the weight limit of logs sent to the output.
     *        Formatting logs sent to output.
     *        etc.
     * )
     * </pre>
     */
    class CLogger
    {

        public:

            /// Class constants for representing log types.
            enum TYPE {
                INFO, /**< Informational log level. */
                WARNING, /**< Warning log level. */
                ERROR /**< Error log level. */
            };

            /// Class constants for representing class flags.
            enum FLAGS {
                LEVEL = 1, /**< Display log level. */
                DATETIME = 2, /**< Display log time and date. */
                FILE = 4, /**< Display the file in which the log occurred. */
                LINE = 8, /**< Display the line on which the log occurred. */
                LIMIT = 16 /**< Apply limitation of stored logs. */
            };

            /// Class constants for representing outputs.
            enum STREAM {
                STD_ONLY, /**< Print log only to standard output. */
                FILE_ONLY, /**< Print log only to file output. */
                BOTH /**< Print log to both standard and file outputs. */
            };

            //! Logger class constructor.
            /*!
             * Constructor may take three parameters:
             * @param type Logging type limit.
             * @param delimiter Delimiter of item in log.
             * @param logsMax Maximal number of stored logs.
             * */
            CLogger(TYPE type = TYPE::WARNING, const std::string & delimiter = "\t", unsigned int logsMax = 1000);

            /// Logger class destructor.
            ~CLogger();

            //! Method for logging info logs.
            /*!
             * Method takes three parameters:
             * @param file File in which the event occurred.
             * @param line Line on which the event occurred.
             * @param message Log message.
             */
            void _Info( const char * file, int line, const std::string & message );

            //! Method for logging warning logs.
            /*!
            * Method takes three parameters:
            * @param file File in which the event occurred.
            * @param line Line on which the event occurred.
            * @param message Log message.
            */
            void _Warning( const char * file, int line, const std::string & message );

            //! Method for logging error logs.
            /*!
            * Method takes three parameters:
            * @param file File in which the event occurred.
            * @param line Line on which the event occurred.
            * @param message Log message.
            */
            void _Error( const char * file, int line, const std::string & message );

            //! Method for setting limit of logs sent to the output.
            /*!
             * Method takes two parameters:
             * @param type Logging limit.
             * @param streamType Output type to which set the limit.
             */
            void SetLimit(TYPE type = WARNING, STREAM streamType = BOTH);

            //! Method for setting the logger class flags.
            /*!
             * Method takes one parameter:
             * @param flags Flags to be set.
             */
            void SetFlags(unsigned char flags);

            //! Method for setting the log file directory.
            /*!
             * Method takes one parameter:
             * @param logDir Log file directory.
             */
            void SetLogDir(const std::string &logDir);

            //! Method for setting the log file name.
            /*!
             * Method takes one parameter:
             * @param logFile Log file name.
             */
            void SetLogFile(const std::string &logFile);

            //! Method for setting log items delimiter.
            /*!
             * Method takes one parameter:
             * @param logDelimiter Log items delimiter.
             */
            void SetDelimiter(const std::string &logDelimiter);

            //! Method for setting maximal number of stored logs in the log file.
            /*!
             * Method takes one parameter:
             * @param max Maximal number of stored logs.
             */
            void SetLogsMax(unsigned int max);

        private:

            //! Method for logging.
            /*!
             * This method is called by _Info, _Warning and _Error methods for logging the right log type.
             *
             * Method takes four parameters:
             * @param file File in which the event occurred.
             * @param line Line on which the event occurred.
             * @param msg Log message.
             * @param type Log type.
             */
            void Log(const char * file, int line, const std::string & msg, TYPE type );

            /// Method for opening stream to the log file.
            bool Open();

            /// Method for closing the stream to the log file.
            bool Close();

            /// Method for cutting logs in the log file to the set limit.
            void CutLogFile();

            /// Member variable for holding stdout logging limit.
            TYPE m_StdLim;

            /// Member variable for holding file output logging limit.
            TYPE m_FileLim;

            /// Member variable for holding the class flags.
            unsigned char m_Flags;

            /// Member variable for holding log data delimiter.
            std::string m_Delimiter;

            /// Member variable for holding output stream to the log file.
            std::ofstream m_Stream;

            /// Member variables for holding number of logs in the log file.
            unsigned int m_LogsInFile;

            /// Member variable for holding limit of logs in the log file.
            unsigned int m_logsMax;

            /// Member variable representing logs levels for printing.
            const char * m_Levels[3] = {
                    "INFO", "WARNING", "ERROR"
            };

            /// Member variable for log file directory.
            std::string m_LogDir = "./";

            /// Member variable for log file name.
            std::string m_LogFile = "log.log";

    };
} }
