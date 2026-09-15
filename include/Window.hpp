#ifndef WINDOW_HPP
#define WINDOW_HPP
#include <string>
#include <SDL3/SDL.h>

class Window {

private:

    std::string titre;
    int largeur;
    int hauteur;
    SDL_Window* pWindow;
    SDL_Renderer* pRenderer;

public:

    Window(std::string titre, int largeur, int hauteur);

    bool windowInitialisation();
};

#endif