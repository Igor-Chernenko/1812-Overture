#pragma once
#include <SFML/Graphics.hpp>

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
        const double PI = 3.14159265358979323846;

        sf::RenderWindow window;
        sf::Image canvas;
        sf::Texture texture;
        sf::Sprite sprite;
        sf::RectangleShape cannon;

};