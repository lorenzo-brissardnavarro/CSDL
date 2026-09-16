#include "GameObject.hpp"
#include <iostream>
using namespace std;

// Constructeur liste d'initiation
GameObject::GameObject(int coordonneeX, int coordonneeY, int tailleX, int tailleY)
    : coordonneeX(coordonneeX), coordonneeY(coordonneeY), tailleX(tailleX), tailleY(tailleY)
{
}

Case::Case(int coordonneeX, int coordonneeY, int tailleX, int tailleY)
    : GameObject(coordonneeX, coordonneeY, tailleX, tailleY)
{
}

void Case::dessiner(SDL_Renderer* pRenderer) {
    SDL_FRect caseSudoku;
    caseSudoku.x = this->coordonneeX;
    caseSudoku.y = this->coordonneeY;
    caseSudoku.w = this->tailleX;
    caseSudoku.h = this->tailleY;
    SDL_RenderRect(pRenderer, &caseSudoku);
}
