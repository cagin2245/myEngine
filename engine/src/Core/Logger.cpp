#include "Core/Logger.h"

#include <chrono>
#include <ctime>
#include <iomanip>
#include <fstream>
#include <mutex>
#include <sstream>
#include <iostream>

namespace Engine {

namespace {
    std::mutex g_logMutex;
    LogLevel g_minLevel = LogLevel::Info;
#ifdef ENGINE_ADVANCED_LOGGING
    bool g_timestampsEnabled = true;
    std::string g_fileFilter; // substring match on __FILE__
    std::string g_outputPath;
#endif
}

#ifdef ENGINE_ADVANCED_LOGGING
static std::string currentTimestamp() {
    using namespace std::chrono;
    auto now = system_clock::now();
    auto secs = system_clock::to_time_t(now);
    auto ms = duration_cast<milliseconds>(now.time_since_epoch()) % 1000;

    std::ostringstream ss;
    std::tm tm;
#ifdef _WIN32
    localtime_s(&tm, &secs);
#else
    localtime_r(&secs, &tm);
#endif
    ss << std::put_time(&tm, "%Y-%m-%d %H:%M:%S") << '.' << std::setfill('0') << std::setw(3) << ms.count();
    return ss.str();
}
#endif

void Logger::setLogLevel(LogLevel minLevel) {
    std::lock_guard<std::mutex> lk(g_logMutex);
    g_minLevel = minLevel;
}

LogLevel Logger::getLogLevel() {
    std::lock_guard<std::mutex> lk(g_logMutex);
    return g_minLevel;
}

#ifdef ENGINE_ADVANCED_LOGGING
void Logger::enableTimestamps(bool enable) {
    std::lock_guard<std::mutex> lk(g_logMutex);
    g_timestampsEnabled = enable;
}

void Logger::setFileFilter(const std::string& filter) {
    std::lock_guard<std::mutex> lk(g_logMutex);
    g_fileFilter = filter;
}

void Logger::setOutputFile(const std::string& path) {
    std::lock_guard<std::mutex> lk(g_logMutex);
    g_outputPath = path;
}

void Logger::log(const std::string& msg, LogLevel level, const char* file, int line) {
    // Quick level check without locking for performance; fine to have small race here.
    if (static_cast<int>(level) < static_cast<int>(g_minLevel)) return;

    // File filter
    if (!g_fileFilter.empty() && file) {
        std::string sf(file);
        if (sf.find(g_fileFilter) == std::string::npos) return;
    }

    std::ostringstream out;
    if (g_timestampsEnabled) {
        out << currentTimestamp() << ' ';
    }

    switch (level) {
    case LogLevel::Info:    out << "[INFO]  "; break;
    case LogLevel::Warning: out << "[WARN]  "; break;
    case LogLevel::Error:   out << "[ERROR] "; break;
    case LogLevel::Debug:   out << "[DEBUG] "; break;
    }

    if (file) {
        out << '[' << file << ':' << line << "] ";
    }

    out << msg << '\n';

    std::string outStr = out.str();

    std::lock_guard<std::mutex> lk(g_logMutex);
    // Always emit errors to stderr; others to stdout.
    if (level == LogLevel::Error) {
        std::cerr << outStr;
    } else {
        std::cout << outStr;
    }

    if (!g_outputPath.empty()) {
        std::ofstream f(g_outputPath, std::ios::app);
        if (f) f << outStr;
    }
}
#else
void Logger::log(const std::string& msg, LogLevel level, const char* file, int line) {
    // Minimal implementation when advanced logging disabled: simple level check + basic output.
    if (static_cast<int>(level) < static_cast<int>(g_minLevel)) return;
    std::lock_guard<std::mutex> lk(g_logMutex);
    switch (level) {
    case LogLevel::Error:
        std::cerr << "[ERROR] " << msg << '\n';
        break;
    case LogLevel::Warning:
        std::cout << "[WARN] " << msg << '\n';
        break;
    case LogLevel::Debug:
    case LogLevel::Info:
    default:
        std::cout << "[INFO] " << msg << '\n';
        break;
    }
}
#endif

} // namespace Engine
