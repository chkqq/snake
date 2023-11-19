#include <iostream>
#include "Snake.h"
#include "Field.h"
#include "Apple.h"

const wchar_t SNAKE_SYMBOL = L'█';

void Snake:: UpdatePosition(Snake& snake, Apple& apple, int& score, const Field& field) {
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
        apple.Generate(apple, field);
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

void Snake:: UpdateState(Snake& snake, Field& field) {
    for (const auto& segment : snake.body) {
        field.layout[segment.second][segment.first] = SNAKE_SYMBOL;
    }
}

void Snake:: Generate(Snake& snake, const Field& field) {
    snake.direction = STOP;
    snake.body.push_back({ FIELD_WIDTH / 2, FIELD_HEIGHT / 2 });
    snake.body.push_back({ FIELD_WIDTH / 2 - 1, FIELD_HEIGHT / 2 });

}