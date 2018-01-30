#include "log.h"
#include <stdlib.h>
#include <stdarg.h>

struct color{
  const char * prefix;
  const char * postfix;
};

struct log_param{
  enum log_level level;
  FILE * output_stream;
  bool stream_cleanup;
  bool color;
  bool file_info;
  bool time_info;
};

static struct log_param clo;
static bool lib_status = false;
static const struct color term_color[] = {
  {"\e[90m", "\e[0m"}, //ALL - Dark gray
  {"\e[37m", "\e[0m"}, //TRACE - light gray
  {"\e[94m", "\e[0m"}, //DEBUG - light blue
  {"\e[92m", "\e[0m"}, //INFO - light green
  {"\e[35m", "\e[0m"}, //WARN - magneta
  {"\e[91m\e[1m", "\e[0m"}, //ERROR - light red
  {"\e[91m\e[4m", "\e[0m"}, //FATAL - underlined light red
  {"\e[8m", "\e[0m"}, //OFF - Hidden, should not trigger
};
inline static void assert_ls()
{
  if (!lib_status){
    fprintf(stderr, "Log library not initialized\n");
    exit(0);
  }
}

void log_initialize()
{
  lib_status = true;
  clo.level = LL_FATAL;
  clo.output_stream = stderr;
  clo.color = false;
}

void log_clean_up()
{
  assert_ls();
  if(clo.stream_cleanup) fclose(clo.output_stream);
  lib_status = false;
}

bool log_set_color_support(bool s)
{
  clo.color = s;
  /* If there is a good way to check if the terminal supports colors,
then the return value should indicate such a possibility. */
  return true;
}

bool log_set_level(enum log_level l)
{
  assert_ls();
  clo.level = l;
  return true;
}

enum log_level log_get_level()
{
  assert_ls();
  return clo.level;
}

bool log_set_output(const char * file_name)
{
  assert_ls();
  clo.output_stream = fopen(file_name, "a");
  if(clo.output_stream == NULL){
    fprintf(stderr, "Error opening log file");
    return false;
  }else{
    clo.stream_cleanup = true;
    return true;
  }
}

FILE* log_get_output()
{
  assert_ls();
  return clo.output_stream;
}

bool log_print_out(enum log_level l,
		   FILE* fp,
		   char* file_name,
		   int line_no,
		   const char * fmt,
		   ...)
{
  assert_ls();
  if(l >= log_get_level() && l < LL_OFF){
    va_list ap;
    va_start(ap, fmt);
    fprintf(fp, "%s:%4d ", file_name, line_no);
    if(clo.color) fprintf(fp, "%s", term_color[l].prefix);
    vfprintf(fp, fmt, ap);
    if(clo.color) fprintf(fp, "%s", term_color[l].postfix);
    va_end(ap);
    return true;
  }else{
    return false;
  }
}
