#include <iostream>
#include <conio.h>
#include <Windows.h>
#include "Snake.h"
#include "Field.h"
#include "Apple.h"

const wchar_t SNAKE_SYMBOL = L'█';

void Snake:: UpdatePosition(Apple& apple, int& score, bool& gameRunning, const Field& field) {
    if (direction == STOP) {
        direction = RIGHT;
    }

    std::pair<int, int> newHead = body.front();
    switch (direction) {
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

    CheckCollision(newHead, gameRunning, field);
    CheckAppleCollision(newHead, apple, field, score, gameRunning);
    CheckWinCondition(score, gameRunning);

    body.push_front(newHead);

    HandleGameOver(gameRunning);
}

void Snake:: CheckCollision(const std::pair<int, int>& newHead, bool& gameRunning, const Field& field) {
    if (newHead.first == 0 || newHead.first == FIELD_WIDTH - 1 ||
        newHead.second == 0 || newHead.second == FIELD_HEIGHT - 1 ||
        field.layout[newHead.second][newHead.first] == SNAKE_SYMBOL) {
        std::wcout << L"Game Over!" << std::endl;
        gameRunning = false;
    }

}

void Snake::CheckAppleCollision(const std::pair<int, int>& newHead, Apple& apple, const Field& field, int& score, bool& gameRunning) {
    if (newHead.first == apple.x && newHead.second == apple.y) {
        apple.Generate(field);
        score++;
    }
    else {
        for (auto it = body.begin(); it != body.end(); ++it) {
            if (newHead.first == it->first && newHead.second == it->second) {
                gameRunning = false;
            }
        }

        body.pop_back();
    }
}

void Snake:: CheckWinCondition(int score, bool& gameRunning) {
    if (score == (FIELD_WIDTH - 2) * (FIELD_HEIGHT - 2)) {
        std::wcout << L"You Win!" << std::endl;
        gameRunning = false;
    }

}

void Snake::  HandleGameOver(bool& gameRunning) {
    if (!gameRunning) {
        std::wcout << L"Press any button to continue" << std::endl;
        Sleep(1000);
        _getch();
    }
}

 
void Snake:: UpdateState(Field& field) {
    for (const auto& segment : body) {
        field.layout[segment.second][segment.first] = SNAKE_SYMBOL;
    }
}

void Snake:: Generate(const Field& field) {
    direction = STOP;
    body.push_back({ FIELD_WIDTH / 2, FIELD_HEIGHT / 2 });
    body.push_back({ FIELD_WIDTH / 2 - 1, FIELD_HEIGHT / 2 });

}