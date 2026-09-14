#ifndef GRILLE_HPP
#define GRILLE_HPP
#include "json.hpp"

class Grille {

private:

    int grille[9][9];

public:

    Grille();

    nlohmann::json initialiser();
    void remplirGrille(const nlohmann::json& value);
    void afficher();
};

#endif