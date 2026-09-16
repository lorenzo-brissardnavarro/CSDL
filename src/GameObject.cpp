#include "GameObject.hpp"
#include <iostream>
using namespace std;

// Constructeur liste d'initiation
GameObject::GameObject(int coordonneeX, int coordonneeY, int tailleX, int tailleY)
    : coordonneeX(coordonneeX), coordonneeY(coordonneeY), tailleX(tailleX), tailleY(tailleY)
{
}

Rectangle::Rectangle(int coordonneeX, int coordonneeY, int tailleX, int tailleY)
    : GameObject(coordonneeX, coordonneeY, tailleX, tailleY)
{
}

void Rectangle::dessiner(SDL_Renderer* pRenderer) {
    SDL_FRect rectangle;
    rectangle.x = this->coordonneeX;
    rectangle.y = this->coordonneeY;
    rectangle.w = this->tailleX;
    rectangle.h = this->tailleY;
    SDL_RenderFillRect(pRenderer, &rectangle);
}
