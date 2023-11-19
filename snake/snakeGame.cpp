#include <iostream>
#include <vector>
#include <deque>
#include <cstdlib>
#include <ctime>
#include <cwchar>
#include <io.h>
#include <fcntl.h>
#include <windows.h>
#include <conio.h>
#include "Field.h"
#include "Snake.h"
#include "Apple.h"

const int COMPLEXITY = 100;

int main() {
    _setmode(_fileno(stdout), _O_U16TEXT);
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    Field field;
    Snake snake;
    Apple apple;

    field.Generate(field);
    snake.Generate(field);
    apple.Generate(field);

    int score = 0;

    apple.UpdateState(apple, field);
    while (true) {
        if (_kbhit()) {
            switch (_getch()) {
            case 'a':
                if (snake.direction != RIGHT)
                    snake.direction = LEFT;
                break;
            case 'd':
                if (snake.direction != LEFT)
                    snake.direction = RIGHT;
                break;
            case 'w':
                if (snake.direction != DOWN)
                    snake.direction = UP;
                break;
            case 's':
                if (snake.direction != UP)
                    snake.direction = DOWN;
                break;
            }
        }

        snake.UpdatePosition(snake, apple, score, field);

        if (snake.body.front().first == 0 || snake.body.front().first == FIELD_WIDTH - 1 ||
            snake.body.front().second == 0 || snake.body.front().second == FIELD_HEIGHT - 1) {
            break;
        }

        field.UpdateState(field);
        snake.UpdateState(snake, field);
        apple.UpdateState(apple, field);

        system("cls");
        field.DrawMap(field);
        std::wcout << L"Score: " << score << std::endl;
        Sleep(COMPLEXITY);
    }

    return 0;
}