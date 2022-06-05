#pragma once

#include <cstdint>
#include <conio.h>

#include "snake.h"
#include "matrix.h"
#include "board.h"
#include "fruit.h"
#include "console-utils.h"

class Game {
public:
    Game() {}

    void Init() {
        fruit_1 = fruit(board_.GetRandomX(), board_.GetRandomY());
        matrix_ = utils::Matrix (board_.GetWidth(), board_.GetHeight());
        matrix_.Init();
        matrix_.MoveSnakePos(snake_1);
        matrix_.MoveFruitPos(fruit_1);
        matrix_.Draw(fruit_1, snake_1, score);
    }
    
    void score_calc(snake& snake_, point& fruit_, utils::Matrix& matrix, game::Board& board) {
        if(check(snake_, fruit_)) {
            bool found = true;
            while(found) {
                found = false;
                fruit_ = fruit(board.GetRandomX(), board.GetRandomY());

                for(size_t i = 0; i < snake_.tail.size(); i++) {
                    if(check(fruit_, snake_.tail[i])) {
                        found = true;
                        break;
                    }
                }
            }

            matrix.MoveFruitPos(fruit_);
        }
    }
        
    void work(snake& temp, point& fruit, snake& out, utils::Matrix& matrix, game::Board& board) {
        for(size_t i = 0; i < temp.tail.size(); i++)
        {
            if(check(temp, temp.tail[i]))
            {
                gameOver = true;
                break;
            }
        }
        
        {
            if(check(temp, fruit))
                score++;

            utils::ClearScreen();
            matrix.ClearSnakePos(out, score);
            out.x = temp.x;
            out.y = temp.y;
            matrix.MoveSnakePos(out);
            score_calc(out, fruit, matrix, board);
            matrix.Draw(fruit, out, score);
        }

        if(gameOver)
        {
            std::cout << "\n";
            std::cout << "Game Over!";
            run = false;
        }
    }

    void Run() {
        while (run) {
            utils::SetCursorVisible(false);
            
            if (_kbhit())
            {
                char ch = _getch();
                switch (ch)
                {
                    case 27:               // press ESC to exit
                        run = false;
                    break;

                    case 'a':
                    {
                        snake temp = snake_1;
                        if(temp.y == 1)
                            temp.y = board_.GetHeight() - 2;
                        else
                            temp.y -= 1;
                        work(temp, fruit_1, snake_1, matrix_, board_);
                        break;
                    }

                    case 'd':
                    {
                        snake temp = snake_1;
                        temp.y += 1;
                        if(temp.y == board_.GetHeight() - 1)
                        temp.y = 1;

                        work(temp, fruit_1, snake_1, matrix_, board_);
                        break;
                    }

                    case 'w':
                    {
                        snake temp = snake_1;
                        if(temp.x == 1)
                        temp.x = board_.GetWidth() - 2;
                        else
                            temp.x -= 1;
                        work(temp, fruit_1, snake_1, matrix_, board_);
                        break;
                    }

                    case 's':
                    {
                        snake temp = snake_1;
                        temp.x += 1;
                        if(temp.x == board_.GetWidth() - 1)
                            temp.x = 1;
                        work(temp, fruit_1, snake_1, matrix_, board_);
                        break;
                    }
                }
            }
        }
    }

private:
    bool gameOver = false;
    bool run = true;
    std::uint16_t score{0};
    utils::Matrix matrix_;
    game::Board board_{20, 20};
    snake snake_1{1, 1};
    fruit fruit_1{0,0};
};