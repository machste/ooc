/**
 * @file    util/log.h
 *
 * @brief   Logging and Debugging Interface
 * 
 */
#ifndef _UTIL_LOG_H_
#define _UTIL_LOG_H_

#define LOG_EMERGENCY "EMERGENCY"
#define LOG_ALERT "ALERT"
#define LOG_CRITICAL "CRITICAL"
#define LOG_ERROR "ERROR"
#define LOG_WARNING "WARNING"
#define LOG_NOTICE "NOTICE"
#define LOG_INFO "INFO"
#define LOG_DEBUG "DEBUG"

typedef enum {
    LOG_LEV_EMERGENCY = 0,
    LOG_LEV_ALERT = 1,
    LOG_LEV_CRITICAL = 2,
    LOG_LEV_ERROR = 3,
    LOG_LEV_WARNING = 4,
    LOG_LEV_NOTICE = 5,
    LOG_LEV_INFO = 6,
    LOG_LEV_DEBUG = 7
} LogLevel;

#ifdef LOG_ENABLED
#define _LOG_ENABLED 1
#else
#define _LOG_ENABLED 0
#endif

#define Log_debug(x, ...) \
    if(_LOG_ENABLED) Log_msg(LOG_LEV_DEBUG, x, ##__VA_ARGS__)
#define Log_info(x, ...) \
    if(_LOG_ENABLED) Log_msg(LOG_LEV_INFO, x, ##__VA_ARGS__)
#define Log_warn(x, ...) \
    if(_LOG_ENABLED) Log_msg(LOG_LEV_WARNING, x, ##__VA_ARGS__)
#define Log_error(x, ...) \
    if(_LOG_ENABLED) Log_msg(LOG_LEV_ERROR, x, ##__VA_ARGS__)

void Log_msg(LogLevel level, const char *msg, ...);

#endif /* _UTIL_LOG_H_ */
