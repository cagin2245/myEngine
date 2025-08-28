#pragma once
#include <SDL2/SDL.h>

class Input {
public:
    void update() {
        SDL_PumpEvents();
        state = SDL_GetKeyboardState(NULL);
    }

    bool isKeyDown(SDL_Scancode key) const {
        return state[key];
    }

private:
    const Uint8* state = nullptr;
};
