#ifndef __BOX__HPP__
#define __BOX__HPP__

#include <SFML/Graphics.hpp>

struct BoxParams{
    sf::Font font;
    unsigned characterSize, width, heightFactor;
};

const char *FONTFILE= "fonts/Roboto-Black.ttf";

class Box: public sf::Drawable{
public:
    void setString(const sf::String& newString);
    void setPosition(sf::Vector2f newPos);
protected:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
private:
    sf::RectangleShape rect;
    sf::Text text;
    static BoxParams params;
};

#endif
