#include "Grille.hpp"
#include <iostream>
#include <cpr/cpr.h>
using namespace std;



Grille::Grille() {
    taille = 9;
}


// Méthode d'initialisation de la grille en faisant un appel API pour récupèrer les valeurs de la grille
void Grille::initialiser() {
    // Faire appel GET
    cpr::Response response = cpr::Get(cpr::Url{"https://sudoku-api.vercel.app/api/dosuku"});

    // Vérification statut HTTP
    if (response.status_code == 200) {
        cout << "Contenu de la reponse : " << response.text << endl;
    } else {
        cerr << "Erreur HTTP : " << response.status_code << " - " << response.error.message << endl;
    }

}

void Grille::afficher() {
    cout << "Affichage d'une grille de taille " << taille << " (exemple fictif).\n";
}