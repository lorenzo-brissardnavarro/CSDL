#include "Jeu.hpp"
#include <iostream>
#include <string>
using namespace std;

Jeu::Jeu()
{
}

void Jeu::demarrer() {

    auto [sudokuGrille, solutionGrille] = grille.initialiser();
    grille.remplirGrille(sudokuGrille);
    grille.remplirSolution(solutionGrille);

    int ligne, col, valeur;
    string texte;
    do {
        cout << endl;
        grille.afficher();
        cout << "\nSaisissez votre valeur (entier compris entre 1 et 9) svp : ";
        cin >> valeur;
        cout << "Colonne : ";
        cin >> col;
        cout << "Ligne : ";
        cin >> ligne;
        if(grille.getGrille(ligne, col) != 0) {
            texte = "La place est prise par un autre nombre";
        } else {
            if(grille.verifierLigne(ligne, col, valeur) == false) {
                texte = "Chiffre deja present sur la ligne";
            } else if (grille.verifierColonne(col, ligne, valeur) == false) {
                texte = "Chiffre deja present sur la colonne";
            } else {
                grille.setGrille(ligne, col, valeur);
                texte = "Chiffre ajoute";
            }
        }
    cout << texte << endl;
        
    } while(grille.grilleComplete() != true);
}