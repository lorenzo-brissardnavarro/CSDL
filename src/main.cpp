#include "Jeu.hpp"
#include "Window.hpp"
using namespace std;

int main() {
    // Jeu jeu;
    // jeu.demarrer();
    Window window("Fenêtre SDL", 800, 600);
    window.windowInitialisation();

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
    }
}