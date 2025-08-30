#pragma once
#include <string>
#include <iostream>

namespace Engine {

enum class LogLevel { Info, Warning, Error, Debug };

class Logger {
public:
    static void log(const std::string& msg, LogLevel level = LogLevel::Info);
};

}