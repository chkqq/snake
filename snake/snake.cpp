#include <SFML/Graphics.hpp>
#include "Snake.h"
#include "Field.h"
#include "Apple.h"

const wchar_t SNAKE_SYMBOL = L'█';
const int CELL_SIZE = 30;  // Размер ячейки поля

void Snake::UpdatePosition(Apple& apple, int& score, bool& gameRunning, const Field& field, sf::RenderWindow& window) {
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

    if (newHead.first == 0 || newHead.first == FIELD_WIDTH - 1 ||
        newHead.second == 0 || newHead.second == FIELD_HEIGHT - 1 ||
        field.layout[newHead.second][newHead.first] == SNAKE_SYMBOL) {
        std::wcout << L"Game Over!" << std::endl;
        gameRunning = false;
    }

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

    if (score == (FIELD_WIDTH - 2) * (FIELD_HEIGHT - 2)) {
        std::wcout << L"You Win!" << std::endl;
        gameRunning = false;
    }
    body.push_front(newHead);

    if (!gameRunning) {
        sf::Text gameOverText;
        sf::Font font;
        if (!font.loadFromFile("arial.ttf")) {  // Замените "arial.ttf" на путь к вашему шрифту
            std::cerr << "Failed to load font." << std::endl;
            return;
        }

        gameOverText.setFont(font);
        gameOverText.setCharacterSize(30);
        gameOverText.setFillColor(sf::Color::White);
        gameOverText.setString("Game Over! Press any button to continue");
        gameOverText.setPosition(50.0f, 200.0f);

        window.draw(gameOverText);
        window.display();

        Sleep(1000);
        _getch();
    }
}

void Snake::UpdateState(Field& field) {
    for (const auto& segment : body) {
        sf::RectangleShape snakeSegment(sf::Vector2f(CELL_SIZE, CELL_SIZE));
        snakeSegment.setPosition(segment.first * CELL_SIZE, segment.second * CELL_SIZE);
        field.window.draw(snakeSegment);
    }
}

void Snake::Generate(const Field& field) {
    direction = STOP;
    body.push_back({ FIELD_WIDTH / 2, FIELD_HEIGHT / 2 });
    body.push_back({ FIELD_WIDTH / 2 - 1, FIELD_HEIGHT / 2 });
}
