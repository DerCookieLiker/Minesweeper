#pragma once

#include "Cell.h"
#include <SFML/Graphics.hpp>

class Grid{

public:
    Grid(int sizeX = 16, int sizeY = 16);
    ~Grid();

    void checkField(int x, int y);
    void switchFlag(int x, int y);
    void render(sf::RenderWindow &window) const;

    bool checkWin() const;
private:
    Cell* **grid;

    int sizeX;
    int sizeY;

    int numberOfMines;
    int numberOfFlags;
    int openFieldCounter;
    bool firstClick;

    bool gameRun;
    sf::Vector2i getContain(int x, int y);

    void setRandomBombs(int x, int y);
    int countBombs(int x, int y) const;
    void openFields(int x, int y);
    bool inRange(int x, int y) const;
    void setNumbers();
    void openBombs();
};
