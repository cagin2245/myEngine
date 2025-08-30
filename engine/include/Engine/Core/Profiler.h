#pragma once
#include <string>
#include <chrono>
#include <iostream>
#include <vector>

namespace Engine
{

    struct ProfileResult
    {
        std::string name;
        long long start, end;
    };

    class Profiler
    {
    public:
        static void beginSession(const std::string &name = "Session");
        static void endSession();
        static void logResult(const ProfileResult &result);
        void beginFrame();
        void endFrame();

        double getLastFrameMs() const { return lastFrameMs; }
        double getAvgFrameMs() const { return avgFrameMs; }
        double getMinFrameMs() const { return minFrameMs; }
        double getMaxFrameMs() const { return maxFrameMs; }
        int getFPS() const { return fps; }

    private:
        static inline bool active = false;
        static inline std::string sessionName;
        using Clock = std::chrono::high_resolution_clock;
        std::chrono::time_point<Clock> frameStart;

        double lastFrameMs = 0.0;
        double avgFrameMs = 0.0;
        double minFrameMs = 1e9;
        double maxFrameMs = 0.0;
        int frameCount = 0;
        double elapsedSec = 0.0;
        int fps = 0;
    };
    class ProfilerSession
    {
    public:
        ProfilerSession(const std::string &name)
        {
            Profiler::beginSession(name);
        }
        ~ProfilerSession()
        {
            Profiler::endSession();
        }
    };

    class ProfileTimer
    {
    public:
        ProfileTimer(const std::string &name);
        ~ProfileTimer();

    private:
        std::string name;
        std::chrono::time_point<std::chrono::high_resolution_clock> startTime;
        bool stopped = false;
        void stop();
    };

} // namespace Engine


#ifdef ENGINE_DEV_MODE
#define PROFILE_SCOPE(name) Engine::ProfileTimer timer##__LINE__(name)
#define PROFILE_FUNCTION() PROFILE_SCOPE(__FUNCTION__)
#else
#define PROFILE_SCOPE(name)
#define PROFILE_FUNCTION()
#endif