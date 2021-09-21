#include "Grid.h"
#include <windows.h>
#include <time.h>
#include <iostream>

Grid::Grid(int sizeX, int sizeY) : sizeX(sizeX), sizeY(sizeY) {

    this->grid = new Cell**[this->sizeY];

    bool switcher = true;
    for(int i = 0; i < this->sizeY; i++){
        this->grid[i] = new Cell*[this->sizeX];
        for(int j = 0; j < this->sizeX; j++){
            this->grid[i][j] = new Cell((j % 2 == switcher) ? sf::Color(0, 176, 47) : sf::Color(0, 150, 30), i, j, 50, false);
        }
        switcher = !switcher;
    }
    this->firstClick = true;
    this->openFieldCounter = 0;
    this->numberOfMines = 50;
    this->numberOfFlags = 0;

    this->gameRun = true;
}
Grid::~Grid() {

    for(int i = 0; i < this->sizeY; i++){
        for(int j = 0; j < this->sizeX; j++){
            delete this->grid[i][j];
        }
        delete[] this->grid[i];
    }
    delete [] this->grid;
}

void Grid::checkField(int x, int y){

    if(!this->gameRun) return;

    sf::Vector2i pos = this->getContain(x, y);
    if(pos.x == -1 && pos.y == -1) return;
    if(this->grid[pos.y][pos.x]->isFlag()) return;
    if(this->firstClick){
        this->setRandomBombs(pos.x, pos.y);
        this->setNumbers();
        this->firstClick = false;
    }
    if(this->grid[pos.y][pos.x]->isMine()){
        this->gameRun = false;
        this->openBombs();
        return;
    }

    this->openFields(pos.x, pos.y);
}
void Grid::switchFlag(int x, int y){

    if(!this->gameRun) return;

    sf::Vector2i pos = this->getContain(x, y);
    if((pos.x == -1 && pos.y == -1)|| this->grid[pos.y][pos.x]->isVisible()) return;

    if(this->numberOfFlags < this->numberOfMines){
        if(!this->grid[pos.y][pos.x]->isFlag()){
            this->numberOfFlags++;
            this->grid[pos.y][pos.x]->setFlag(true);
        }else{
            this->numberOfFlags--;
            this->grid[pos.y][pos.x]->setFlag(false);
        }
    }else{
        if(this->grid[pos.y][pos.x]->isFlag()){
            this->numberOfFlags--;
            this->grid[pos.y][pos.x]->setFlag(false);
        }
    }
}
void Grid::render(sf::RenderWindow &window) const {
    for(int i = 0; i < this->sizeY; i++){
        for(int j = 0; j < this->sizeX; j++){
            this->grid[i][j]->draw(window);
        }
    }
}
sf::Vector2i Grid::getContain(int x, int y){

    for(int i = 0; i < this->sizeY; i++){
        for(int j = 0; j < this->sizeX; j++){
            if(this->grid[i][j]->contains(x, y))
                return sf::Vector2i(j, i);
        }
    }
    return sf::Vector2i(-1, -1);
}
void Grid::setRandomBombs(int x, int y){

srand(time(NULL));

    int randY, randX;
    for(int i = 0; i < this->numberOfMines; i++){

        randX = rand() % this->sizeX;
        randY = rand() % this->sizeY;
        if(this->grid[y][x]->isMine() ||   (x -1 == randX && y - 1 == randY)
                                        || (x == randX && y - 1 == randY)
                                        || (x + 1 == randX && y - 1 == randY)
                                        || (x - 1 == randX && y == randY)
                                        || (x == randX && y == randY)
                                        || (x + 1 == randX && y == randY)
                                        || (x -1 == randX && y + 1 == randY)
                                        || (x == randX && y + 1 == randY)
                                        || (x + 1 == randX && y + 1 == randY)){
            i--;

        }else{
            this->grid[randY][randX]->setMine(true);
        }

    }
}
void Grid::openFields(int x, int y){

    this->grid[y][x]->setVisible(true);
    this->grid[y][x]->setColor(( x % 2 == (y % 2 == 0)) ? sf::Color(150, 150, 150) : sf::Color(120, 120, 120));
    this->openFieldCounter++;

    if(this->grid[y][x]->getNumber() == 0){

        for(int i = -1; i <= 1; i++){
            for(int j = -1; j <= 1; j++){
              if(this->inRange(j + x, i + y) && this->grid[y + i][x + j]->canOpen()) this->openFields(j + x, i + y);
            }
        }
    }
}
bool Grid::inRange(int x, int y) const{
   if(x > this->sizeX - 1 || y > this->sizeY - 1 || x < 0 || y < 0) return false;
   return true;
}
void Grid::setNumbers(){
    for(int i = 0; i < this->sizeY; i++){
        for(int j = 0; j < this->sizeX; j++){
            if(!this->grid[i][j]->isMine()){
                int bombs = this->countBombs(j, i);
                if(bombs >= 0){
                    this->grid[i][j]->setNumber(bombs);
                }
            }
        }
    }
}
int Grid::countBombs(int x, int y) const{
    int counter = 0;
    if(this->grid[y][x]->isMine()){
        return -1;
    }
    for(int i = -1; i <= 1; i++){
        for(int j = -1; j <= 1; j++){
          if(this->inRange(x + j, y + i) && this->grid[y + i][x + j]->isMine()) counter++;
        }
    }
    return counter;
}
void Grid::openBombs() {

    for(int i = 0; i < this->sizeY; i++){
        for(int j = 0; j < this->sizeX; j++){
            if(this->grid[i][j]->isMine() && !this->grid[i][j]->isFlag()){
                this->grid[i][j]->setVisible(true);
            }
            if(this->grid[i][j]->isFlag() && !this->grid[i][j]->isMine()){
                this->grid[i][j]->setWrongFlag(true);
            }
        }
    }
}
bool Grid::checkWin() const{

    return (this->openFieldCounter == (this->sizeX * this->sizeY) - this->numberOfMines);
}
