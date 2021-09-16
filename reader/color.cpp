#include "color.hpp"
#include "fmt/format.h"

std::string reader::fg(reader::color c){
    return fmt::format("\033[1;{}m", c);
}