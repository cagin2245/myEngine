#include "ProfilerOverlay.h"
#include <sstream>

namespace Engine
{

    ProfilerOverlay::ProfilerOverlay(Profiler &profiler, std::shared_ptr<TextRenderer> textRenderer)
        : profiler(profiler), textRenderer(std::move(textRenderer)) {}

    void ProfilerOverlay::render(int x, int y)
    {
#ifdef ENGINE_DEV_MODE
        std::stringstream ss;
        ss << "FPS: " << profiler.getFPS()
           << " | Frame: " << profiler.getLastFrameMs() << "ms"
           << " | Avg: " << profiler.getAvgFrameMs() << "ms";

        textRenderer->renderText(ss.str(), (float)x, (float)y, 1.0f, glm::vec3(1.0f, 1.0f, 0.0f));
        std::string mem = "Memory: " + MemoryTracker::getCurrentUsageMB();
        textRenderer->renderText(mem, (float)x, (float)(y + 20), 1.0f, glm::vec3(0.5f, 1.0f, 0.5f));
#endif
    }

}
