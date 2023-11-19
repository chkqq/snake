#include <iostream>
#include "Apple.h"

const wchar_t APPLE_SYMBOL = L'◈';
const wchar_t FIELD_SYMBOL = L' ';


void Apple:: Generate(Apple& apple, const Field& field) {
    do {
        apple.x = std::rand() % (FIELD_WIDTH - 2) + 1;
        apple.y = std::rand() % (FIELD_HEIGHT - 2) + 1;
    } while (field.layout[apple.y][apple.x] != FIELD_SYMBOL);
}

void Apple:: UpdateState(Apple& apple, Field& field) {
    field.layout[apple.y][apple.x] = APPLE_SYMBOL;
}

