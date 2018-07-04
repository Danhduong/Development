#include "sysLogger.h"

SyslogLogger::SyslogLogger(void) : BaseLogger()
{
    m_LogType = LOG_SYSLOG_TYPE;
    m_FacilityCode = LOG_USER;
    m_LogOpt = LOG_PID;
}

SyslogLogger::~SyslogLogger(void)
{

}

void SyslogLogger::SetFacilityCode(int facilityCode)
{
    m_FacilityCode = facilityCode;
}

void SyslogLogger::SetLogOpt(int logOpt)
{
    m_LogOpt = logOpt;
}

void SyslogLogger::Log(LOG_LEVEL level, const char * strMsg, const char * file, const unsigned long line, const char * function)
{
    char logMsg[MAX_LOG_LENGTH];
    memset(logMsg, 0, sizeof(logMsg));

    snprintf(logMsg, MAX_LOG_LENGTH, "[%s] %s, File: %s, Line: %lu, Function: %s\n", BaseLogger::LEVEL_STRING[level], strMsg, file, line, function);
    openlog(file, m_LogOpt, m_FacilityCode);
    syslog(level, "%s", logMsg);
    closelog();
}