#include "Core/MemoryTracker.h"

#include <sstream>

#ifdef _WIN32
    #define WIN32_LEAN_AND_MEAN
    #include <windows.h>
    #include <psapi.h>
#elif defined(__linux__)
    #include <unistd.h>
    #include <fstream>
#endif

namespace Engine {

std::size_t MemoryTracker::getCurrentUsage() {
#ifdef _WIN32
    PROCESS_MEMORY_COUNTERS_EX pmc;
    if (GetProcessMemoryInfo(GetCurrentProcess(),
                             (PROCESS_MEMORY_COUNTERS*)&pmc,
                             sizeof(pmc))) {
        return static_cast<std::size_t>(pmc.WorkingSetSize);
    }
    return 0;
#elif defined(__linux__)
    std::ifstream statm("/proc/self/statm");
    long rss = 0;
    if (statm.good()) {
        long dummy;
        statm >> dummy >> rss;
        statm.close();
        long page_size_kb = sysconf(_SC_PAGE_SIZE) / 1024;
        return rss * page_size_kb * 1024; // bytes
    }
    return 0;
#else
    return 0; // diğer platformlarda desteklenmiyor
#endif
}

std::string MemoryTracker::getCurrentUsageMB() {
    std::ostringstream oss;
    double mb = getCurrentUsage() / (1024.0 * 1024.0);
    oss << mb << " MB";
    return oss.str();
}

} // namespace Engine
