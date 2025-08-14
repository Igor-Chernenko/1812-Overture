#pragma Once
#include "point.hpp"
#include <SFML/Graphics.hpp>
#include <vector>

class Button{
    public:
        Button() = default;
        Button(float width, float height, Point position);

        bool is_clicked(sf::Vector2i click);
        sf::Color get_color();
        void change_color(sf::Color new_color);

        sf::RectangleShape get_shape();


    private:
        float width;
        float height;
        sf::RectangleShape button_shape;
};