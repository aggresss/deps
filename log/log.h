#ifndef __LOG_H__
#define __LOG_H__

#include <stdarg.h>
#include <stdio.h>

extern int nLogLevel;
typedef void (*LogFunc)(int nLevel, char * pLog);

void SetLogLevel(int nLevel);
void SetLogCallback(LogFunc f);
void LogGenerate(const char *file, const int line, const char *func, const int nLevel, const char * pFmt, ...);

#define LOG_LEVEL_TRACE 1
#define LOG_LEVEL_DEBUG 2
#define LOG_LEVEL_INFO  3
#define LOG_LEVEL_WARN  4
#define LOG_LEVEL_ERROR 5

#ifndef DEFAULT_LOG_LEVEL
#define DEFAULT_LOG_LEVEL LOG_LEVEL_TRACE
#endif

#define MAX_LOG_LENGTH 512

#define LOG_WITH_TIME 1

#define LOG_WITH_COLOR 1

#ifdef LOG_WITH_COLOR

#define NONE            "\e[0m"
#define BLACK           "\e[0;30m"
#define RED             "\e[0;31m"
#define GREEN           "\e[0;32m"
#define YELLOW          "\e[0;33m"
#define BLUE            "\e[0;34m"
#define MAGENTA         "\e[0;35m"
#define CYAN            "\e[0;36m"
#define WHITE           "\e[0;37m"

#define L_BLACK         "\e[1;30m"
#define L_RED           "\e[1;31m"
#define L_GREEN         "\e[1;32m"
#define L_YELLOW        "\e[1;33m"
#define L_BLUE          "\e[1;34m"
#define L_MAGENTA       "\e[1;35m"
#define L_CYAN          "\e[1;36m"
#define L_WHITE         "\e[1;37m"

#define BOLD            "\e[1m"
#define UNDERLINE       "\e[4m"
#define BLINK           "\e[5m"
#define REVERSE         "\e[7m"
#define HIDE            "\e[8m"
#define CLEAR           "\e[2J"
#define CLRLINE         "\r\e[K"

#endif /* LOG_WITH_COLOR */

#define LogTrace(fmt,...) \
        LogGenerate(__FILE__, __LINE__, __FUNCTION__, LOG_LEVEL_TRACE, "[T]" fmt "\n", ##__VA_ARGS__)
#define LogDebug(fmt,...) \
        LogGenerate(__FILE__, __LINE__, __FUNCTION__, LOG_LEVEL_DEBUG, "[D]" fmt "\n", ##__VA_ARGS__)
#define LogInfo(fmt,...) \
        LogGenerate(__FILE__, __LINE__, __FUNCTION__, LOG_LEVEL_INFO, "[I]" fmt "\n", ##__VA_ARGS__)
#define LogWarn(fmt,...) \
        LogGenerate(__FILE__, __LINE__, __FUNCTION__, LOG_LEVEL_WARN, "[W]" fmt "\n", ##__VA_ARGS__)
#define LogError(fmt,...) \
        LogGenerate(__FILE__, __LINE__, __FUNCTION__, LOG_LEVEL_ERROR, "[E]" fmt "\n", ##__VA_ARGS__)

#define log_trace(args...) LogTrace(args)
#define log_debug(args...) LogDebug(args)
#define log_info(args...) LogInfo(args)
#define log_warn(args...) LogWarn(args)
#define log_error(args...) LogError(args)

#endif
