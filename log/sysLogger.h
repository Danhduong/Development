#ifndef _SYSLOGGER_H_
#define _SYSLOGGER_H_

#include "baseLogger.h"
#include <syslog.h>

extern "C"
{
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
}

class SyslogLogger : public BaseLogger
{
    public:
        SyslogLogger(void);
        ~SyslogLogger(void);
        void SetFacilityCode(int facilityCode);
        void SetLogOpt(int logOpt);
        void Log(LOG_LEVEL level, const char * strMsg, const char * file, const unsigned long line, const char * function);

    private:
        int m_FacilityCode;
        int m_LogOpt;
};

#endif