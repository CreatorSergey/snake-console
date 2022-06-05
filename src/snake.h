#pragma once

#include <cstdint>
#include <vector>

#include "point.h"

struct snake: public point {
   snake(std::uint16_t x, std::uint16_t y): point(x, y) {}

   std::vector<point> tail;
};