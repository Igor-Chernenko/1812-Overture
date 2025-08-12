#pragma once

#include "point.hpp"
#include "ball.hpp"
#include <SFML/Graphics.hpp>
#include <memory>

class WindowApp{
    public:
    WindowApp();
    
    void run();

    private:
        void processEvents();
        void update(sf::Time deltaTime);
        void render();

        const int CANVAS_WIDTH = 800;
        const int CANVAS_HEIGHT = 700;
        const float PI = 3.14159265358979323846f;

        sf::RectangleShape cannon;
        Point cannon_center;
        const int CANNON_WIDTH = 200;
        const int CANNON_HEIGHT = 50;
        const float CANNON_OFFSET = -50;

        sf::Clock shoot_clock;

        sf::RenderWindow window;
        sf::Image canvas;
        sf::Texture texture;
        sf::Sprite sprite;

        std::vector<std::unique_ptr<Ball>> balls;

};