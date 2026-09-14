#include "Grille.hpp"
#include "json.hpp"
#include <iostream>
#include <cpr/cpr.h>
#include <vector>
using namespace std;
using json = nlohmann::json;



Grille::Grille() 
{
}


// Méthode d'initialisation de la grille en faisant un appel API pour récupèrer les valeurs de la grille
json Grille::initialiser() {
    // Faire appel GET
    cpr::Response response = cpr::Get(cpr::Url{"https://sudoku-api.vercel.app/api/dosuku"});

    // Vérification statut HTTP
    if (response.status_code == 200) {
        json data = json::parse(response.text);
        json sudoku = data["newboard"]["grids"][0]["value"];
        return sudoku;

    } else {
        cerr << "Erreur HTTP : " << response.status_code << " - " << response.error.message << endl;
        return {};
    }

}

void Grille::remplirGrille(const nlohmann::json& value) {
    // Ajout des valeurs dans notre tableau grille
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j <9; ++j) {
            grille[i][j] = value[i][j];
        }
    }
}

void Grille::afficher() {
    // Affichage du tableau
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j <9; ++j) {
            cout << grille[i][j] << " ";
        }
        cout << endl;
    }
}