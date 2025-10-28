// sel.cpp
#include "sel.hpp"

Sel::Sel(int x, int y) : Organisme(x, y) {}

char Sel::getSymbole() const {
    return 'S';
}
