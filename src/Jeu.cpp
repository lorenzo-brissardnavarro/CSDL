#include "Jeu.hpp"
#include <iostream>
using namespace std;

Jeu::Jeu()
{
}

void Jeu::demarrer() {

    nlohmann::json sudoku = grille.initialiser();
    grille.remplirGrille(sudoku);
    grille.afficher();
}