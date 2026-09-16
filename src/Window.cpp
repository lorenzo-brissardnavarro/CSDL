#include "Window.hpp"
#include <iostream>
#include <string>
using namespace std;


// Constructeur liste d'initiation
Window::Window(std::string titre, int largeur, int hauteur)
    : titre(titre), largeur(largeur), hauteur(hauteur), pWindow(nullptr), pRenderer(nullptr)
{
}

// Méthode pour initialiser la fenêtre
bool Window::windowInitialisation() {
    if (!SDL_Init(SDL_INIT_VIDEO)) {         
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[DEBUG] > %s", SDL_GetError());         
        return false;     
    }       

    pWindow = SDL_CreateWindow(this->titre.c_str(), this->largeur, this->hauteur, 0);       
    if (pWindow == nullptr) {         
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[DEBUG] > %s", SDL_GetError());         
        SDL_Quit();         
        return false;     
    }
    
    pRenderer = SDL_CreateRenderer(pWindow, NULL);       
    if (pRenderer == nullptr) {         
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[DEBUG] > %s", SDL_GetError());         
        SDL_Quit();         
        return false;     
    }
    return true;     
}

// Getter pour récupérer le pointeur
SDL_Renderer* Window::getRenderer(){
    return this->pRenderer;
}
