#include "point.hpp"
#include <utility>
#include <SFML/Graphics.hpp>


class Ball{
    public:
        Ball(float init_angle);
        void set_ball_position(Point ball_position);
        sf::CircleShape& get_shape();

        void update_ball(sf::Time delta_t);

    private:
        const float GRAVITY = -9.807;
        const float INITIAL_SPEED = 350.f;
        const float BALL_MASS = 0.2f; // kg/pixel

        sf::CircleShape ball_shape;
        Point position;
        std::pair<float, float> velocity; //x,y
        const std::pair<float, float> acceleration = {0, GRAVITY};//x,y

};