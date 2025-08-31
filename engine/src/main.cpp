#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include "Core/Profiler.h"
#include "Game.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
int main() {
    Engine::Profiler::beginSession("Main Session");
    
        Engine::Game game(SCREEN_WIDTH, SCREEN_HEIGHT);
        game.run();
        return 0;
    

    

}
