#include "loups.hpp"
#include "univers.hpp"

Loup::Loup(int x, int y, bool genre) : Animal(x, y,genre) {}

char Loup::getSymbole() const {
    return 'L';
}

void Loup::deplacement(Univers& univers) {
    univers.deplacerAnimal(this);
}

bool Loup::estMort() const {
    // Un loup meurt s'il atteint 60 tours OU s'il n'a pas mangé depuis 10 tours (faim >= 10)
    return (age >= 60 || faim >= 10);  // Changé de 11 à 10
}

void Loup::mettreJour() {
    incrementerAge();
    incrementerFaim();
}