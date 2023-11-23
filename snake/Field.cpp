#include <iostream>
#include <windows.h>
#include "Field.h"

const wchar_t FIELD_SYMBOL = L' ';
const wchar_t BOUNDARY_SYMBOL = L'▓';

void Field::Generate() {
    layout = std::vector<std::vector<wchar_t>>(FIELD_HEIGHT, std::vector<wchar_t>(FIELD_WIDTH, FIELD_SYMBOL));

    std::fill(layout.front().begin(), layout.front().end(), BOUNDARY_SYMBOL);
    std::fill(layout.back().begin(), layout.back().end(), BOUNDARY_SYMBOL);

    for (auto& row : layout) {
        row.front() = BOUNDARY_SYMBOL;
        row.back() = BOUNDARY_SYMBOL;
    }
}

void Field::UpdateState() {
    for (int y = 1; y < FIELD_HEIGHT - 1; ++y) {
        for (int x = 1; x < FIELD_WIDTH - 1; ++x) {
             layout[y][x] = FIELD_SYMBOL;
        }
    }
}

void Field:: DrawMap () {
    COORD position;
    position.X = 0;
    position.Y = 0;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);

    for (int y = 0; y < FIELD_HEIGHT; ++y) {
        for (int x = 0; x < FIELD_WIDTH; ++x) {
            std::wcout << layout[y][x];
        }
        std::wcout << std::endl;
    }
}