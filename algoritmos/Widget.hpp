#ifndef __WIDGET__HPP__
#define __WIDGET__HPP__

#include <SFML/Graphics.hpp>
#include <functional>

class Button: public sf::Sprite{
public:
    void onMouseMove(sf::Event::MouseMoveEvent mouse);

    void onMouseClick(sf::Event::MouseButtonEvent mouse);
private:
    std::function<void(void)> callback;
};

#endif