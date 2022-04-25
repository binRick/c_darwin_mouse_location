#ifndef DARWIN_MOUSE_LOCATION_MODULE_C
#define DARWIN_MOUSE_LOCATION_MODULE_C

#include "../include/includes.h"
#include "../include/types.h"
#include "../src/darwin-mouse-location.c"

#define dml_r    require(darwin_mouse_location)
#define dml_m    module(darwin_mouse_location)

enum module_logger_mode {
  LOGGER_NONE,
  LOGGER_INFO,
  LOGGER_ERROR,
  LOGGER_DEBUG,
  LOGGER_TRACE,
};

// Module Type Interface
dml_m {
  define(darwin_mouse_location, CLIB_MODULE);

  enum module_logger_mode mode;

  struct CGPoint          point;
  CGEventRef              event;

  DarwinMouseLocation_t   *location;

  int                     x; int y;

  int                     (*get)();
};

int darwin_mouse_location_init(dml_m *exports);
void darwin_mouse_location_deinit(dml_m *exports);

// Default Module Exports
exports(darwin_mouse_location) {
  .mode   = LOGGER_NONE,
  .x      = -1,
  .y      = -1,
  .init   = darwin_mouse_location_init,
  .deinit = darwin_mouse_location_deinit,
};


void darwin_mouse_location_deinit(dml_m *exports) {
  clib_module_deinit(darwin_mouse_location);
}


static inline CGPoint __get_darwin_mouse_point() {
  return(CGEventGetLocation(dml_r->event));
}


static inline int __get_mouse_location() {
  if (dml_r->mode >= LOGGER_DEBUG) {
    fprintf(stderr, "getting mouse location......\n");
  }

  dml_r->point = __get_darwin_mouse_point();

  dml_r->location->x = dml_r->point.x;
  dml_r->location->y = dml_r->point.y;

  dml_r->x = dml_r->point.x;
  dml_r->y = dml_r->point.y;

  return(dml_r->x > -1 && dml_r->y > -1);
}


int darwin_mouse_location_init(dml_m *exports) {
  clib_module_init(darwin_mouse_location, exports);

  exports->mode = LOGGER_NONE;

  exports->x = -1;
  exports->y = -1;

  exports->get = __get_mouse_location;

  exports->location = malloc(sizeof(DarwinMouseLocation_t));
  assert(exports->location != NULL);
  exports->event = CGEventCreate(nil);
  assert(exports->event != NULL);

  return(0);
}

#define DarwinMouseLocation        dml_m
#define InitDarwinMouseLocation()    { dml_r }
#define FreeDarwinMouseLocation    clib_module_free


DarwinMouseLocation_t * get_darwin_mouse_location(){
  DarwinMouseLocation *dml = InitDarwinMouseLocation();

  assert(dml->get() == 1);
  assert(dml->x > -1 && dml->y > -1);
  DarwinMouseLocation_t *l = malloc(sizeof(DarwinMouseLocation_t));

  l->x = dml->x;
  l->y = dml->y;
  FreeDarwinMouseLocation(dml);
  return(l);
}

#endif
