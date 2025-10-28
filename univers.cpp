#include <iostream>
#include <random>
#include <functional>
#include "univers.hpp"
#include "mouton.hpp"
#include "loups.hpp"
#include "animal.hpp"

Univers::Univers(int l, int c, int nbMoutons, int nbLoups)
    : lignes(l), colonnes(c),
      grille(l, std::vector<Organisme*>(c, nullptr)),
      nb_loups(nbLoups), nb_moutons(nbMoutons), tour(0)  // initialisation
{
    placerAleatoirement(nbMoutons, 'M');
    placerAleatoirement(nbLoups, 'L');
}


bool Univers::isFinUnivers() {
    return nb_moutons == 0 && nb_loups == 0;
}


std::string coordEnLettre(int x, int y) {
    char ligne = 'A' + x;
    int colonne = y + 1;
    return "(" + std::string(1, ligne) + std::to_string(colonne) + ")";
}



Univers::~Univers() {
    for (int i = 0; i < lignes; ++i) {
        for (int j = 0; j < colonnes; ++j) {
            if (grille[i][j] != nullptr) {  // Ajoutez cette vérification
                delete grille[i][j];
            }
        }
    }
        std::cout << "Fin de l'univers." << std::endl;

}
void Univers::mangerProie(Animal* animal) {
    int x = animal->getX();
    int y = animal->getY();

    for (int dx = -1; dx <= 1; ++dx) {
        for (int dy = -1; dy <= 1; ++dy) {
            if (dx == 0 && dy == 0) continue;

            int nx = x + dx;
            int ny = y + dy;

            if (!estCaseValide(nx, ny)) continue;

            Organisme* voisin = grille[nx][ny];
            if (voisin == nullptr) continue;

            Animal* autreAnimal = dynamic_cast<Animal*>(voisin);
            if (autreAnimal == nullptr) continue;

            if (animal->getSymbole() == 'L' && autreAnimal->getSymbole() == 'M') {
                // Marque que l'animal a déjà agi
                animal->setDejaAgi(true);

                // Sauvegarde ancienne position
                int oldX = animal->getX();
                int oldY = animal->getY();

                // ✅ Ajoute cette vérification avant d'accéder à la grille
                if (estCaseValide(oldX, oldY) && estCaseValide(nx, ny)) {
                    // Déplace le loup
                    animal->setPosition(nx, ny);
                    grille[nx][ny] = animal;
                    grille[oldX][oldY] = nullptr;

                    // Réinitialise la faim
                    if (Loup* loup = dynamic_cast<Loup*>(animal)) {
                        loup->resetFaim();
                    }

                    // Supprime le mouton
                    delete autreAnimal;
                    nb_moutons--;

                    std::cout << "Le loup " << coordEnLettre(oldX, oldY)
                            << " a mangé et reste en " << coordEnLettre(nx, ny) << std::endl;
                }

                return; // Sort après avoir mangé
            }
        }
    }
}


void Univers::placerAleatoirement(int nb, char symbole) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dx(0, lignes - 1);
    std::uniform_int_distribution<> dy(0, colonnes - 1);



    int placees = 0;
    while (placees < nb) {
        int i = dx(gen);
        int j = dy(gen);

        if (grille[i][j] == nullptr) {
            bool genre = rand() % 2;
            if (symbole == 'M') grille[i][j] = new Mouton(i, j,genre);
            if (symbole == 'L') grille[i][j] = new Loup(i, j,genre);
            ++placees;
        }
    }
}

void Univers::setGrille(int i, int j, Organisme* org) {
    grille[i][j] = org;
}

bool Univers::estCaseValide(int x, int y) const {
    return x >= 0 && x < lignes && y >= 0 && y < colonnes;
}

bool Univers::estCaseLibre(int x, int y) const {
    return grille[x][y] == nullptr;
}

std::vector<std::pair<int, int>> Univers::casesAdjacentesLibres(int x, int y) const {
    std::vector<std::pair<int, int>> cases;
    for (int dx = -1; dx <= 1; ++dx) {
        for (int dy = -1; dy <= 1; ++dy) {
            if (dx == 0 && dy == 0) continue;
            int nx = x + dx;
            int ny = y + dy;
            if (estCaseValide(nx, ny) && estCaseLibre(nx, ny)) {
                cases.emplace_back(nx, ny);
            }
        }
    }
    return cases;
}

void Univers::deplacerAnimal(Animal* animal) {
    int x = animal->getX();
    int y = animal->getY();

    auto cases = casesAdjacentesLibres(x, y);
    if (!cases.empty()) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dist(0, cases.size() - 1);
        auto [nx, ny] = cases[dist(gen)];

        if (estCaseValide(x, y) && estCaseValide(nx, ny)) {
    grille[nx][ny] = animal;
    grille[x][y] = nullptr;
}
animal->setPosition(nx, ny);

        afficher();
        if(animal->getSymbole() == 'M') std::cout << "Le mouton " << coordEnLettre(x,y) << " se déplace en " << coordEnLettre(nx,ny) << std::endl;
        if(animal->getSymbole() == 'L') std::cout << "Le loup " << coordEnLettre(x,y) << " se déplace en " << coordEnLettre(nx,ny) << std::endl;

    }
}

