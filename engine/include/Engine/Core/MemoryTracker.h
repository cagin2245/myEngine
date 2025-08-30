#pragma once
#include <cstddef>
#include <string>

namespace Engine {

class MemoryTracker {
public:
    // Process tarafından kullanılan RAM (bytes)
    static std::size_t getCurrentUsage();

    // MB olarak helper
    static std::string getCurrentUsageMB();
};

} // namespace Engine