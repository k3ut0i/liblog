#include "log.h"

int main(){
  log_initialize();
  log_set_level(LL_DEBUG);
  log_print(LL_FATAL, "%s", "hey");
  log_clean_up();
  return 0;
}

