#pragma once
#include "button.hpp"
#include "point.hpp"
#include "ball.hpp"
#include <utility>
#include <SFML/Graphics.hpp>
#include <memory>

class WindowApp{
    public:
    WindowApp();
    void run();

    std::pair<int,int> get_canvas();


    private:
        void processEvents();
        void update(sf::Time deltaTime);
        void render();

        const int CANVAS_WIDTH = 800;
        const int CANVAS_HEIGHT = 700;
        const float PI = 3.14159265358979323846f;
        int coefficient_of_restitution = 1;

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
        sf::Font font;
        sf::Text text;


        std::vector<std::unique_ptr<Ball>> balls;
        Button restitution;  //1 for elastic, 0 for inelastic
};