#include <iostream>
#include <SFML/Graphics.hpp>
#include "Field.h"
#include "Snake.h"
#include "Apple.h"

const int CELL_SIZE = 30;  // Размер ячейки поля
const int COMPLEXITY = 100;

void SnakeGame(bool& gameRunning) {
    sf::RenderWindow window(sf::VideoMode(FIELD_WIDTH * CELL_SIZE, FIELD_HEIGHT * CELL_SIZE), "Snake Game");
    window.setFramerateLimit(60);  // Ограничиваем количество кадров в секунду

    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {  // Замените "arial.ttf" на путь к вашему шрифту
        std::cerr << "Failed to load font." << std::endl;
        return;
    }

    sf::Text scoreText;
    scoreText.setFont(font);
    scoreText.setCharacterSize(20);
    scoreText.setPosition(10.0f, 10.0f);

    Field field;
    Snake snake;
    Apple apple;

    field.Generate();
    snake.Generate(field);
    apple.Generate(field);

    int score = 0;

    while (window.isOpen() && gameRunning) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            } else if (event.type == sf::Event::KeyPressed) {
                switch (event.key.code) {
                case sf::Keyboard::A:
                    if (snake.direction != RIGHT)
                        snake.direction = LEFT;
                    break;
                case sf::Keyboard::D:
                    if (snake.direction != LEFT)
                        snake.direction = RIGHT;
                    break;
                case sf::Keyboard::W:
                    if (snake.direction != DOWN)
                        snake.direction = UP;
                    break;
                case sf::Keyboard::S:
                    if (snake.direction != UP)
                        snake.direction = DOWN;
                    break;
                case sf::Keyboard::X:
                    gameRunning = false;
                    break;
                case sf::Keyboard::R:
                    SnakeGame(gameRunning);
                    break;
                }
            }
        }

        snake.UpdatePosition(apple, score, gameRunning, field);
        field.UpdateState();
        snake.UpdateState(field);
        apple.UpdateState(field);

        window.clear();

        // Отрисовка поля
        for (int y = 0; y < FIELD_HEIGHT; ++y) {
            for (int x = 0; x < FIELD_WIDTH; ++x) {
                sf::RectangleShape cell(sf::Vector2f(CELL_SIZE, CELL_SIZE));
                cell.setPosition(x * CELL_SIZE, y * CELL_SIZE);
                window.draw(cell);
            }
        }

        // Отрисовка змейки
        for (const auto& segment : snake.GetBody()) {
            sf::RectangleShape snakeSegment(sf::Vector2f(CELL_SIZE, CELL_SIZE));
            snakeSegment.setPosition(segment.first * CELL_SIZE, segment.second * CELL_SIZE);
            window.draw(snakeSegment);
        }

        // Отрисовка яблока
        sf::RectangleShape appleShape(sf::Vector2f(CELL_SIZE, CELL_SIZE));
        appleShape.setPosition(apple.GetX() * CELL_SIZE, apple.GetY() * CELL_SIZE);
        window.draw(appleShape);

        // Отрисовка счета
        scoreText.setString("Score: " + std::to_string(score));
        window.draw(scoreText);

        window.display();
        sf::sleep(sf::milliseconds(COMPLEXITY));
    }

    if (!gameRunning) {
        std::cout << "Press 'x' to exit, 'r' to restart: ";
        while (true) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::X)) {
                return;
            } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
                gameRunning = true;
                SnakeGame(gameRunning);
                return;
            }
        }
    }
}

int main() {
    SnakeGame(true);
    return 0;
}
