#include "window.hpp"
#include "point.hpp"

#include <iostream>
#include <utility>
#include <cmath>
#include <SFML/Graphics.hpp>

WindowApp::WindowApp(){
    window.create(sf::VideoMode(CANVAS_WIDTH, CANVAS_HEIGHT), "1812-Overture");
    canvas.create(CANVAS_WIDTH, CANVAS_HEIGHT, sf::Color::White);
    texture.loadFromImage(canvas);
    sprite.setTexture(texture);

    //import and create fonts
    if (!font.loadFromFile("ArialMdm.ttf")) {
        throw std::runtime_error("Could not load font");
    }
    text.setFont(font);
    text.setCharacterSize(20);
    text.setFillColor(sf::Color::Black);


    // create cannon with width=200, height=50
    cannon.setSize(sf::Vector2f(CANNON_WIDTH, CANNON_HEIGHT));
    cannon.setFillColor(sf::Color(128, 128, 128));
    cannon.setOrigin(0.0f, cannon.getSize().y / 2.0f);
    cannon.setPosition(CANNON_OFFSET, CANVAS_HEIGHT/2.f);

    //create buttons
    Point button_location = {50, 650};
    restitution = Button(200,50,button_location);
    text.setString("Collision: Elastic");
    text.setPosition(button_location.x +15, button_location.y +10);

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

std::pair<int,int> WindowApp::get_canvas(){
    std::pair<int,int> canvas_sizes = {CANVAS_WIDTH,CANVAS_HEIGHT};
    return canvas_sizes;
}

void WindowApp::processEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        if (event.type == sf::Event::MouseButtonPressed){
            if(event.mouseButton.button == sf::Mouse::Left){
                if(restitution.is_clicked(mousePos)){
                    if(restitution.get_color() == sf::Color::Blue){
                        restitution.change_color(sf::Color::Green);
                        coefficient_of_restitution = 0;
                        text.setString("Collision: Inelastic");
                    }else{
                        restitution.change_color(sf::Color::Blue);
                        coefficient_of_restitution = 1; 
                        text.setString("Collision: Elastic");
                    }
                }
            }
        }
        if (event.type == sf::Event::Closed) {
            window.close();
        }
        if(event.type == sf::Event::KeyPressed){
            if(event.key.code == sf::Keyboard::Space){
                if(shoot_clock.getElapsedTime().asSeconds() >= 0.70f){
                    const int ADJUSTMENT_VAL =5;
                    //create new ball and place at the tip of cannon
                    std::unique_ptr<Ball> new_ball = std::make_unique<Ball>(cannon_center.angle);

                    new_ball->canvas_height = CANVAS_HEIGHT;
                    new_ball->canvas_width = CANVAS_WIDTH;

                    float initial_ball_y = (CANVAS_HEIGHT/2.f +(CANNON_WIDTH)*sin(cannon_center.angle));
                    float initial_ball_x = (CANNON_OFFSET+(CANNON_WIDTH)*cos(cannon_center.angle))-ADJUSTMENT_VAL;
                    
                    Point initial_ball_position = {initial_ball_x, initial_ball_y};
                    new_ball->get_shape().setOrigin(new_ball->get_shape().getRadius(), new_ball->get_shape().getRadius());
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
        ball_ptr->update_ball(deltaTime, balls, coefficient_of_restitution);
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

    //render buttons
    window.draw(restitution.get_shape());

    //render text
    window.draw(text);

    window.display();
}