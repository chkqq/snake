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

const int FIELD_WIDTH = 40;
const int FIELD_HEIGHT = 20;

const wchar_t SNAKE_SYMBOL = L'█';
const wchar_t APPLE_SYMBOL = L'◈';
const wchar_t FIELD_SYMBOL = L' ';
const wchar_t BOUNDARY_SYMBOL = L'▓';

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

Field GenerateField() {
    Field field;
    field.layout = std::vector<std::vector<wchar_t>>(FIELD_HEIGHT, std::vector<wchar_t>(FIELD_WIDTH, FIELD_SYMBOL));

    for (int y = 0; y < FIELD_HEIGHT; ++y) {
        field.layout[y][0] = BOUNDARY_SYMBOL;
        field.layout[y][FIELD_WIDTH - 1] = BOUNDARY_SYMBOL;
    }
    for (int x = 0; x < FIELD_WIDTH; ++x) {
        field.layout[0][x] = BOUNDARY_SYMBOL;
        field.layout[FIELD_HEIGHT - 1][x] = BOUNDARY_SYMBOL;
    }

    return field;
}

Snake GenerateSnake(const Field& field) {
    Snake snake;
    snake.direction = STOP;
    snake.body.push_back({ FIELD_WIDTH / 2, FIELD_HEIGHT / 2 });
    snake.body.push_back({ FIELD_WIDTH / 2 - 1, FIELD_HEIGHT / 2 });

    return snake;
}

Apple GenerateApple(const Field& field) {
    Apple apple;
    do {
        apple.x = std::rand() % (FIELD_WIDTH - 2) + 1;
        apple.y = std::rand() % (FIELD_HEIGHT - 2) + 1;
    } while (field.layout[apple.y][apple.x] != FIELD_SYMBOL);
    return apple;
}

void DrawField(const Field& field) {
    COORD position;
    position.X = 0;
    position.Y = 0;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);

    for (int y = 0; y < FIELD_HEIGHT; ++y) {
        for (int x = 0; x < FIELD_WIDTH; ++x) {
            std::wcout << field.layout[y][x];
        }
        std::wcout << std::endl;
    }
}
void UpdateSnakePosition(Snake& snake, Apple& apple, int& score, const Field& field) {
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

    if (newHead.first == 0 || newHead.first == FIELD_WIDTH - 1 ||
        newHead.second == 0 || newHead.second == FIELD_HEIGHT - 1 ||
        field.layout[newHead.second][newHead.first] == SNAKE_SYMBOL) {
        std::wcout << L"Game Over!" << std::endl;
        exit(0);
    }

    if (newHead.first == apple.x && newHead.second == apple.y) {
        Apple newApple = GenerateApple(field);
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

    if (score == (FIELD_WIDTH - 2) * (FIELD_HEIGHT - 2)) {
        std::wcout << L"You Win!" << std::endl;
        exit(0);
    }

    snake.body.push_front(newHead);
}


int main() {
    _setmode(_fileno(stdout), _O_U16TEXT);
    std::srand(static_cast<unsigned>(std::time(nullptr)));


    Field field = GenerateField();
    Snake snake = GenerateSnake(field);
    Apple apple = GenerateApple(field);

    int score = 0;

    field.layout[apple.y][apple.x] = APPLE_SYMBOL;

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

        UpdateSnakePosition(snake, apple, score, field);

        if (snake.body.front().first == 0 || snake.body.front().first == FIELD_WIDTH - 1 ||
            snake.body.front().second == 0 || snake.body.front().second == FIELD_HEIGHT - 1) {
            break;
        }

        for (int y = 1; y < FIELD_HEIGHT - 1; ++y) {
            for (int x = 1; x < FIELD_WIDTH - 1; ++x) {
                field.layout[y][x] = FIELD_SYMBOL;
            }
        }

        for (const auto& segment : snake.body) {
            field.layout[segment.second][segment.first] = SNAKE_SYMBOL;
        }

        field.layout[apple.y][apple.x] = APPLE_SYMBOL;
        system("cls");
        DrawField(field);
        std::wcout << L"Score: " << score << std::endl;
        Sleep(100);
    }

    std::wcout << L"Game Over!" << std::endl;

    return 0;
}