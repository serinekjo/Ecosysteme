#include "univers.hpp"
#include "organisme.hpp"
#include <vector>
#include <string>
#include <iostream>
#include <cstdlib>
#include <cstdlib> // pour rand() et srand()
#include <ctime>

int main(int argc, char* argv[]) {
    std::srand(std::time(nullptr));

    if (argc != 5) {
        std::cerr << "Usage: " << argv[0] << " <m> <n> <nb_loups> <nb_moutons>" << std::endl;
        return 1;
    }

    int m = std::atoi(argv[1]);
    int n = std::atoi(argv[2]);
    int nb_loups = std::atoi(argv[3]);
    int nb_moutons = std::atoi(argv[4]);
    
    if (m <= 0 || n <= 0 || nb_loups < 0 || nb_moutons < 0) {
        std::cerr << "Les dimensions et le nombre d'animaux doivent être valides." << std::endl;
        return 1;
    }

    Univers u(m, n, nb_moutons, nb_loups);
    

    std::cout << "Lancement de l'univers" << std::endl;
    std::cout << "Au début: " << nb_moutons << "mouton et " << nb_loups << "loups" << std::endl;


    while (!u.isFinUnivers() /*nb_moutons != 0 && nb_loups != 0*/) {
        
        u.afficher();
        u.mettreAJour();

        /*if (tour >= 10) break;*/
    }

    std::cout << "Simulation terminée." << std::endl;
    return 0;
}
