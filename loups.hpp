#ifndef LOUPS_HPP
#define LOUPS_HPP

#include "animal.hpp"

class Loup : public Animal {
public:
    Loup(int x, int y, bool genre);
    char getSymbole() const override;
    void deplacement(Univers& univers) override;
    bool estMort() const override;
    void mettreJour()override;


};

#endif
