#include "Box.hpp"

void Box::setString(const sf::String &newString){
    text.setString(newString);
    auto rect= text.getLocalBounds();
    text.setOrigin(rect.width/ 2.0f, rect.height);
}

void Box::setPosition(sf::Vector2f newPos){
    text.setPosition(newPos);
    rect.setPosition(newPos);
}

void Box::draw(sf::RenderTarget &target, sf::RenderStates states) const{
    target.draw(rect, states);
    target.draw(text, states);
}
