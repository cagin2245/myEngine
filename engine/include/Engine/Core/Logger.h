enum class LogLevel { Info, Warning, Error, Debug };
#pragma once
#include <string>

namespace Engine {

enum class LogLevel { Info = 0, Warning = 1, Error = 2, Debug = 3 };

class Logger {
public:
    // Basic logging call used throughout the codebase. `file`/`line` are optional and
    // can be provided via the LOG_* macros below.
    static void log(const std::string& msg, LogLevel level = LogLevel::Info, const char* file = nullptr, int line = 0);

    // Configuration helpers
    static void setLogLevel(LogLevel minLevel);
    static LogLevel getLogLevel();

#ifdef ENGINE_ADVANCED_LOGGING
    // Advanced/optional features. Controlled by compile-time flag to avoid
    // runtime overhead when not needed.
    static void enableTimestamps(bool enable);
    // If `filter` is non-empty only logs whose filename contains `filter` will be emitted
    static void setFileFilter(const std::string& filter);
    // If `path` is non-empty logs will also be appended to that file (thread-safe append).
    static void setOutputFile(const std::string& path);
#else
    // Stubs when advanced logging disabled
    static void enableTimestamps(bool) {}
    static void setFileFilter(const std::string&) {}
    static void setOutputFile(const std::string&) {}
#endif
};

// Convenience macros that capture file/line.
#define LOG_INFO(msg)  Engine::Logger::log((msg), Engine::LogLevel::Info,  __FILE__, __LINE__)
#define LOG_WARN(msg)  Engine::Logger::log((msg), Engine::LogLevel::Warning, __FILE__, __LINE__)
#define LOG_ERROR(msg) Engine::Logger::log((msg), Engine::LogLevel::Error, __FILE__, __LINE__)
#define LOG_DEBUG(msg) Engine::Logger::log((msg), Engine::LogLevel::Debug, __FILE__, __LINE__)

} // namespace Engine