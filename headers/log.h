/**
 * A logger with 3 logging levels.
 * 
 * @author https://stackoverflow.com/a/23446001
 **/
#include <stdarg.h>

#ifndef LOG_H 
#define LOG_H


void log_error(const char* message, ...);
void log_info(const char* message, ...);
void log_debug(const char* message, ...);

#endif