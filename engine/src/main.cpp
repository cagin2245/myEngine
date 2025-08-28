#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include "Game.h"

int main() {
    Game game(800, 600);
    game.run();
    return 0;
}
