#ifndef __APP__HPP__
#define __APP__HPP__

#include "Scene.hpp"

#include <memory>
#include <stack>

class App{
public:
    int run();
private:
    std::stack<std::unique_ptr<Scene> > scenes;
};

#endif
