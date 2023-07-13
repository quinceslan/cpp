#ifndef __ITEM__HPP__
#define __ITEM__HPP__

#include <SFML/Graphics.hpp>

class Item: public sf::Text{
public:
    void setSelectColor(sf::Color select, sf::Color deselect= sf::Color::White);

    void onMouseMove(sf::Event::MouseMoveEvent mouse);

    void onMouseClick(sf::Event::MouseButtonEvent mouse);

    void setTitle(const sf::String &title);

    template<typename Fun>
    void setCallBack(Fun fun){
        callback= fun;
    }
private:
    sf::Color select, deselect;
    std::function<void(void)> callback;
};

#endif
