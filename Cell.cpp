#include "Cell.h"
Cell::Cell(const sf::Color &color, int indexX, int indexY, int width, bool mine, int number) :
    indexX(indexX),
    indexY(indexY),
    width(width),
    mine(mine),
    flag(false),
    visible(false),
    number(number),
    color(color) { }

void Cell::draw(sf::RenderWindow &window) const{
    sf::RectangleShape shape;
    shape.setSize({(float) this->width, (float) this->width});
    shape.setFillColor(this->color);
    shape.setPosition({(float) this->indexX * this->width, (float) this->indexY * this->width});
    shape.setOutlineColor(sf::Color::Black);
    shape.setOutlineThickness(1.0);

    window.draw(shape);
    if(this->visible) {
        if(this->mine){
            sf::Texture t;
            t.loadFromFile("assets/images/bomb.png");
            sf::Sprite s;
            s.setTexture(t, false);
            s.setScale({3, 3});
            s.setPosition({(float) this->indexX * this->width + 1, (float) this->indexY * this->width + 1});
            window.draw(s);
        }
        if(this->number > 0){
            sf::Texture t;

            switch(this->number){
                case 1: t.loadFromFile("assets/images/one.png");
                    break;
                case 2: t.loadFromFile("assets/images/two.png");
                    break;
                case 3: t.loadFromFile("assets/images/three.png");
                    break;
                case 4: t.loadFromFile("assets/images/four.png");
                    break;
                case 5: t.loadFromFile("assets/images/five.png");
                    break;
                case 6: t.loadFromFile("assets/images/six.png");
                    break;
                case 7: t.loadFromFile("assets/images/seven.png");
                    break;
                case 8: t.loadFromFile("assets/images/eight.png");
                    break;
            }
            sf::Sprite s;
            s.setTexture(t, false);
            s.setScale({3, 3});
            s.setPosition({(float) this->indexX * this->width + 1, (float) this->indexY * this->width + 1});
            window.draw(s);
        }
    }
    if(this->flag){
            sf::Texture t;
            t.loadFromFile("assets/images/flag.png");
            sf::Sprite s;
            s.setTexture(t, false);
            s.setScale({3, 3});
            s.setPosition({(float) this->indexX * this->width + 1, (float) this->indexY * this->width + 1});
            window.draw(s);
    }
}
bool Cell::canOpen() const{
    return (this->number >= 0 && !this->flag && !this->mine && !this->visible);
}
bool Cell::contains(int x, int y) const {
    int this_X = this->indexX * this->width;
    int this_Y = this->indexY * this->width;
    return (x >= this_X && x <= this_X + this->width && y >= this_Y && y <= this_Y + this->width);
}

void Cell::setIndexY(int indexY){
    this->indexY = indexY;
}
void Cell::setIndexX(int indexX){
    this->indexX = indexX;
}
void Cell::setWidth(int width){
    this->width = width;
}
void Cell::setNumber(int number){
    this->number = number;
}
void Cell::setColor(sf::Color color){
    this->color = color;
}
void Cell::setMine(bool mine){
    this->mine = mine;
}
void Cell::setFlag(bool flag){
    this->flag = flag;
}
void Cell::setVisible(bool visible){
    this->visible = visible;
}

int Cell::getIndexY() const{
    return this->indexX;
}
int Cell::getIndexX() const{
    return this->indexY;
}
int Cell::getWidth() const{
    return this->width;
}
int Cell::getNumber() const{
    return this->number;
}
sf::Color Cell::getColor() const{
    return this->color;
}

bool Cell::isMine() const{
    return this->mine;
}
bool Cell::isFlag() const{
    return this->flag;
}
bool Cell::isVisible() const{
    return this->visible;
}
