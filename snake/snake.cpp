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

const int fieldWidth = 40;
const int fieldHeight = 20;

const wchar_t snakeSymbol = L'█';
const wchar_t appleSymbol = L'◈';
const wchar_t fieldSymbol = L'░';
const wchar_t boundarySymbol = L'▓';

enum Direction {
    STOP = 0,
    LEFT,
    RIGHT,
    UP,
    DOWN
};

struct Snake {
    std::deque<std::pair<int, int>> body;
    Direction direction;
};

struct Apple {
    int x;
    int y;
};

struct Field {
    std::vector<std::vector<wchar_t>> layout;
};

Field generateField() {
    Field field;
    field.layout = std::vector<std::vector<wchar_t>>(fieldHeight, std::vector<wchar_t>(fieldWidth, fieldSymbol));

    for (int y = 0; y < fieldHeight; ++y) {
        field.layout[y][0] = boundarySymbol;
        field.layout[y][fieldWidth - 1] = boundarySymbol;
    }
    for (int x = 0; x < fieldWidth; ++x) {
        field.layout[0][x] = boundarySymbol;
        field.layout[fieldHeight - 1][x] = boundarySymbol;
    }

    return field;
}

Snake generateSnake(const Field& field) {
    Snake snake;
    snake.direction = STOP;
    snake.body.push_back({ fieldWidth / 2, fieldHeight / 2 });
    snake.body.push_back({ fieldWidth / 2 - 1, fieldHeight / 2 });

    return snake;
}

Apple generateApple(const Field& field) {
    Apple apple;
    do {
        apple.x = std::rand() % (fieldWidth - 2) + 1;
        apple.y = std::rand() % (fieldHeight - 2) + 1;
    } while (field.layout[apple.y][apple.x] != fieldSymbol);
    return apple;
}

void drawField(const Field& field) {
    for (int y = 0; y < fieldHeight; ++y) {
        for (int x = 0; x < fieldWidth; ++x) {
            std::wcout << field.layout[y][x];
        }
        std::wcout << std::endl;
    }
}

void updateSnakePosition(Snake& snake, Apple& apple, int& score, const Field& field) {
    if (snake.direction == STOP) {
        snake.direction = RIGHT;
    }

    std::pair<int, int> newHead = snake.body.front();
    switch (snake.direction) {
    case LEFT:
        newHead.first--;
        break;
    case RIGHT:
        newHead.first++;
        break;
    case UP:
        newHead.second--;
        break;
    case DOWN:
        newHead.second++;
        break;
    default:
        break;
    }

    if (newHead.first == 0 || newHead.first == fieldWidth - 1 ||
        newHead.second == 0 || newHead.second == fieldHeight - 1 ||
        field.layout[newHead.second][newHead.first] == snakeSymbol) {
        std::wcout << L"Game Over!" << std::endl;
        exit(0);
    }

    if (newHead.first == apple.x && newHead.second == apple.y) {
        Apple newApple = generateApple(field);
        apple = newApple;
        score++;
    }
    else {
        for (auto it = snake.body.begin(); it != snake.body.end(); ++it) {
            if (newHead.first == it->first && newHead.second == it->second) {
                std::wcout << L"Game Over!" << std::endl;
                exit(0);
            }
        }

        snake.body.pop_back();
    }

    if (score == (fieldWidth - 2) * (fieldHeight - 2)) {
        std::wcout << L"You Win!" << std::endl;
        exit(0);
    }

    snake.body.push_front(newHead);
}


int main() {
    _setmode(_fileno(stdout), _O_U16TEXT);
    std::srand(static_cast<unsigned>(std::time(nullptr)));


    Field field = generateField();
    Snake snake = generateSnake(field);
    Apple apple = generateApple(field);

    int score = 0;

    field.layout[apple.y][apple.x] = appleSymbol;

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

        updateSnakePosition(snake, apple, score, field);

        if (snake.body.front().first == 0 || snake.body.front().first == fieldWidth - 1 ||
            snake.body.front().second == 0 || snake.body.front().second == fieldHeight - 1) {
            break;
        }

        for (int y = 1; y < fieldHeight - 1; ++y) {
            for (int x = 1; x < fieldWidth - 1; ++x) {
                field.layout[y][x] = fieldSymbol;
            }
        }

        for (const auto& segment : snake.body) {
            field.layout[segment.second][segment.first] = snakeSymbol;
        }

        field.layout[apple.y][apple.x] = appleSymbol;
        system("cls");
        drawField(field);
        std::wcout << L"Score: " << score << std::endl;
        Sleep(100);
    }

    std::wcout << L"Game Over!" << std::endl;

    return 0;
}