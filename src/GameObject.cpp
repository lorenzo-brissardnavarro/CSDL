#include "GameObject.hpp"
#include <iostream>
using namespace std;

// Constructeur liste d'initiation
GameObject::GameObject(int coordonneeX, int coordonneeY, int tailleX, int tailleY)
    : coordonneeX(coordonneeX), coordonneeY(coordonneeY), tailleX(tailleX), tailleY(tailleY)
{
}

Case::Case(int coordonneeX, int coordonneeY, int tailleX, int tailleY, bool actuelle)
    : GameObject(coordonneeX, coordonneeY, tailleX, tailleY),
    actuelle(actuelle)
{
}


void Case::dessiner(SDL_Renderer* pRenderer) {
    SDL_FRect caseSudoku = {(float)this->coordonneeX, (float)this->coordonneeY, (float)this->tailleX, (float)this->tailleY};
    if (this->actuelle) {
        SDL_SetRenderDrawColor(pRenderer, 210, 210, 210, 255);
        SDL_RenderFillRect(pRenderer, &caseSudoku);
    } else {
        SDL_SetRenderDrawColor(pRenderer, 0, 0, 0, 0);
        SDL_RenderRect(pRenderer, &caseSudoku);
    }
}
