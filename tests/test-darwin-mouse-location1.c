/*******************************************/
//#define MODULE_LOG_LEVEL LOGGER_TRACE
#define MODULE_LOG_LEVEL    LOGGER_ERROR
#define GET_QTY             50
/*******************************************/
#include "../include/includes.h"
#include "../include/types.h"
#include "../src/darwin-mouse-location-module.c"
#include "../src/darwin-mouse-location.c"
/*******************************************/


/*******************************************/
int main(const int argc, const char **argv) {
  for (int i = 0; i < GET_QTY; i++) {
    DarwinMouseLocation *dml = InitDarwinMouseLocation();
    assert(dml);
    assert(dml->x == -1 && dml->y == -1);

    dml->mode = MODULE_LOG_LEVEL;
    assert(dml->mode == MODULE_LOG_LEVEL);

    assert(dml->get() == 1);
    assert(dml->x > -1 && dml->y > -1);
    fprintf(stdout,
            "x:%d | y:%d | mode: %d | \n",
            dml->x,
            dml->y,
            dml->mode
            );
    fflush(stdout);
    usleep(100 * 1000);

    FreeDarwinMouseLocation(dml);
  }
  return(0);
}
/*******************************************/
