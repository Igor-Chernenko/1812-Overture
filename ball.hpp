#pragma Once
#include "point.hpp"
#include <utility>
#include <memory>
#include <SFML/Graphics.hpp>


class Ball{
    public:
        int canvas_width;
        int canvas_height;

        Ball(float init_angle);
        void set_ball_position(Point ball_position);
        sf::CircleShape& get_shape();

        void update_ball(sf::Time delta_t, std::vector<std::unique_ptr<Ball>>& balls, int coefficient_of_restitution);

    private:
        
        const float GRAVITY = -9.807;
        const float INITIAL_SPEED = 500.f;
        const float BALL_MASS_CONSTANT = 0.2f; // kg per radius pixel
        
        float radius;
        float mass;
        sf::CircleShape ball_shape;
        Point position;
        Point center;
        std::pair<float, float> velocity; //x,y
        const std::pair<float, float> acceleration = {0, GRAVITY};//x,y

};