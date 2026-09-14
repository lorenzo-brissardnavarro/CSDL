#include "Jeu.hpp"
#include <iostream>
using namespace std;

Jeu::Jeu()
{
}

void Jeu::demarrer() {

    cout << "Demarrage du jeu (exemple fictif).\n";

    grille.initialiser();
    grille.afficher();
}