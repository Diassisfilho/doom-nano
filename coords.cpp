#include <stdint.h>
#include <math.h>
#include "coords.h"
#include "constants.h"

#define sq(val)   (val) * (val)

Coords coords(double x, double y) {
  return { x, y };
}

uint8_t coords_distance(Coords* a, Coords* b) {
  return sqrt(sq(a->x - b->x) + sq(a->y - b->y)) * DISTANCE_MULTIPLIER;
}
