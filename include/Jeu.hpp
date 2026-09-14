#ifndef JEU_HPP
#define JEU_HPP

#include "Grille.hpp"

class Jeu {

private:
    Grille grille; // Un Jeu possède une Grille

public:
    Jeu();

    void demarrer();
};

#endif