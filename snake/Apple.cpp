#include <iostream>
#include "Apple.h"

const wchar_t APPLE_SYMBOL = L'◈';
const wchar_t FIELD_SYMBOL = L' ';


void Apple:: Generate(const Field& field) {
    do {
        x = std::rand() % (FIELD_WIDTH - 2) + 1;
        y = std::rand() % (FIELD_HEIGHT - 2) + 1;
    } while (field.layout[y][x] != FIELD_SYMBOL);
}

void Apple:: UpdateState(Field& field) {
    field.layout[y][x] = APPLE_SYMBOL;
}

