#include <iostream>
#include "Apple.h"

const wchar_t APPLE_SYMBOL = L'◈';
const wchar_t FIELD_SYMBOL = L' ';


Apple Apple:: Generate(const Field& field) {
    Apple apple;
    do {
        apple.x = std::rand() % (FIELD_WIDTH - 2) + 1;
        apple.y = std::rand() % (FIELD_HEIGHT - 2) + 1;
    } while (field.layout[apple.y][apple.x] != FIELD_SYMBOL);
    return apple;
}

void Apple:: UpdateState(Apple& apple, Field& field) {
    field.layout[apple.y][apple.x] = APPLE_SYMBOL;
}

