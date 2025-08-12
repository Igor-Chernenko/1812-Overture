#include "window.hpp"
#include "point.hpp"

#include <iostream>
#include <cmath>
#include <SFML/Graphics.hpp>

WindowApp::WindowApp(){

    window.create(sf::VideoMode(CANVAS_WIDTH, CANVAS_HEIGHT), "1812-Overture");
    canvas.create(CANVAS_WIDTH, CANVAS_HEIGHT, sf::Color::White);
    texture.loadFromImage(canvas);
    sprite.setTexture(texture);

     // create cannon with width=200, height=50
    cannon.setSize(sf::Vector2f(CANNON_WIDTH, CANNON_HEIGHT));
    cannon.setFillColor(sf::Color(128, 128, 128));
    cannon.setOrigin(0.0f, cannon.getSize().y / 2.0f);
    cannon.setPosition(CANNON_OFFSET, CANVAS_HEIGHT/2.f);
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
            if(event.key.code == sf::Keyboard::Space){
                if(shoot_clock.getElapsedTime().asSeconds() >= 0.5f){
                    const int ADJUSTMENT_VAL =5;
                    //create new ball and place at the tip of cannon
                    std::unique_ptr<Ball> new_ball = std::make_unique<Ball>(cannon_center.angle);
                    float initial_ball_y = (CANVAS_HEIGHT/2.f +(CANNON_WIDTH)*sin(cannon_center.angle));
                    float initial_ball_x = (CANNON_OFFSET+(CANNON_WIDTH)*cos(cannon_center.angle))-ADJUSTMENT_VAL;
                    Point initial_ball_position = {initial_ball_x,initial_ball_y};
                    new_ball->set_ball_position(initial_ball_position);
                    balls.push_back(std::move(new_ball));

                    shoot_clock.restart();
                }
            }
        }
    }
}

void WindowApp::update(sf::Time deltaTime) {
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    //update cannon
    float delta_y = mousePos.y - CANVAS_HEIGHT / 2.f;
    float delta_x = mousePos.x;
    float angle = std::atan2(delta_y, delta_x) * 180.f / PI;
    cannon.setRotation(angle);
    cannon_center = {-50.0f, CANVAS_HEIGHT/2.0f, angle*PI/180};

    //update ball
    for(auto& ball_ptr: balls){
        ball_ptr->update_ball(deltaTime);
    }
}

void WindowApp::render() {
    window.clear();
    window.draw(sprite);

    //render ball
    for (auto& ball_ptr : balls) {
        window.draw(ball_ptr->get_shape());
    }
    //render cannon
    window.draw(cannon);

    window.display();
}