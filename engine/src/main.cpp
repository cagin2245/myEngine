#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include "Game.h"

int main() {
    Engine::Game game(1920, 1080);
    game.run();
    return 0;
}
