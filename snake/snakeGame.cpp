#include <iostream>
#include <cstdlib>
#include <ctime>
#include <io.h>
#include <fcntl.h>
#include <windows.h>
#include <conio.h>
#include "Field.h"
#include "Snake.h"
#include "Apple.h"

const int COMPLEXITY = 100;

void SnakeGame(bool& gameRunning);

void GameControls(Snake& snake, bool& gameRunning) {
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
        case 'x':
            return;
        case 'r':
            SnakeGame(gameRunning);
        }
    }
}

void ReturnAndExitAfterGameEnd(bool& gameRunning) {
    while (true) {
        if (_kbhit()) {
            switch (_getch()) {
            case 'x':
                return;
            case 'r':
                gameRunning = true;
                SnakeGame(gameRunning);
                return;
            }
        }
    }
}

void SnakeGame(bool& gameRunning) {
    Field field;
    Snake snake;
    Apple apple;

    while (true) {

        field.Generate();
        snake.Generate(field);
        apple.Generate(field);

        int score = 0;

        apple.UpdateState(field);
        while (gameRunning) {
            GameControls(snake, gameRunning);

            snake.UpdatePosition(apple, score, gameRunning, field);

            field.UpdateState();
            snake.UpdateState(field);
            apple.UpdateState(field);

            system("cls");
            if (gameRunning) {
                field.DrawMap();
                std::wcout << L"Score: " << score << std::endl;
            }
            Sleep(COMPLEXITY);
        }
        std::wcout << L"Press 'x' to exit, 'r' to restart: ";
        ReturnAndExitAfterGameEnd(gameRunning);
    }
}

int main() {
    _setmode(_fileno(stdout), _O_U16TEXT);
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    std::wcout << L"Snake controls: 'w', 'a', 's', 'd'" << std::endl;
    std::wcout << L"Press 'x' for exit, press 'r' for restart" << std::endl;
    std::wcout << L"Press any button to continue" << std::endl;

    bool gameRunning = true;

    _getch();
    SnakeGame(gameRunning);

    return 0;
}
