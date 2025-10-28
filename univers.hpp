#ifndef UNIVERS_HPP
#define UNIVERS_HPP

#include <vector>
#include "organisme.hpp"
#include "animal.hpp"
#include "herbe.hpp"

class Animal; // déclaration anticipée

class Univers {
    private:
    int lignes, colonnes;
    std::vector<std::vector<Organisme*>> grille;
    std::vector<std::vector<Herbe>>herbes;
    int nb_loups;
    int nb_moutons;
    int tour = 0;


public:
    Univers(int colonnes, int lignes, int nb_loups = 0, int nb_moutons = 0);
    ~Univers();

    void placerAleatoirement(int nb, char symbole);
    void afficher();
    bool isFinUnivers();
    void setGrille(int i, int j, Organisme* org);
    bool estCaseValide(int x, int y) const;
    bool estCaseLibre(int x, int y) const;
    std::vector<std::pair<int, int>> casesAdjacentesLibres(int x, int y) const;
    void deplacerAnimal(Animal* animal);
    void Reproduction(Animal* animal);
    void mangerProie(Animal* animal);
    void mettreAJour();
};

#endif
