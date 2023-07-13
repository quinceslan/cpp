#include "Menu.hpp"

#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;

int main(){
    sf::RenderWindow window(sf::VideoMode(800, 600), "Mi juego favorito");
    Menu menu;
    menu.setTitle("Mi juego favorito");
    menu.addItem("Nuevo Juego", [](){ cout<<"Opcion 1"<<endl; });
    menu.addItem("Guardar partida", [](){ cout<<"Opcion 2"<<endl; });
    menu.addItem("Elaborar nueva caza", [](){ cout<<"Opcion 3"<<endl; });
    menu.addItem("Salir", [](){ cout<<"Opcion 4"<<endl; });
    menu.setPosition(sf::Vector2f(400.0f, 50.0f));
    while(window.isOpen()){
        sf::Event event;
        while(window.pollEvent(event)){
            if(event.type== sf::Event::Closed){
                window.close();
            }
            else{
                menu.readEvent(event);
            }
        }
        window.clear(sf::Color::Blue);
        window.draw(menu);
        window.display();
    }
    return EXIT_SUCCESS;
}
