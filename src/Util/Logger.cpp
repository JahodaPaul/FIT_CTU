#include "Util/Logger.hpp"

namespace RG {
    CLogger::CLogger(CLogger::TYPE type, const std::string &delimiter, unsigned int logsMax)
            : m_StdLim{type}, m_FileLim{type}, m_Delimiter(delimiter), m_logsMax(logsMax) {
        Open();
        std::ifstream f(m_LogFile);
        std::string line;
        unsigned int i;
        for (i = 0; std::getline(f, line); i++);
        m_LogsInFile = i;
        f.close();
    }

    CLogger::~CLogger() {
        std::cout << std::flush;
        m_Stream.flush();
        Close();
    }

    bool CLogger::Open() {
        if (!m_Stream.is_open()) {
            std::string fullPath = m_LogDir + m_LogFile;
            try {
                m_Stream.open(fullPath, std::ofstream::out | std::ofstream::app);
            }
            catch (std::exception &e) {
                return false;
            }
        }
        return true;
    }

    bool CLogger::Close() {
        try {
            if (m_Stream.is_open()) {
                m_Stream.close();
                return !m_Stream.is_open();
            } else return false;
        }
        catch (std::exception &e) {
            return false;
        }
    }

    void CLogger::Log(const char *file, int line, const std::string &msg, CLogger::TYPE type) {
        if (type < m_StdLim && type < m_FileLim) return;

        std::chrono::system_clock::time_point p = std::chrono::system_clock::now();
        std::time_t t = std::chrono::system_clock::to_time_t(p);
        std::string strTime = ctime(&t);
        strTime = strTime.substr(0, strTime.length() - 1);

        std::stringstream outStream;

        if (m_Flags & CLogger::FLAGS::DATETIME)
            outStream << "[" << strTime << "]" << m_Delimiter;
        if (m_Flags & CLogger::FLAGS::FILE)
            outStream << "[" << file << "]" << m_Delimiter;
        if (m_Flags & CLogger::FLAGS::LINE)
            outStream << "[line: " << line << "]" << m_Delimiter;
        outStream << msg;
        outStream << "\n";

        if (type >= m_StdLim)
            std::cout << outStream.str();
        if (type >= m_FileLim)
            m_Stream << outStream.str() << std::flush;

        m_LogsInFile++;

        if (m_Flags & CLogger::FLAGS::LIMIT)
            if (m_LogsInFile >= 2 * m_logsMax)
                CutLogFile();

    }

    void CLogger::_Info(const char *file, int line, const std::string &message) {
        Log(file, line, message, CLogger::TYPE::INFO);
    }

    void CLogger::_Warning(const char *file, int line, const std::string &message) {
        Log(file, line, message, CLogger::TYPE::WARNING);
    }

    void CLogger::_Error(const char *file, int line, const std::string &message) {
        Log(file, line, message, CLogger::TYPE::ERROR);
    }

    void CLogger::SetLimit(CLogger::TYPE type = WARNING, CLogger::STREAM streamType = BOTH) {
        if (streamType == CLogger::STREAM::STD_ONLY || streamType == CLogger::STREAM::BOTH)
            m_StdLim = type;

        if (streamType == CLogger::STREAM::FILE_ONLY || streamType == CLogger::STREAM::BOTH)
            m_FileLim = type;
    }

    void CLogger::SetFlags(unsigned char flags) {
        m_Flags = flags;
    }

    void CLogger::SetLogDir(const std::string &logDir) {
        m_LogDir = logDir;
        if (m_Stream.is_open()) {
            Close();
            Open();
        }
    }

    void CLogger::SetLogFile(const std::string &logFile) {
        m_LogFile = logFile;
        if (m_Stream.is_open()) {
            Close();
            Open();
        }
        unsigned int i;
        std::string line;
        std::ifstream f(m_LogFile);
        for (i = 0; std::getline(f, line); i++);
        f.close();
        m_LogsInFile = i;
    }

    void CLogger::SetDelimiter(const std::string &logDelimiter) {
        m_Delimiter = logDelimiter;
    }

    void CLogger::SetLogsMax(unsigned int max) {
        m_logsMax = max;
    }

    void CLogger::CutLogFile() {
        std::ifstream f(m_LogFile.c_str());
        std::ofstream tmp("tmp.txt");
        std::string s;

        for (unsigned int i = 0; i < m_logsMax; i++)
            std::getline(f, s);

        for (unsigned int i = 0; i < m_logsMax; i++) {
            std::getline(f, s);
            tmp << s << '\n';
        }
        tmp << std::flush;

        f.close();
        tmp.close();

        Close();
        std::remove(m_LogFile.c_str());
        Open();

        std::ifstream tmpFile("tmp.txt");

        while (std::getline(tmpFile, s))
            m_Stream << s << '\n';
        m_Stream << std::flush;

        tmpFile.close();
        std::remove("tmp.txt");

        m_LogsInFile = m_logsMax;

    }

    int main() {
        CLogger logger(CLogger::TYPE::INFO);
        logger.SetLimit(CLogger::TYPE::INFO);
        logger.SetFlags(CLogger::FLAGS::DATETIME | CLogger::FLAGS::FILE | CLogger::FLAGS::LINE | CLogger::FLAGS::LIMIT);
        //logger.SetDelimiter("|");
        //logger.SetLogFile( "./log.txt" );
        //logger.SetLogsMax(100);

        logger.Info("Some info message. 1");
        logger.Error("Error has occurred. 2");
    }
}