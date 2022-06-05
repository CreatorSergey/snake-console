#pragma once
#include <random>

namespace utils {

/**
 * @brief Обертка над генератором случаныйх чисел
 */
template <typename T>
class Random final {
public:
    Random() {
        std::random_device device;
        random_generator_.seed(device());
    }

    Random(const Random&) = delete;
    Random(Random&&) = delete;
    Random& operator=(const Random&) = delete;
    Random& operator=(Random&&) = delete;

    /**
     * @brief Получить значение из диапазона
     * @param min - минимальное
     * @param max - максимальное
     * @return T - cлучайное значение
     */
    T Get(T min, T max) {
        std::uniform_int_distribution<T> range(min, max);
        return range(random_generator_);
    }

private:
    std::mt19937 random_generator_;
};

}  // namespace utils