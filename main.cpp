#include <SFML/Graphics.hpp>
#include "Cell.h"
#include "Grid.h"
#include <math.h>
#include <iostream>

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 800), "Minesweeper", sf::Style::Titlebar | sf::Style::Close);
    window.setFramerateLimit(60);
    Grid g;

    sf::Clock current;
    float deltaTime;
    float mouseDelay = 0;
    while (window.isOpen() && !g.checkWin()) {

        deltaTime = current.restart().asSeconds();

        if(mouseDelay > 0){
            mouseDelay -= deltaTime;
        }else{
            mouseDelay = 0;
        }

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && !mouseDelay){
            sf::Vector2i mousPos = sf::Mouse::getPosition(window);
            g.checkField(mousPos.x, mousPos.y);
            //std::cout << "[Left] mPos_X: " << mousPos.x << " | " << "mPos_Y: " << mousPos.y << std::endl;
            mouseDelay = 0.1;
        }
        if(sf::Mouse::isButtonPressed(sf::Mouse::Right) && !mouseDelay){
            sf::Vector2i mousPos = sf::Mouse::getPosition(window);
            g.switchFlag(mousPos.x, mousPos.y);
            //std::cout << "[Left] mPos_X: " << mousPos.x << " | " << "mPos_Y: " << mousPos.y << std::endl;
            mouseDelay = 0.1;
        }

        window.clear(sf::Color::White);
        g.render(window);
        window.display();
    }

    return 0;
}
