#include "../src/get-darwin-mouse-location.c"


int main(const int argc, const char **argv) {
  DarwinMouseLocation_t *dml = get_darwin_mouse_location();

  fprintf(stdout,
          "x:%d | y:%d |\n",
          dml->x,
          dml->y
          );

  free(dml);
  return(0);
}
