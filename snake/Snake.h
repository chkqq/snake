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
};

#endif
        