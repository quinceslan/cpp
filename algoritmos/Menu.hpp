#ifndef __MENU__HPP__
#define __MENU__HPP__

#include "Scene.hpp"
#include "Item.hpp"

#include <functional>
#include <vector>

class Menu: public Scene{
public:
    Menu();

    void setTitle(const sf::String &newTitle);

    void setPosition(const sf::Vector2f &newPos);

    template<typename Fun>
    void addItem(const sf::String &label, Fun fun){
        items.emplace_back();
        items.back().setFont(font);
        items.back().setCharacterSize(characterSize);
        items.back().setTitle(label);
        items.back().setCallBack(fun);
        items.back().setSelectColor(selectColor, deselectColor);
        items.back().setCallBack(fun);
        if(items.size() == 1){
            items.back().setPosition(pos+ sf::Vector2f(0.0f, characterSize+ 10));
        }
        else{
            items.back().setPosition(items[items.size()- 2].getPosition()+ sf::Vector2f(0, characterSize+ 10));
        }
    }

    void readEvent(sf::Event event) override;

    void updateLogic() override;
protected:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
private:
    sf::Text title;
    std::vector<Item> items;
    sf::Font font;
    unsigned characterSize;
    sf::Color titleColor, selectColor, deselectColor;
    sf::Vector2f pos;
};

#endif
