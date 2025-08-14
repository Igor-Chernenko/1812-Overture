#include "button.hpp"


Button::Button(float width, float height, Point position){
    sf::RectangleShape new_button_shape;
    this->width = width;
    this->height = height;
    new_button_shape.setSize({width, height});
    new_button_shape.setFillColor(sf::Color::Blue);
    new_button_shape.setOutlineColor(sf::Color::Black);
    new_button_shape.setOutlineThickness(5);
    new_button_shape.setPosition({position.x, position.y});

    button_shape = new_button_shape;
}

bool Button::is_clicked(sf::Vector2i click){
    if(click.x<= width + button_shape.getPosition().x && click.x >= button_shape.getPosition().x &&
        click.y<= height + button_shape.getPosition().y && click.y >= button_shape.getPosition().y){
            return true;
        }
    return false;
}

sf::Color Button::get_color(){
    return this->button_shape.getFillColor();
}

sf::RectangleShape Button::get_shape(){
    return this->button_shape;
}

void Button::change_color(sf::Color new_color){
    button_shape.setFillColor(new_color);
}