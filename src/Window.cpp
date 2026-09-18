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
    
    if (!TTF_Init()) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[DEBUG] > %s", SDL_GetError());
        return EXIT_FAILURE;
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

// Getter pour récupérer le pointeur
SDL_Window* Window::getWindow(){
    return this->pWindow;
}


// Destructeur pour libérer la mémoire
Window::~Window() {
    if (pRenderer != nullptr) {
        SDL_DestroyRenderer(pRenderer);
    }
    if (pWindow != nullptr) {
        SDL_DestroyWindow(pWindow);
    }
    TTF_Quit();
    SDL_Quit();
}


