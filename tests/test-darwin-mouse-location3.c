#include "../src/get-darwin-mouse-location.c"
#include <stdbool.h>
#define SLEEP_MS_DURATION 10

DarwinMouseLocation_t *dml;
bool running = true;
unsigned int cur_x, cur_y, updates_qty;

int main(const int argc, const char **argv) {
  while(running){
    dml = get_darwin_mouse_location();
    if(cur_x != dml->x || cur_y != dml->y){
      fprintf(stdout,
          "#%d> x:%d | y:%d |\n"
          , updates_qty++
          , dml->x
          , dml->y
          );
      cur_x = dml->x;
      cur_y = dml->y;
    }
    usleep(SLEEP_MS_DURATION * 1000);
  }

  free(dml);
  return(0);
}
