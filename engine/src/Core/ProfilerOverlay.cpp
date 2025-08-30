#include "ProfilerOverlay.h"
#include <SDL2/SDL.h>
#include <iostream>

using namespace Engine;

void ProfilerOverlay::render() {
#ifdef ENGINE_DEV_MODE
    std::cout 
        << "FPS: " << profiler.getFPS()
        << " | Frame: " << profiler.getLastFrameMs() << "ms"
        << " | Avg: " << profiler.getAvgFrameMs() << "ms"
        << " | Min: " << profiler.getMinFrameMs() << "ms"
        << " | Max: " << profiler.getMaxFrameMs() << "ms"
        << std::endl;
#endif
}
