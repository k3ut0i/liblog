#include "log.h"
#include <stdlib.h>
#include <stdarg.h>

struct log_options{
  enum log_level level;
  FILE * output_stream;
  bool stream_cleanup;
};

static struct log_options clo;
static bool lib_status = false;

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
}

void log_clean_up()
{
  assert_ls();
  if(clo.stream_cleanup) fclose(clo.output_stream);
  lib_status = false;
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
  if(l >= log_get_level()){
    va_list ap;
    va_start(ap, fmt);
    fprintf(fp, "%s:[%d] ", file_name, line_no);
    vfprintf(fp, fmt, ap);
    va_end(ap);
    return true;
  }else{
    return false;
  }
}
