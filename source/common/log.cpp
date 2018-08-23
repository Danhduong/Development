#include "log.h"

BaseLogger::BaseLogger(void)
{

}

BaseLogger::~BaseLogger(void)
{

}

LOG_TYPE BaseLogger::GetLogType()
{
    return m_LogType;
}

void BaseLogger::LogDebug(const char * info, const char * file, const unsigned long line, const char * function)
{
    Log(LOG_LEVEL_DEBUG, info, file, line, function);
}

void BaseLogger::LogInfo(const char * info, const char * file, const unsigned long line, const char * function)
{
    Log(LOG_LEVEL_INFO, info, file, line, function);
}

void BaseLogger::LogNotice(const char * info, const char * file, const unsigned long line, const char * function)
{
    Log(LOG_LEVEL_NOTICE, info, file, line, function);
}

void BaseLogger::LogWarn(const char * info, const char * file, const unsigned long line, const char * function)
{
    Log(LOG_LEVEL_WARN, info, file, line, function);
}

void BaseLogger::LogError(const char * info, const char * file, const unsigned long line, const char * function)
{
    Log(LOG_LEVEL_ERROR, info, file, line, function);
}

void BaseLogger::LogCrit(const char * info, const char * file, const unsigned long line, const char * function)
{
    Log(LOG_LEVEL_CRIT, info, file, line, function);
}

void BaseLogger::LogAlert(const char * info, const char * file, const unsigned long line, const char * function)
{
    Log(LOG_LEVEL_ALERT, info, file, line, function);
}

void BaseLogger::LogEmerg(const char * info, const char * file, const unsigned long line, const char * function)
{
    Log(LOG_LEVEL_EMERG, info, file, line, function);
}

const char * BaseLogger::GetSystemTime(const char * format)
{
    time_t rawtime;
    time(&rawtime);    

    struct tm *timeinfo;
    timeinfo = localtime(&rawtime);
    snprintf(m_CurrentTime, sizeof(m_CurrentTime), format, 1900 + timeinfo->tm_year, 1 + timeinfo->tm_mon, timeinfo->tm_mday, timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);

    return m_CurrentTime;
}

const char* BaseLogger::LEVEL_STRING[] = {"EMERGENCY" ,"ALERT", "CRITICAL", "ERROR", "WARNNING", "NOTICE", "INFO", "DEBUG"};

char BaseLogger::m_CurrentTime[] = "\0";

FileLogger::FileLogger(void) : BaseLogger()
{
    m_LogType = LOG_FILE_TYPE;
}

FileLogger::~FileLogger(void)
{

}

void FileLogger::Log(LOG_LEVEL level, const char * strMsg, const char * file, const unsigned long line, const char * function)
{
    char logMsg[MAX_LOG_LENGTH];
    memset(logMsg, 0, sizeof(logMsg));

    snprintf(logMsg, MAX_LOG_LENGTH, "[%s] [%s] %s, File: %s, Line: %lu, Function: %s\n", GetSystemTime(), BaseLogger::LEVEL_STRING[level], strMsg, file, line, function);
    _WriteLogToFile(logMsg, file);
}

void FileLogger::_WriteLogToFile(const char * strMsg, const char * filename)
{
    char logfile[MAX_FILE_NAME_LENGTH];
    memset(logfile, 0, sizeof(logfile));

    const char *ext = ".log";
    const char *pos = NULL;
    const char *newpos = NULL;

    strncpy(logfile, LOG_PATH, sizeof(LOG_PATH));
    pos = strrchr(filename, '/');

    if(pos != NULL)
    {
        newpos = pos;
    }
    else
    {
        newpos = filename;
    }
    
    newpos = pos != NULL ? (pos+1) : filename;
    FILE * fp;

    if(access(logfile, 0) == -1)
    {
        mkdir(logfile, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    }

    strcat(logfile, newpos);
    strcat(logfile, ext);
    fp = fopen(logfile, "at+");

    if(NULL == fp)
    {
        return;
    }
    fprintf(fp, "%s", strMsg);
    fflush(fp);
    fclose(fp);
}
