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

            if (grille.getGrille(ligne, col) == grille.getSolution(ligne, col)) {
                texte = "\033[31mLa place contient deja le bon nombre\033[0m";
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
    texte = "\033[32mBravo, vous avez resolu le sudoku !\033[0m";
}

///////////////////////////////////////////////////////////// Méthodes interface graphique ///////////////////////////////////////////////

void Jeu::initialiser() {
    auto [sudokuGrille, solutionGrille] = grille.initialiser();
    grille.remplirGrille(sudokuGrille);
    grille.remplirSolution(solutionGrille);
}

void Jeu::demarrerInterface(SDL_Renderer* pRenderer) {
    grille.chargerPolice();
    grille.dessiner(pRenderer);
}

void Jeu::gererClavier(SDL_Event& event) {
    switch (event.key.key) {
        case SDLK_UP:
            grille.deplacerSelection(0, -1);
            break;
        case SDLK_DOWN:
            grille.deplacerSelection(0, 1);
            break;
        case SDLK_LEFT:
            grille.deplacerSelection(-1, 0);
            break;
        case SDLK_RIGHT:
            grille.deplacerSelection(1, 0);
            break;
        case SDLK_1:
        case SDLK_KP_1:
            grille.modifierCase(1);
            break;
        case SDLK_2:
        case SDLK_KP_2:
            grille.modifierCase(2);
            break;
        case SDLK_3:
        case SDLK_KP_3:
            grille.modifierCase(3);
            break;
        case SDLK_4:
        case SDLK_KP_4:
            grille.modifierCase(4);
            break;
        case SDLK_5:
        case SDLK_KP_5:
            grille.modifierCase(5);
            break;
        case SDLK_6:
        case SDLK_KP_6:
            grille.modifierCase(6);
            break;
        case SDLK_7:
        case SDLK_KP_7:
            grille.modifierCase(7);
            break;
        case SDLK_8:
        case SDLK_KP_8:
            grille.modifierCase(8);
            break;
        case SDLK_9:
        case SDLK_KP_9:
            grille.modifierCase(9);
            break;
        default:
            break;
    }
}
