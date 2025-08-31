#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include "Core/Profiler.h"
#include "Game.h"

#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080

int main() {
    Engine::Profiler::beginSession("Main Session");
    
        Engine::Game game(SCREEN_WIDTH, SCREEN_HEIGHT);
        game.run();
        return 0;
    

    

}
