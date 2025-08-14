#include <SFML/Graphics.hpp>
#include <random>
#include <cmath>
#include <iostream>
#include <utility>
#include <memory>
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
    this->radius = ball_shape.getRadius();
    this->mass = BALL_MASS_CONSTANT* radius;
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

void Ball::update_ball(sf::Time delta_t ,std::vector<std::unique_ptr<Ball>>& balls, int coefficient_of_restitution){

    float fin_vel_x = velocity.first + acceleration.first *delta_t.asSeconds();
    float fin_vel_y = velocity.second - acceleration.second* delta_t.asSeconds();

    float fin_pos_x = 1.f/2.f * (velocity.first + fin_vel_x)*delta_t.asSeconds() + position.x;
    float fin_pos_y = 1.f/2.f * (velocity.second+ fin_vel_y)*delta_t.asSeconds() + position.y;
 
    sf::CircleShape ball = this->ball_shape;
    float r = ball.getRadius();
    //check if ball is hitting right wall
    if(fin_pos_x+ r >= canvas_width){
        fin_pos_x = canvas_width-r;
        fin_vel_x = -fin_vel_x;

    }//check if ball is hitting left wall
    if (fin_pos_x -r <= 0){
        fin_pos_x = r;
        fin_vel_x = -fin_vel_x;

    } //check if ball is hitting celing
    if (fin_pos_y -r<= 0){
        fin_pos_y = r;
        fin_vel_y = -fin_vel_y;

    } //check if ball is hitting floor
    if (fin_pos_y + r >= canvas_height){
        fin_pos_y = canvas_height-r;
        fin_vel_y = -fin_vel_y;
    }
    
    //check if ball is hitting another ball
    for(auto& check_ball: balls){
        if(this == check_ball.get()){
            continue;
        }
        float r2 = check_ball->get_shape().getRadius();
        auto check_ball_position = check_ball->get_shape().getPosition();

        float dx = check_ball_position.x - fin_pos_x;
        float dy = check_ball_position.y - fin_pos_y;
        float distance = sqrt(dx*dx + dy*dy);

        if(!(distance <= r + r2)){
            continue;
        }
        //collision occured, deflect with v1 = this ball, v2 = check_ball
        std::pair<float, float> n = {check_ball_position.x - fin_pos_x, check_ball_position.y - fin_pos_y};
        float abs_n = sqrt(n.first*n.first + n.second*n.second);
        std::pair<float,float> unit_n = {n.first/abs_n, n.second/abs_n};
        std::pair<float,float> unit_t = {-unit_n.second, unit_n.first};

        float v1_n = fin_vel_x*unit_n.first +fin_vel_y*unit_n.second;
        float v1_t = fin_vel_x*unit_t.first +fin_vel_y*unit_t.second;

        float v2_n = check_ball->velocity.first*unit_n.first + check_ball->velocity.second*unit_n.second;
        float v2_t = check_ball->velocity.first*unit_t.first + check_ball->velocity.second*unit_t.second;

        float v1_n_prime = (this->mass*v1_n+check_ball->mass*v2_n - check_ball->mass*(v1_n-v2_n)*coefficient_of_restitution)/(this->mass + check_ball->mass);

        float v2_n_prime = (this->mass*v1_n+check_ball->mass*v2_n - this->mass*(v2_n-v1_n)*coefficient_of_restitution)/(this->mass + check_ball->mass);

        std::pair<float, float> new_velocity1 = {v1_t*unit_t.first+v1_n_prime*unit_n.first, v1_t*unit_t.second+v1_n_prime*unit_n.second};
        std::pair<float, float> new_velocity2 = {v2_t*unit_t.first+v2_n_prime*unit_n.first, v2_t*unit_t.second+v2_n_prime*unit_n.second};

        fin_vel_x = new_velocity1.first;
        fin_vel_y = new_velocity1.second;

        check_ball->velocity.first = new_velocity2.first;
        check_ball->velocity.second = new_velocity2.second;

        //check and adjust for overlap
        float overlap = r+r2 -distance;
        if(overlap >= 0 && coefficient_of_restitution ==1){
            if(fin_vel_x<0){
                fin_pos_x -= overlap/2;
            }else{
                fin_pos_x += overlap/2;
            }
            if(fin_vel_y<0){
                fin_pos_y -= overlap/2;
            }else{
                fin_pos_y += overlap/2;
            }

            if(check_ball->velocity.first<0){
                Point adjustment_point = {check_ball->position.x -= overlap/2, check_ball->position.y};
                check_ball->set_ball_position(adjustment_point);
            }else{
                Point adjustment_point = {check_ball->position.x += overlap/2, check_ball->position.y};
                check_ball->set_ball_position(adjustment_point);
            }
            if(check_ball->velocity.second<0){
                Point adjustment_point = {check_ball->position.x, check_ball->position.y -= overlap/2};
                check_ball->set_ball_position(adjustment_point);
            }else{
                Point adjustment_point = {check_ball->position.x, check_ball->position.y += overlap/2};
                check_ball->set_ball_position(adjustment_point);
            }

        }
    }
    this->velocity = {fin_vel_x, fin_vel_y};
    this->position = {fin_pos_x, fin_pos_y};
    ball_shape.setPosition(fin_pos_x, fin_pos_y);
}

