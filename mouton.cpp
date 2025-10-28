#include "mouton.hpp"
#include "univers.hpp"

Mouton::Mouton(int x, int y, bool genre) : Animal(x, y,genre) {}

char Mouton::getSymbole() const {
    return 'M';
}

void Mouton::deplacement(Univers& univers) {
    univers.deplacerAnimal(this);
}


bool Mouton::estMort()const{
    return (age >= 50 || faim >= 5);
}

void Mouton::mettreJour() {
    incrementerAge();
    incrementerFaim();
}