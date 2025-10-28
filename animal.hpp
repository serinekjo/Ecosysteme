#ifndef ANIMAL_HPP
#define ANIMAL_HPP

#include "organisme.hpp"

class Animal : public Organisme {
protected:
    int x, y;
    bool genre; // true = mâle, false = femelle
    int age = 0;
    int faim = 0; // nombre de tours où l'animal n'a pas mangé
    bool aDejaAgi;
public:
    Animal(int x, int y, bool genre);

    int getX() const;
    int getY() const;
    void setPosition(int nx, int ny);
    bool estMale() const {return genre;}
    void setDejaAgi(bool valeur) { aDejaAgi = valeur; }
    bool aDejaAgit() const { return aDejaAgi; }

    virtual bool estMort() const = 0;
    virtual char getSymbole() const = 0;
    virtual void mettreJour() = 0;

    int getAge()const;
    int getFaim()const;
    void incrementerAge();
    void incrementerFaim();
    void resetFaim();
};

#endif
