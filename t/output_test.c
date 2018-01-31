#include "log.h"

int main(){
  log_initialize();
  log_set_level(LL_ALL);
  log_set_color_support(true);
  log_print(LL_ALL, "%s\n", "all");
  log_print(LL_TRACE, "%s\n", "trace");
  log_print(LL_DEBUG, "%s\n", "debug");
  log_print(LL_INFO, "%s\n", "info");
  log_print(LL_WARN, "%s\n", "warn");
  log_print(LL_ERROR, "%s\n", "error");
  log_print(LL_FATAL, "%s\n", "fatal");
  log_print(LL_OFF, "%s\n", "off");
  log_clean_up();
  return 0;
}

