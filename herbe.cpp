#include "herbe.hpp"

Herbe::Herbe() : presente(true) {}

bool Herbe::estPresente() const {
    return presente;
}

void Herbe::setPresente(bool p) {
    presente = p;
}