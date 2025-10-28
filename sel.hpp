// sel.hpp
#ifndef SEL_HPP
#define SEL_HPP

#include "organisme.hpp"

class Sel : public Organisme {
public:
    Sel(int x, int y);
    char getSymbole() const override;
};

#endif
