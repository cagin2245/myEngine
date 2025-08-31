#pragma once
#include "Profiler.h"
#include "TextRenderer.h"
#include "MemoryTracker.h"
#include <memory>
#include <array>

namespace Engine {

class ProfilerOverlay {
public:
    ProfilerOverlay(Profiler& profiler, std::shared_ptr<TextRenderer> textRenderer);
    void render(int x = 10, int y = 30, std::array<int,2> resolution = {0,0});

private:
    Profiler& profiler;
    std::shared_ptr<TextRenderer> textRenderer;
};

}