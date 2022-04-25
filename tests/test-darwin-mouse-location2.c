/*******************************************/
#include "../include/includes.h"
#include "../include/types.h"
#include "../src/darwin-mouse-location-module.c"
#include "../src/darwin-mouse-location.c"
/*******************************************/


/*******************************************/
int main(const int argc, const char **argv) {
    DarwinMouseLocation *dml = InitDarwinMouseLocation();
    assert(dml);
    assert(dml->x == -1 && dml->y == -1);

    assert(dml->get() == 1);
    assert(dml->x > -1 && dml->y > -1);
    fprintf(stdout,
            "x:%d | y:%d | mode: %d | \n",
            dml->x,
            dml->y,
            dml->mode
            );

    FreeDarwinMouseLocation(dml);
  return(0);
}
/*******************************************/
