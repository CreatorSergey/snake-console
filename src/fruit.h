#pragma once

#include <cstdint>
#include "point.h"

struct fruit: public point {
   fruit(std::uint16_t x, std::uint16_t y): point(x, y) {}
};
