#include <SFML/Graphics.hpp>
#include <random>
#include <cmath>
#include <iostream>
#include "ball.hpp"

Ball::Ball(float init_angle){
    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_int_distribution<> color_dist(0,255);
    std::uniform_int_distribution<> size_dist(5,20);

    sf::CircleShape new_circle;
    new_circle.setFillColor(sf::Color(color_dist(gen), color_dist(gen), color_dist(gen)));
    new_circle.setRadius(size_dist(gen));

    this->ball_shape = new_circle;

    float init_vel_x = INITIAL_SPEED*cos(init_angle);
    float init_vel_y = INITIAL_SPEED*sin(init_angle);
    
    this->velocity = {init_vel_x, init_vel_y};
}

void Ball::set_ball_position(Point ball_position){
    this->position = ball_position;
    this->ball_shape.setPosition(ball_position.x, ball_position.y);
}

sf::CircleShape& Ball::get_shape(){
    return this->ball_shape;
}

void Ball::update_ball(sf::Time delta_t){

    float fin_vel_x = velocity.first + acceleration.first *delta_t.asSeconds();
    float fin_vel_y = velocity.second - acceleration.second* delta_t.asSeconds();
    if(fin_vel_x<0){
        fin_vel_x=0;
    }
    float fin_pos_x = 1.f/2.f * (velocity.first + fin_vel_x)*delta_t.asSeconds() + position.x;
    float fin_pos_y = 1.f/2.f * (velocity.second+ fin_vel_y)*delta_t.asSeconds() + position.y;
    
    sf::CircleShape ball = this->ball_shape;



    this->velocity = {fin_vel_x, fin_vel_y};
    this->position = {fin_pos_x, fin_pos_y};

    ball_shape.setPosition(fin_pos_x, fin_pos_y);
}

