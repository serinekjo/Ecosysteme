#ifndef MOUTON_HPP
#define MOUTON_HPP

#include "animal.hpp"

class Mouton : public Animal {
public:
    Mouton(int x, int y, bool genre);
    char getSymbole() const override;
    void deplacement(Univers& univers) override;
    bool estMort() const override;
    void mettreJour()override;
};

#endif
