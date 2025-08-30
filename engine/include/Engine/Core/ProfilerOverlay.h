#pragma once
#include "Profiler.h"

namespace Engine {

class ProfilerOverlay {
public:
    ProfilerOverlay(Profiler& profiler) : profiler(profiler) {}

    void render();

private:
    Profiler& profiler;
};

}