#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include "Core/Profiler.h"
#include "Game.h"

int main() {
    Engine::Profiler::beginSession("Main Session");
    
        Engine::Game game(800, 600);
        game.run();
        return 0;
    

    

}
