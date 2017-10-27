#include <stdarg.h>
#include <stdio.h> // TODO: Replace it with <util/print.h> (when it is ready)

#include <util/log.h>

#ifdef LOG_PRINT_LEVEL
static const char *_LEV_NAMES[] = {
   [LOG_LEV_EMERGENCY] = LOG_EMERGENCY,
   [LOG_LEV_ALERT] = LOG_ALERT,
   [LOG_LEV_CRITICAL] = LOG_CRITICAL,
   [LOG_LEV_ERROR] = LOG_ERROR,
   [LOG_LEV_WARNING] = LOG_WARNING,
   [LOG_LEV_NOTICE] = LOG_NOTICE,
   [LOG_LEV_INFO] = LOG_INFO,
   [LOG_LEV_DEBUG] = LOG_DEBUG
};
#endif

static LogLevel _level = LOG_LEV_DEBUG;

void Log_msg(LogLevel level, const char *msg, ...)
{
    if(_level >= level) {
        va_list ap;
        va_start(ap, msg);
#ifdef LOG_PRINT_LEVEL
        printf("%s: ", _LEV_NAMES[level]);
#endif
        vprintf(msg, ap);
        va_end(ap);
    }
}
