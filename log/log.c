#include "log.h"

int nLogLevel = DEFAULT_LOG_LEVEL;
LogFunc logFunc = NULL;

void SetLogCallback(LogFunc f)
{
    logFunc = f;
}

void SetLogLevel(int level)
{
    if (level >= LOG_LEVEL_TRACE && level <= LOG_LEVEL_ERROR)
        nLogLevel = level;
}

void Log(int nLevel, char * pFmt, ...)
{
    char log_buf[MAX_LOG_LENGTH + 1] = { 0 };
    if (nLevel >= nLogLevel) {
        va_list ap;
        va_start(ap, pFmt);
#ifdef LOG_WITH_TIME
#include <time.h>
#include <string.h>
        char time_buf[64] = { 0 };
        time_t t = time(NULL);
        struct tm *tm_now = localtime(&t);
        strftime(time_buf, 64, "[%Y-%m-%d %H:%M:%S]", tm_now);
        int time_len = strlen(time_buf);
        strncpy(log_buf, time_buf, strlen(time_buf));
        vsnprintf(log_buf + time_len, (MAX_LOG_LENGTH - time_len), pFmt, ap);
#else
        vsnprintf(log_buf, MAX_LOG_LENGTH, pFmt, ap);
#endif /* LOG_WITH_TIME */
        va_end(ap);
        if (logFunc == NULL) {
#ifdef LOG_WITH_COLOR
            switch (nLevel) {
                case LOG_LEVEL_TRACE:
                    printf(L_BLUE "%s" NONE, log_buf);
                    break;
                case LOG_LEVEL_DEBUG:
                    printf(L_CYAN "%s" NONE, log_buf);
                    break;
                case LOG_LEVEL_INFO:
                    printf(L_GREEN "%s" NONE, log_buf);
                    break;
                case LOG_LEVEL_WARN:
                    printf(L_YELLOW "%s" NONE, log_buf);
                    break;
                case LOG_LEVEL_ERROR:
                    printf(L_RED "%s" NONE, log_buf);
                    break;
                default:
                    break;
            }
#else
    printf("%s", log_buf);
#endif /* LOG_WITH_COLOR */
        } else {
            logFunc(nLevel, log_buf);
        }
    }
}
