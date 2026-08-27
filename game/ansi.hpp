#pragma once

#include <string>
#include <string_view>

namespace ansi {
    inline constexpr std::string_view RESET = "\033[0m";
    inline constexpr std::string_view BLOCK = "\xE2\x96\x88"; // █

    namespace fg {
        inline constexpr std::string_view BLACK   = "\033[30m";
        inline constexpr std::string_view RED     = "\033[31m";
        inline constexpr std::string_view GREEN   = "\033[32m";
        inline constexpr std::string_view YELLOW  = "\033[33m";
        inline constexpr std::string_view BLUE    = "\033[34m";
        inline constexpr std::string_view MAGENTA = "\033[35m";
        inline constexpr std::string_view CYAN    = "\033[36m";
        inline constexpr std::string_view WHITE   = "\033[37m";
    }

    namespace bg {
        inline constexpr std::string_view BLACK   = "\033[40m";
        inline constexpr std::string_view RED     = "\033[41m";
        inline constexpr std::string_view GREEN   = "\033[42m";
        inline constexpr std::string_view YELLOW  = "\033[43m";
        inline constexpr std::string_view BLUE    = "\033[44m";
        inline constexpr std::string_view MAGENTA = "\033[45m";
        inline constexpr std::string_view CYAN    = "\033[46m";
        inline constexpr std::string_view WHITE   = "\033[47m";
    }
}
