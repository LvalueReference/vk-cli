#ifndef COLOR_HPP
#define COLOR_HPP

#include <string>

namespace reader{
    enum class color{
        CLEAR = 0, BOLD_BLACK = 30, BOLD_GREEN = 32, BOLD_YELLOW = 33, BOLD_BLUE = 34, BOLD_WHITE = 37
    };

    std::string fg(color c);
}

#endif