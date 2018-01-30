#ifndef LOG_H
#define LOG_H

#include <stdbool.h>
#include <stdio.h>

enum log_option{
  LO_COLOR,
  LO_TIME,
  LO_FILE,
};

enum log_level{
  LL_ALL,
  LL_TRACE,
  LL_DEBUG,
  LL_INFO,
  LL_WARN,
  LL_ERROR,
  LL_FATAL,
  LL_OFF
};

void log_initialize();
void log_clean_up();

void log_set_option(enum log_option, bool);
bool log_set_color_support(bool);

bool log_set_level(enum log_level);
enum log_level log_get_level();

bool log_set_output(const char *);
FILE * log_get_output();

bool log_print_out(enum log_level,
		   FILE*,
		   char * file_name,
		   int line_no,
		   const char * fmt, ...);

#define log_print(ll, format, ...) log_print_out(ll,			\
						 log_get_output(),	\
						 __FILE__,		\
						 __LINE__,		\
						 format,		\
						 __VA_ARGS__);


#endif
