#include "Grille.hpp"
#include "GameObject.hpp"
#include "json.hpp"
#include <iostream>
#include <cpr/cpr.h>
#include <vector>
#include <utility>
using namespace std;
using json = nlohmann::json;


Grille::Grille()
    : grille{}, solution{}, font(nullptr), ligneActuelle(0), colonneActuelle(0), message(""), messageErreur(false)
{
}


// Méthode d'initialisation de la grille en faisant un appel API pour récupèrer les valeurs de la grille
pair<nlohmann::json, nlohmann::json> Grille::initialiser() { // paire de deux objets JSON
    // Faire appel GET
    cpr::Response response = cpr::Get(cpr::Url{"https://sudoku-api.vercel.app/api/dosuku"});

    // Vérification statut HTTP
    if (response.status_code == 200) {
        json data = json::parse(response.text); // conversion au format JSON
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
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            if (this->grille[i][j] == 0) {
                cout << ".";
            } else {
                if(this->grille[i][j] == this->solution[i][j]) {
                    cout << "\033[32m" << this->grille[i][j] << "\033[0m";
                } else {
                    cout << "\033[33m" << this->grille[i][j] << "\033[0m";
                }
            }
            if (j == 2 || j == 5) {
                cout << " | ";
            } else if (j < 8) {
                cout << " ";
            }
        }
        cout << endl;
        if (i == 2 || i == 5) {
            cout << "-----------------------" << endl;
        }
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

bool Grille::verifierCarre(int ligne, int col, int valeur) {
    // On trouve dans quel groupe de 3 se trouve la valeur et on regarde les cases alentours
    int startLigne = (ligne / 3) * 3;
    int startCol = (col / 3) * 3;
    for (int i = startLigne; i < startLigne + 3; i++) {
        for (int j = startCol; j < startCol + 3; j++) {
            if (i != ligne || j != col) {
                if (this->grille[i][j] == valeur) {
                    return false;
                }
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

int Grille::getSolution(int ligne, int col) {
    return this->solution[ligne][col];
}

void Grille::setGrille(int ligne, int col, int valeur) {
    this->grille[ligne][col] = valeur;
}


///////////////////////////////////////////////////////////// Méthodes interface graphique ///////////////////////////////////////////////

bool Grille::chargerPolice() {
    font = TTF_OpenFont("fonts/BebasNeue-Regular.ttf", 38);
    return font != nullptr;
}


void Grille::dessiner(SDL_Renderer* pRenderer) {
    char texte[3];
    bool actuelle;
    SDL_Color couleur = {0, 255, 0, 255};
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            int x = 175 + j * 50;
            int y = 75 + i * 50;

            if(i == this->ligneActuelle && j == this->colonneActuelle) {
                actuelle = true;
            } else {
                actuelle = false;
            }

            Case caseSudoku(x, y, 49, 49, actuelle);
            caseSudoku.dessiner(pRenderer);

            couleur = {0, 0, 0, 0};

            if (this->grille[i][j] == 0) {
                snprintf(texte, sizeof(texte), "X");
            } else {
                snprintf(texte, sizeof(texte), "%d", this->grille[i][j]);
                couleur = {0, 180, 0, 0};
                if (this->grille[i][j] != this->solution[i][j]) {
                    couleur = {255, 255, 0, 255};
                } 
            }

            SDL_Surface* surface = TTF_RenderText_Blended(this->font, texte, 0, couleur); 
            SDL_Texture* texture = SDL_CreateTextureFromSurface(pRenderer, surface); 
            float texteX = x + (50 - surface->w) / 2.0f;
            float texteY = y + (50 - surface->h) / 2.0f;
            SDL_FRect dest_rect = {texteX, texteY, (float)surface->w, (float)surface->h};
            SDL_DestroySurface(surface); 
            SDL_RenderTexture(pRenderer, texture, nullptr, &dest_rect);
            SDL_DestroyTexture(texture);

            if (!message.empty()) {
                SDL_Color couleur;
                if (messageErreur) {
                    couleur = {255, 0, 0, 255};
                } else {
                    couleur = {0, 255, 0, 255};
                }
                SDL_Surface* surface = TTF_RenderText_Blended(this->font, message.c_str(), 0, couleur);
                SDL_Texture* texture = SDL_CreateTextureFromSurface(pRenderer, surface);
                SDL_FRect dest_rect = {(800 - surface->w) / 2.0f , 540, (float)surface->w, (float)surface->h};
                SDL_DestroySurface(surface);
                SDL_RenderTexture(pRenderer, texture, nullptr, &dest_rect);
                SDL_DestroyTexture(texture);
            }
        }
    }
}

void Grille::deplacerSelection(int directionX, int directionY) {
    colonneActuelle += directionX;
    ligneActuelle += directionY;

    if (colonneActuelle < 0)
        colonneActuelle = 8;
    if (colonneActuelle > 8)
        colonneActuelle = 0;
    if (ligneActuelle < 0)
        ligneActuelle = 8;
    if (ligneActuelle > 8)
        ligneActuelle = 0;
}

bool Grille::modifierCase(int valeur) {
    if (grille[ligneActuelle][colonneActuelle] == solution[ligneActuelle][colonneActuelle]) {
        message = "Cette case contient deja le bon nombre";
        messageErreur = true;
        return false;
    } else if (verifierLigne(ligneActuelle, colonneActuelle, valeur) == false) {
        message = "Chiffre deja present sur la ligne";
        messageErreur = true;
        return false;
    } else if (verifierColonne(colonneActuelle, ligneActuelle, valeur) == false) {
        message = "Chiffre deja present sur la colonne";
        messageErreur = true;
        return false;
    } else if (verifierCarre(ligneActuelle, colonneActuelle, valeur) == false) {
        message = "Chiffre deja present dans le carre";
        messageErreur = true;
        return false;
    } else {
        grille[ligneActuelle][colonneActuelle] = valeur;
        message = "Chiffre ajoute";
        messageErreur = false;
        return true;
    }
}

// Destructeur pour libérer la mémoire
Grille::~Grille() {
    if (font != nullptr) {
        TTF_CloseFont(font);
    }
}