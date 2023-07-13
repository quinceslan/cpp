#include "Menu.hpp"

#include <cassert>

Menu::Menu()
    : characterSize(48), titleColor(sf::Color::White)
    , selectColor(sf::Color::Red), deselectColor(sf::Color::White){
    assert(font.loadFromFile("fonts/Roboto-Black.ttf"));
    title.setFont(font);
    title.setCharacterSize(characterSize);
    setTitle("Menu Principal");
    title.setPosition(pos);
}

void Menu::setTitle(const sf::String &newTitle){
    title.setString(newTitle);
    title.setFillColor(titleColor);
    title.setOrigin(title.getLocalBounds().width/ 2, 0.0f);
}

void Menu::setPosition(const sf::Vector2f &newPos){
    pos= newPos;
    title.setPosition(pos);
    for(unsigned i= 0; i< items.size(); ++i){
        items[i].setPosition(pos.x, pos.y+ characterSize* (i*1.5f+ 2.0f));
    }
}

void Menu::readEvent(sf::Event event){
    if(event.type== sf::Event::MouseMoved){
        for(Item &item: items) item.onMouseMove(event.mouseMove);
    }
    else if(event.type== sf::Event::MouseButtonPressed){
        for(Item &item: items) item.onMouseClick(event.mouseButton);
    }
}

void Menu::updateLogic(){

}

void Menu::draw(sf::RenderTarget &target, sf::RenderStates states) const{
    target.draw(title, states);
    for(const Item &item: items)
        target.draw(item, states);
}
