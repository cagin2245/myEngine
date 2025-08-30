#include "Core/Profiler.h"
#include "Core/Logger.h"

namespace Engine {

void Profiler::beginSession(const std::string& name) {
    active = true;
    sessionName = name;
#ifdef ENGINE_DEV_MODE
    Engine::Logger::log(std::string("[Profiler] Session started: ") + name, Engine::LogLevel::Info);
#endif
}

void Profiler::endSession() {
    active = false;
    Engine::Logger::log(std::string("[Profiler] Session ended: ") + sessionName, Engine::LogLevel::Info);
}

void Profiler::logResult(const ProfileResult& result) {
    if (active) {
        auto duration = (result.end - result.start) / 1000.0; // microseconds -> ms
    Engine::Logger::log(std::string("[Profiler] ") + result.name + " took " + std::to_string(duration) + " ms", Engine::LogLevel::Info);
    }
}

ProfileTimer::ProfileTimer(const std::string& name)
    : name(name), startTime(std::chrono::high_resolution_clock::now()) {}

ProfileTimer::~ProfileTimer() {
    if (!stopped) stop();
}

void ProfileTimer::stop() {
    auto endTime = std::chrono::high_resolution_clock::now();
    long long start = std::chrono::time_point_cast<std::chrono::microseconds>(startTime).time_since_epoch().count();
    long long end   = std::chrono::time_point_cast<std::chrono::microseconds>(endTime).time_since_epoch().count();
    Profiler::logResult({ name, start, end });
    stopped = true;
}
void Profiler::beginFrame() {
    frameStart = Clock::now();
}

void Profiler::endFrame() {
    auto frameEnd = Clock::now();
    lastFrameMs = std::chrono::duration<double, std::milli>(frameEnd - frameStart).count();

    // FPS hesaplama
    frameCount++;
    elapsedSec += lastFrameMs / 1000.0;
    if (elapsedSec >= 1.0) {
        fps = frameCount;
        frameCount = 0;
        elapsedSec = 0.0;
    }

    // Min / max / avg
    if (lastFrameMs < minFrameMs) minFrameMs = lastFrameMs;
    if (lastFrameMs > maxFrameMs) maxFrameMs = lastFrameMs;

    avgFrameMs = (avgFrameMs * 0.9) + (lastFrameMs * 0.1); // exponential moving average
}
} // namespace Engine