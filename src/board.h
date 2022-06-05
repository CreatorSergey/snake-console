#pragma once
#include <cstdint>

#include "random.h"

namespace game {

/**
 * @brief Доска
 */
class Board {
public:
    constexpr static std::uint16_t kFrameSize {1};

    Board(std::uint16_t width, std::uint16_t height):
        width_(width), height_(height) {}
    
    Board(const Board&) = delete;
    Board(Board&&) = delete;
    Board& operator=(const Board&) = delete;
    Board& operator=(Board&&) = delete;

    std::uint16_t GetWidth() const { return width_; }
    std::uint16_t GetHeight() const { return height_; }

    std::uint16_t GetRandomX() {
        return random_.Get(kFrameSize, width_ - 1 - kFrameSize);
    }
    std::uint16_t GetRandomY() {
        return random_.Get(kFrameSize, height_ - 1 - kFrameSize);
    }

private:
    std::uint16_t width_ = 0;
    std::uint16_t height_ = 0;
    utils::Random<std::uint16_t> random_;
};

}  // namespace game
