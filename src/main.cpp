#include "Jeu.hpp"
#include "Window.hpp"
#include "GameObject.hpp"
using namespace std;

int main() {

    Window window("Fenêtre SDL", 800, 600);
    window.windowInitialisation();

    Jeu jeu;

    SDL_Event events;
    bool isOpen = true;

    TTF_Font* font = TTF_OpenFont("fonts/BebasNeue-Regular.ttf", 38);
    SDL_Surface* surface = TTF_RenderText_Blended( font, "Hello world", 0, {0, 255, 0, 255} ); 
    SDL_Texture* texture = SDL_CreateTextureFromSurface(window.getRenderer(), surface); 
    SDL_DestroySurface(surface); 
    

    while (isOpen) {
        while (SDL_PollEvent(&events)) {
            switch (events.type) {
                case SDL_EVENT_QUIT:
                    isOpen = false;
                    break;
            }
        }
        SDL_SetRenderDrawColor(window.getRenderer(), 255, 255, 255, 255);
        SDL_RenderClear(window.getRenderer());

        SDL_SetRenderDrawColor(window.getRenderer(), 0, 0, 0, 0);
        jeu.demarrerInterface(window.getRenderer());

        // Affichage du texte 
        SDL_FRect destination = { 250.0f, 270.0f, 300.0f, 60.0f }; 
        SDL_RenderTexture(window.getRenderer(), texture, nullptr, &destination);

        SDL_RenderPresent(window.getRenderer());

        SDL_Delay(16);
    }

    SDL_DestroyTexture(texture); 
    TTF_CloseFont(font);
}