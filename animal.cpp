#include "animal.hpp"

Animal::Animal(int x, int y,bool genre) : x(x), y(y), genre(genre), age(0),faim(0) {}

int Animal::getX() const {
    return x;
}

int Animal::getY() const {
    return y;
}

void Animal::setPosition(int nx, int ny) {
    x = nx;
    y = ny;
}

int Animal::getAge()const{
    return age;
}

int Animal::getFaim()const{
    return faim;
}

void Animal::incrementerAge() {
    age++;
}

void Animal::incrementerFaim(){
    faim++;
}

void Animal::resetFaim(){
    faim = 0;
}
