#pragma once
#include <SDL2/SDL.h>

namespace Engine {
class Timer {
public:
    Timer() {
        last = SDL_GetPerformanceCounter();
    }

    double getDeltaTime() {
        Uint64 now = SDL_GetPerformanceCounter();
        double dt = (double)(now - last) / (double)SDL_GetPerformanceFrequency();
        last = now;
        return dt;
    }

private:
    Uint64 last;
};
}