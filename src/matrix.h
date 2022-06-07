#pragma once

#include <cstdint>
#include <vector>

#include "color.hpp"

#include "snake.h"
#include "string-utils.h"

namespace utils {

class Matrix {

    struct item {
        char value;
        std::uint8_t color;
    };

public:
    Matrix() = default;
    Matrix(std::size_t width, std::size_t height): width_(width), height_(height) 
    {}

   // Matrix(const Matrix&) = delete;
  //  Matrix(Matrix&&) = delete;
  //  Matrix& operator=(const Matrix&) = delete;
  //  Matrix& operator=(Matrix&&) = delete;

    void Init() {
        matrix.resize(height_);
        for (size_t i = 0; i < matrix.size(); ++i) {
            auto& line = matrix[i];
            line.resize(width_);
            for (size_t j = 0; j < line.size(); ++j) {
                auto& px = line[j];
                if(i == 0 || i == matrix.size() - 1 || j == 0 || j == line.size() - 1) {
                    px = { 0x23, 7 }; 
                }
                else
                    px = { 0x20, 0 }; // space
            }
        }
    }
    
    void DrawLine(std::uint16_t x1, std::uint16_t y1, std::uint16_t x2, std::uint16_t y2) {
        float increment = (float)width_ / (float)height_;
        float pos_y = y1;
        float pos_x = x1;

        bool minus_y = y2 < y1;
        bool minux_x = x2 < x1;

        if(minux_x)
            pos_x -= 1;

        if(minus_y)
            pos_y -= 1;

        float buffer_decrement_x = 0;

        while(
            (minus_y ? pos_y >= y2 : pos_y < y2) && 
            (minux_x ? pos_x >= x2 : pos_x < x2))
        {
            matrix[pos_y][pos_x] = { 0x2A,  4};

            if(minux_x)
            {
                buffer_decrement_x += increment;
                if(buffer_decrement_x > 1)
                {
                    pos_x -= 1;
                    buffer_decrement_x -= 1;
                }
            }
            else
                pos_x += increment;

            if(minus_y)
                pos_y--;
            else
                pos_y++;
        }
    }
        
    void ClearSnakePos(snake& item, std::size_t score) {
        for(size_t i = 0; i < item.tail.size(); i++) {
            auto point = item.tail[i];
            matrix[point.x][point.y] = { 0x20, 0 };
        }

        if(item.tail.size()) {
            auto temp1 = item.tail[0];
            item.tail[0] = {item.x, item.y};
            for(size_t i = 1; i < item.tail.size(); i++) {
                auto temp2 = item.tail[i];
                item.tail[i] = temp1;
                temp1 = temp2;
            }
        }

        if(item.tail.size() < score )
            item.tail.push_back({item.x, item.y});

        matrix[item.x][item.y] = { 0x20, 0 };
    }
        
    void MoveFruitPos(point& item) {
        matrix[item.x][item.y] = { 0x24, 2 };
    }

    void MoveSnakePos(snake& item) {
        for(auto& point: item.tail) {
            matrix[point.x][point.y] = { 0x40, 4 };
        }
        matrix[item.x][item.y] = { 0x2A, 12 };
    }

    void Draw(point& fruit, point& snake, size_t score, size_t seconds) {
        std::cout << "score: " << utils::addZero(score) << " $\n";
        std::cout << "spped: 1 step / " << utils::addZero(seconds) << " ms\n";
        std::cout << "fruit: x = " << utils::addZero(fruit.x) << "; y = " << utils::addZero(fruit.y) << "\n";
        std::cout << "snake: x = " << utils::addZero(snake.x) << "; y = " << utils::addZero(snake.y) << "\n";
        for(const auto& line: matrix) {
            for(const auto& px: line) {
                if(px.color == 4)
                    std::cout << dye::red(px.value);
                else if(px.color == 0)
                    std::cout << dye::black(px.value);
                else if(px.color == 7)
                    std::cout << dye::bright_white(px.value);
                else if(px.color == 2)
                    std::cout << dye::light_green(px.value);
                else if(px.color == 12)
                    std::cout << dye::light_red(px.value);
                else
                    std::cout << px.value;
            }
            std::cout << "\n";
        }
    }

private:
    std::vector<std::vector<item>> matrix;
    std::size_t width_ = 0;
    std::size_t height_ = 0;
};

}  // namespace utils