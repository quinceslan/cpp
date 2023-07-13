#ifndef __SCENE__HPP__
#define __SCENE__HPP__

#include <SFML/Graphics.hpp>

class Scene: public sf::Drawable{
public:
    virtual ~Scene(){}
    virtual void readEvent(sf::Event event)= 0;
    virtual void updateLogic()= 0;
    void passTime(float dt);
private:
    float time;
};

#endif
