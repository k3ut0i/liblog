#include "log.h"

struct log_options{
  enum log_level level;
  FILE * output_stream;
  bool stream_cleanup;
};

static struct log_options clo;

static void initialize()
{
  clo.level = LL_FATAL;
  clo.output_stream = stderr;
}

static void clean_up()
{
  if(clo.stream_cleanup) fclose(clo.output_stream);
}

bool log_set_level(enum log_level l)
{
  clo.level = l;
  return true;
}

enum log_level log_get_level()
{
  return clo.level;
}

bool log_set_output(const char * file_name)
{
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
  return clo.output_stream;
}

bool log_print_out(enum log_level l,
		   FILE* fp,
		   char* file_name,
		   int line_no,
		   const char * fmt,
		   ...)
{
  
}
