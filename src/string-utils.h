#pragma once

#include <string>

namespace utils {

/**
 * @brief Добавить ноль к числу, если его значение меньше 9
 * @tparam T - тип
 * @param value - значение
 * @return std::string - число в виде строки 
 */
template <typename T>
std::string addZero(T value) {
   if(value < 10)
      return "0" + std::to_string(value);
   return std::to_string(value);
}

}  // namespace utils