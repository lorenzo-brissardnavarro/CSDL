#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>

// Classe abstraite
class GameObject {

protected:
    int coordonneeX;
    int coordonneeY;
    int tailleX;
    int tailleY;

public:

    // Constructeur de la classe abstraite
    GameObject(int coordonneeX, int coordonneeY, int tailleX, int tailleY);

    virtual void dessiner(SDL_Renderer* pRenderer) = 0;
};

// Classe enfant point qui hérite de la classe GameObject
class Point : public GameObject {

public:

    Point(int coordonneeX, int coordonneeY, int tailleX, int tailleY);

    void dessiner(SDL_Renderer* pRenderer) override;
};

// Classe enfant case qui hérite de la classe GameObject
class Case : public GameObject {

private:
    bool actuelle;

public:

    Case(int coordonneeX, int coordonneeY, int tailleX, int tailleY, bool actuelle);

    void dessiner(SDL_Renderer* pRenderer) override;
};


// Classe enfant ligne qui hérite de la classe GameObject
class Ligne : public GameObject {

public:

    Ligne(int coordonneeX, int coordonneeY, int tailleX, int tailleY);

    void dessiner(SDL_Renderer* pRenderer) override;
};

#endif