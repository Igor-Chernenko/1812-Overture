#include "window.hpp"
#include <iostream>
#include <cmath>
#include <SFML/Graphics.hpp>

WindowApp::WindowApp(){

    window.create(sf::VideoMode(CANVAS_WIDTH, CANVAS_HEIGHT), "1812-Overture");
    canvas.create(CANVAS_WIDTH, CANVAS_HEIGHT, sf::Color::White);
    texture.loadFromImage(canvas);
    sprite.setTexture(texture);

     // create cannon with width=100, height=50
    cannon.setSize(sf::Vector2f(200, 50));
    cannon.setFillColor(sf::Color(128, 128, 128));
    cannon.setPosition(-50.0f, CANVAS_HEIGHT/2.f);
};

void WindowApp::run(){
    sf::Clock clock;
    while (window.isOpen())
        {
            sf::Time deltaTime = clock.restart();
            processEvents();
            update(deltaTime);
            render();
        }
}

void WindowApp::processEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
        if(event.type == sf::Event::KeyPressed){
            //if key == space shoot:
        }
    }
}

void WindowApp::update(sf::Time deltaTime) {
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    float delta_y = mousePos.y - CANVAS_HEIGHT / 2.f;
    float delta_x = mousePos.x;
    float angle = std::atan2(delta_y, delta_x) * 180.f / PI;
    cannon.setRotation(angle);
}

void WindowApp::render() {
    window.clear();
    window.draw(sprite);
    window.draw(cannon);
    window.display();
}