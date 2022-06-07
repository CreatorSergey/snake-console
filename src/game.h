#pragma once

#include <cstdint>
#include <conio.h>

#include "snake.h"
#include "matrix.h"
#include "board.h"
#include "fruit.h"
#include "console-utils.h"
#include "timer.h"

class Game {
public:
    Game() {}

    void Init() {
        fruit_1 = fruit(board_.GetRandomX(), board_.GetRandomY());
        matrix_ = utils::Matrix (board_.GetHeight(), board_.GetWidth());
        matrix_.Init();
        matrix_.MoveSnakePos(snake_1);
        matrix_.MoveFruitPos(fruit_1);
        matrix_.Draw(fruit_1, snake_1, score, timer.elapsedMilliseconds());
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
            matrix.Draw(fruit, out, score, timer.elapsedMilliseconds());
        }

        if(gameOver)
        {
            std::cout << "\n";
            std::cout << "Game Over!";
            run = false;
        }
    }

    void RunCommand() {
        switch (last_command_) {
            case 27:               // press ESC to exit
                run = false;
            break;

            case 'a': {
                snake temp = snake_1;
                if(temp.y == 1)
                    temp.y = board_.GetHeight() - 2;
                else
                    temp.y -= 1;
                work(temp, fruit_1, snake_1, matrix_, board_);
                break;
            }

            case 'd': {
                snake temp = snake_1;
                temp.y += 1;
                if(temp.y == board_.GetHeight() - 1)
                temp.y = 1;

                work(temp, fruit_1, snake_1, matrix_, board_);
                break;
            }

            case 'w': {
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

    void Run() {

        timer.Start();
        while (run) {
            utils::SetCursorVisible(false);

            auto speed = 300;
            if((score / 5) > 0)
                speed = speed / (score / 5);

            if(timer.elapsedMilliseconds() > speed)
            {
                if(last_command_ != 0)
                    RunCommand();

                timer.Start();
            }

            
            if (_kbhit())
                last_command_ = _getch();
        }
    }

private:
    bool gameOver = false;
    bool run = true;
    std::uint16_t score{0};
    utils::Matrix matrix_;
    game::Board board_{15, 30};
    snake snake_1{1, 1};
    fruit fruit_1{0,0};
    char last_command_{'d'};
    utils::Timer timer;
};