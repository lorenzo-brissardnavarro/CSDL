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
        cout << "Colonne (1-9) : ";
        cin >> col;
        cout << "Ligne (1-9) : ";
        cin >> ligne;

        if (valeur < 1 || valeur > 9) {
            texte = "\033[31mLa valeur doit etre comprise entre 1 et 9\033[0m";
        } else if (col < 1 || col > 9 || ligne < 1 || ligne > 9) {
            texte = "\033[31mLa ligne et la colonne doivent etre comprises entre 1 et 9\033[0m";
        } else {
            col--;
            ligne--;

            if (grille.getGrille(ligne, col) != 0) {
                texte = "\033[31mLa place est deja prise par un autre nombre\033[0m";
            } else if (grille.verifierLigne(ligne, col, valeur) == false) {
                texte = "\033[31mChiffre deja present sur la ligne\033[0m";
            } else if (grille.verifierColonne(col, ligne, valeur) == false) {
                texte = "\033[31mChiffre deja present sur la colonne\033[0m";
            } else if (grille.verifierCarre(ligne, col, valeur) == false) {
                texte = "\033[31mChiffre deja present dans le carre\033[0m";
            } else {
                grille.setGrille(ligne, col, valeur);
                texte = "\033[32mChiffre ajoute\033[0m";
            }
        }
        cout << texte << endl;
    } while (grille.grilleComplete() != true);
}