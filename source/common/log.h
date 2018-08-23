#ifndef _BASELOGGER_H_
#define _BASELOGGER_H_

#include <iostream>

extern "C"
{
    #include <time.h>
    #include <string.h>
    #include <stdio.h>
    #include <stdarg.h>
    #include <unistd.h>
    #include <sys/stat.h>
}

enum LOG_LEVEL
{
	LOG_LEVEL_EMERG  = 0, 
    LOG_LEVEL_ALERT		, 
    LOG_LEVEL_CRIT		, 
    LOG_LEVEL_ERROR     , 
    LOG_LEVEL_WARN	    , 
    LOG_LEVEL_NOTICE	, 
    LOG_LEVEL_INFO      ,
    LOG_LEVEL_DEBUG
};

enum LOG_TYPE
{
    LOG_STDOUT_TYPE = 0,
    LOG_FILE_TYPE      ,
    LOG_SYSLOG_TYPE
};

#define MAX_LOG_LENGTH 4096

class BaseLogger
{
    public:
        BaseLogger(void);
        virtual ~BaseLogger(void) = 0;
        void LogDebug(const char * info, const char * file, const unsigned long line, const char * function);
        void LogInfo(const char * info, const char * file, const unsigned long line, const char * function);
        void LogNotice(const char * info, const char * file, const unsigned long line, const char * function);
        void LogWarn(const char * info, const char * file, const unsigned long line, const char * function);
        void LogError(const char * info, const char * file, const unsigned long line, const char * function);
        void LogCrit(const char * info, const char * file, const unsigned long line, const char * function);
        void LogAlert(const char * info, const char * file, const unsigned long line, const char * function);
        void LogEmerg(const char * info, const char * file, const unsigned long line, const char * function);
        
        virtual void Log(LOG_LEVEL level, const char * strMsg, const char * file, const unsigned long line, const char * function) = 0;
        LOG_TYPE GetLogType();
        const static char * GetSystemTime(const char * format = "%4d-%02d-%02d %02d:%02d:%02d");
        static const char * LEVEL_STRING[11];
    
    protected:
        LOG_TYPE m_LogType;

    private:
        static char m_CurrentTime[512];
};

#endif