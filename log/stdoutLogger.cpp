#include "stdoutLogger.h"
#include <iostream>

StdOutLogger::StdOutLogger(void) : BaseLogger()
{
    m_LogType = LOG_STDOUT_TYPE;
}

StdOutLogger::~StdOutLogger(void)
{

}

void StdOutLogger::Log(LOG_LEVEL level, const char * strMsg, const char * file, const unsigned long line, const char * function)
{
    char logMsg[MAX_LOG_LENGTH];
    memset(&logMsg, 0, sizeof logMsg);

    snprintf(logMsg, MAX_LOG_LENGTH, "[%s] [%s] %s, File: %s, Line: %lu, Function: %s\n", GetSystemTime(), BaseLogger::LEVEL_STRING[level], strMsg, file, line, function);
    std::cout << logMsg;
}