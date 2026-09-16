#include "Jeu.hpp"
#include "Window.hpp"
#include "GameObject.hpp"
using namespace std;

int main() {
    // Jeu jeu;
    // jeu.demarrer();
    Window window("Fenêtre SDL", 800, 600);
    window.windowInitialisation();

    Rectangle caseTest(100, 100, 50, 50);

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
        caseTest.dessiner(window.getRenderer());
        SDL_RenderPresent(window.getRenderer());
    }
}