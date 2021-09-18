#pragma once
#include <SFML/Graphics.hpp>

class Cell {

public:
    Cell(const sf::Color &color = sf::Color(0, 176, 47) ,int indexX = 0, int indexY = 0, int width = 10, bool mine = false, int number = -1);

    void draw(sf::RenderWindow &window) const;
    bool canOpen() const;
    bool contains(int x, int y) const;

    void setIndexY(int indexY);
    void setIndexX(int indexX);
    void setWidth(int width);
    void setNumber(int number);
    void setColor(sf::Color color);
    void setMine(bool mine);
    void setFlag(bool flag);
    void setVisible(bool visible);

    int getIndexY() const;
    int getIndexX() const;
    int getWidth() const;
    int getNumber() const;
    sf::Color getColor() const;

    bool isMine() const;
    bool isFlag() const;
    bool isVisible() const;

private:
    int indexX;
    int indexY;
    int width;

    bool mine;
    bool flag;
    bool visible;
    int number;

    sf::Color color;

};
