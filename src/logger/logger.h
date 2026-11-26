#pragma once

#include <string>
#include <string_view>

namespace Logger {
    void info(std::string_view message);
    void warn(std::string_view message);
    void error(std::string_view message);
    void fatal(std::string_view message);

    void init(const std::string_view fileName, bool needTime);
}