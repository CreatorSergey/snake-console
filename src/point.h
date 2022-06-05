#pragma once

#include <cstdint>

struct point {
   point(std::uint16_t x_, std::uint16_t y_): x(x_), y(y_) {}
   std::uint16_t x = 0;
   std::uint16_t y = 0;
};

bool check(point& left, point& right) {
   return left.x == right.x && left.y == right.y;
}
