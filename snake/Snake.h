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
    void UpdatePosition(Snake& snake, Apple& apple, int& score, const Field& field);
    void UpdateState(Snake& snake, Field& field);
    Snake Generate(const Field& field);

    std::deque<std::pair<int, int>> body;
    Direction direction;
};

#endif
        