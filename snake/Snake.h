#ifndef SNAKE_H
#define SNAKE_H
#include "Apple.h"
#include "Field.h"
#include <deque>
#include <utility>

enum Direction {
    STOP = 0,
    LEFT,
    RIGHT,
    UP,
    DOWN
};

class Snake {
public:
    void Generate(const Field& field);
    void UpdatePosition(Apple& apple, int& score, bool& gameRunning, const Field& field);
    void UpdateState(Field& field);

    std::deque<std::pair<int, int>> body;
    Direction direction;
private:
    void CheckCollision(const std::pair<int, int>& newHead, bool& gameRunning, const Field& field);
    void CheckAppleCollision(const std::pair<int, int>& newHead, Apple& apple, const Field& field, int& score, bool& gameRunning);
    void CheckWinCondition(int score, bool& gameRunning);
    void HandleGameOver(bool& gameRunning);
};

#endif
        