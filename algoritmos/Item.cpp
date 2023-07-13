#include "Item.hpp"

#include <cassert>

void Item::setSelectColor(sf::Color select, sf::Color deselect){
    assert(select != deselect);
    this->select= select;
    this->deselect= deselect;
}

void Item::onMouseMove(sf::Event::MouseMoveEvent mouse){
    if(getGlobalBounds().contains(mouse.x, mouse.y)){
        setFillColor(select);
        setScale(1.1f, 1.1f);
    }
    else{
        setFillColor(deselect);
        setScale(1.0f, 1.0f);
    }
}

void Item::onMouseClick(sf::Event::MouseButtonEvent mouse){
    if(mouse.button== 0 && getFillColor() == select && callback) callback();
}

void Item::setTitle(const sf::String &title){
    setString(title);
    setOrigin(getLocalBounds().width/ 2, 0);
}
