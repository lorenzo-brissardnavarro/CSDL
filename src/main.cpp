#include "Jeu.hpp"
#include "Window.hpp"
#include "GameObject.hpp"
using namespace std;

int main() {

    Window window("Fenêtre SDL", 800, 600);
    window.windowInitialisation();

    Jeu jeu;
    jeu.initialiser();

    SDL_Event events;
    bool ouvert = true;
    

    while (ouvert) {
        while (SDL_PollEvent(&events)) {
            switch (events.type) {
                case SDL_EVENT_QUIT:
                    ouvert = false;
                    break;
                case SDL_EVENT_KEY_DOWN:
                    jeu.gererClavier(events);
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