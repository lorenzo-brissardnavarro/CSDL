#ifndef GRILLE_HPP
#define GRILLE_HPP
#include "json.hpp"
#include <utility>

class Grille {

private:

    int grille[9][9];
    int solution[9][9];

public:

    Grille();

    std::pair<nlohmann::json, nlohmann::json> initialiser();
    void remplirGrille(const nlohmann::json& value);
    void remplirSolution(const nlohmann::json& value);
    void afficher();
    bool verifierLigne(int ligne, int colActuelle, int valeur);
    bool verifierColonne(int col, int ligneActuelle, int valeur);
    bool verifierCarre(int ligne, int col, int valeur);
    bool grilleComplete();
    int getGrille(int ligne, int col);
    int getSolution(int ligne, int col);
    void setGrille(int ligne, int col, int valeur);
};

#endif