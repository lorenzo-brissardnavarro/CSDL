#include "Grille.hpp"
#include "json.hpp"
#include <iostream>
#include <cpr/cpr.h>
#include <vector>
#include <utility>
using namespace std;
using json = nlohmann::json;


Grille::Grille()
    : grille{}, solution{}
{
}


// Méthode d'initialisation de la grille en faisant un appel API pour récupèrer les valeurs de la grille
pair<nlohmann::json, nlohmann::json> Grille::initialiser() {
    // Faire appel GET
    cpr::Response response = cpr::Get(cpr::Url{"https://sudoku-api.vercel.app/api/dosuku"});

    // Vérification statut HTTP
    if (response.status_code == 200) {
        json data = json::parse(response.text);
        json sudoku = data["newboard"]["grids"][0]["value"];
        json solution = data["newboard"]["grids"][0]["solution"];
        
        return make_pair(sudoku, solution);

    } else {
        cerr << "Erreur HTTP : " << response.status_code << " - " << response.error.message << endl;
        return {};
    }

}

void Grille::remplirGrille(const nlohmann::json& value) {
    // Ajout des valeurs dans notre tableau grille
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j <9; ++j) {
            this->grille[i][j] = value[i][j];
        }
    }
}

void Grille::remplirSolution(const nlohmann::json& value) {
    // Ajout des valeurs dans notre tableau grille
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j <9; ++j) {
            this->solution[i][j] = value[i][j];
        }
    }
}

void Grille::afficher() {
    // Affichage du tableau
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j <9; ++j) {
            cout << this->grille[i][j] << " ";
        }
        cout << endl;
    }
}

bool Grille::verifierLigne(int ligne, int colActuelle, int valeur) {
    // On vérifie si le nombre saisi n'est pas déjà sur la ligne
    for (int col = 0; col < 9; col++) {
        if (col != colActuelle) {
            if (this->grille[ligne][col] == valeur) {
                return false;
            }
        }
    }
    return true;
}

bool Grille::verifierColonne(int col, int ligneActuelle, int valeur) {
    // On vérifie si le nombre saisi n'est pas déjà dans la colonne
    for (int ligne = 0; ligne < 9; ligne++) {
        if (ligne != ligneActuelle) {
            if (this->grille[ligne][col] == valeur) {
                return false;
            }
        }
    }
    return true;
}

bool Grille::grilleComplete() {
    // vérifier si la grille est entièrement et correctement complétée
    for (int ligne = 0; ligne < 9; ligne++) {
        for (int col = 0; col < 9; col++) {
            if (this->grille[ligne][col] != this->solution[ligne][col]) {
                return false;
            }
        }
    }
    return true;
}

int Grille::getGrille(int ligne, int col) {
    return this->grille[ligne][col];
}

void Grille::setGrille(int ligne, int col, int valeur) {
    this->grille[ligne][col] = valeur;
}