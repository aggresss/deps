#ifndef __LOG_H__
#define __LOG_H__

#include <stdarg.h>
#include <stdio.h>

#define _s_l_(x) #x
#define _str_line_(x) _s_l_(x)
#define __STR_LINE__ _str_line_(__LINE__)

#define LOG_LEVEL_TRACE 1
#define LOG_LEVEL_DEBUG 2
#define LOG_LEVEL_INFO  3
#define LOG_LEVEL_WARN  4
#define LOG_LEVEL_ERROR 5

#define MAX_LOG_LENGTH 512

#define LOG_WITH_TIME

#ifndef DEFAULT_LOG_LEVEL
#define DEFAULT_LOG_LEVEL LOG_LEVEL_TRACE
#endif

extern int nLogLevel;
typedef void (*LogFunc)(int nLevel, char * pLog);

void SetLogLevel(int nLevel);
void SetLogCallback(LogFunc f);
void Log(int nLevel, char * pFmt, ...);

#ifndef __PROJECT__
#define __PROJECT__
#endif

#ifndef __FILE_NAME__
#define __FILE_NAME__
#define __FILE_LINE__
#else
#define __FILE_LINE__ ":" __STR_LINE__
#endif

#define LogTrace(fmt,...) \
        Log(LOG_LEVEL_TRACE, "[T]" __PROJECT__ __FILE_NAME__ __FILE_LINE__ " " fmt "\n", ##__VA_ARGS__)
#define LogDebug(fmt,...) \
        Log(LOG_LEVEL_DEBUG, "[D]" __PROJECT__ __FILE_NAME__ __FILE_LINE__ " " fmt "\n", ##__VA_ARGS__)
#define LogInfo(fmt,...) \
        Log(LOG_LEVEL_INFO,  "[I]" __PROJECT__ __FILE_NAME__ __FILE_LINE__ " " fmt "\n", ##__VA_ARGS__)
#define LogWarn(fmt,...) \
        Log(LOG_LEVEL_WARN,  "[W]" __PROJECT__ __FILE_NAME__ __FILE_LINE__ " " fmt "\n", ##__VA_ARGS__)
#define LogError(fmt,...) \
        Log(LOG_LEVEL_ERROR, "[E]" __PROJECT__ __FILE_NAME__ __FILE_LINE__ " " fmt "\n", ##__VA_ARGS__)

#define log_trace(args...) LogTrace(args)
#define log_debug(args...) LogDebug(args)
#define log_info(args...) LogInfo(args)
#define log_warn(args...) LogWarn(args)
#define log_error(args...) LogError(args)


#endif