void Univers::Reproduction(Animal* animal) {
    int x = animal->getX();
    int y = animal->getY();

    // On cherche les voisins pour la reproduction
    for (int dx = -1; dx <= 1; ++dx) {
        for (int dy = -1; dy <= 1; ++dy) {
            if (dx == 0 && dy == 0) continue; // pas la même case
            int nx = x + dx;
            int ny = y + dy;

            if (!estCaseValide(nx, ny)) continue;

            Organisme* voisin = grille[nx][ny];
            if (voisin == nullptr) continue;

            // Vérifie que c'est un Animal
            Animal* autreAnimal = dynamic_cast<Animal*>(voisin);
            if (!autreAnimal) continue;

            // Même espèce et sexe opposé ?
            if (animal->getSymbole() == autreAnimal->getSymbole() &&
                animal->estMale() != autreAnimal->estMale()) {

                // Cherche une case libre autour de l'animal pour bébé
                auto casesLibres = casesAdjacentesLibres(x, y);
                if (!casesLibres.empty()) {
                    // Place le bébé sur une case libre au hasard
                    std::random_device rd;
                    std::mt19937 gen(rd());
                    std::uniform_int_distribution<> dist(0, casesLibres.size() - 1);
                    auto [bx, by] = casesLibres[dist(gen)];

                    // Crée le bébé : même type que l'animal, genre aléatoire
                    bool bebeGenre = rand() % 2;

                    if (animal->getSymbole() == 'M') {
                    grille[bx][by] = new Mouton(bx, by, bebeGenre);
                    nb_moutons++;  // 👈 nouveau mouton
                } else if (animal->getSymbole() == 'L') {
                    grille[bx][by] = new Loup(bx, by, bebeGenre);
                    nb_loups++;    // 👈 nouveau loup
                }

                if (grille[x][y] != animal || grille[nx][ny] != autreAnimal) {
    continue;  // Un des parents a été déplacé/supprimé
}

                    std::cout << "Reproduction : un bébé est né en "<< coordEnLettre(bx, by) <<std::endl;

                }

                // Une reproduction par tour suffit, on sort
                return;
            }
        }
    }
}



void Univers::afficher() {
    std::cout << "  ";
    for (int j = 1; j <= colonnes; ++j) {
        std::cout << " " << j << "  ";
    }
    std::cout << std::endl;

    for (int i = 0; i < lignes; ++i) {
        std::cout << "  +";
        for (int j = 0; j < colonnes; ++j) {
            std::cout << "---+";
        }
        std::cout << std::endl;

        std::cout << static_cast<char>('A' + i) << " |";
        for (int j = 0; j < colonnes; ++j) {
            if (grille[i][j])
                std::cout << " " << grille[i][j]->getSymbole() << " |";
            else
                std::cout << "   |";
        }

        std::cout << std::endl;
    }

    std::cout << "  +";
    for (int j = 0; j < colonnes; ++j) {
        std::cout << "---+";
    }
    std::cout << std::endl;
    std::cout << "Tour : " << tour << " Loups : " << nb_loups << " | Moutons : " << nb_moutons << std::endl;
}


void Univers::mettreAJour() {
    tour++;

    // Étape 1 : Collecter les animaux vivants avec leurs positions
    struct AnimalEntry {
        Animal* animal;
        int x;
        int y;
    };
    std::vector<AnimalEntry> animaux;

    for (int i = 0; i < lignes; ++i) {
        for (int j = 0; j < colonnes; ++j) {
            if (Animal* a = dynamic_cast<Animal*>(grille[i][j])) {
                animaux.push_back({a, i, j});
            }
        }
    }

    // Étape 2 : Traiter chaque animal
    for (const auto& entry : animaux) {
        Animal* animal = entry.animal;
        int x = entry.x;
        int y = entry.y;

        // Vérifier que l'animal existe toujours à cette position
        if (!animal || !estCaseValide(x, y) || grille[x][y] != animal) {
            continue;
        }

        animal->incrementerAge();

        // Gestion spécifique aux loups
        if (animal->getSymbole() == 'L' && !animal->aDejaAgit()) {
            if (Loup* loup = dynamic_cast<Loup*>(animal)) {
                loup->incrementerFaim();
                mangerProie(loup);
            }
        }

        // Déplacement
        if (!animal->aDejaAgit() && !animal->estMort()) {
            deplacerAnimal(animal);
        }

        // Reproduction
        if (!animal->aDejaAgit() && !animal->estMort()) {
            Reproduction(animal);
        }

        // Gestion de la mort
        if (animal->estMort()) {
            if (estCaseValide(x, y) && grille[x][y] == animal) {
                if (animal->getSymbole() == 'L') nb_loups--;
                else if (animal->getSymbole() == 'M') nb_moutons--;

                delete animal;
                grille[x][y] = nullptr;
            }
        }
    }
}