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
        SDL_RenderPresent(window.getRenderer());

        SDL_Delay(16);
    }
}