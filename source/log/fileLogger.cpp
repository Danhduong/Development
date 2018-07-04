#include "fileLogger.h"

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