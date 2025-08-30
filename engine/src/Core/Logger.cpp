#include "Core/Logger.h"

namespace Engine {

void Logger::log(const std::string& msg, LogLevel level) {
    switch (level) {
        case LogLevel::Info:    std::cout << "[INFO] " << msg << std::endl; break;
        case LogLevel::Warning: std::cout << "[WARN] " << msg << std::endl; break;
        case LogLevel::Error:   std::cerr << "[ERROR] " << msg << std::endl; break;
#ifdef ENGINE_DEV_MODE
        case LogLevel::Debug:   std::cout << "[DEBUG] " << msg << std::endl; break;
#endif
    }
}

}
