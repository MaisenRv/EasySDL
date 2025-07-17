#pragma once

#include <string>
#include <sstream>
#include <iomanip>

namespace EasySDL{
    static std::string floatFormat(float value, int precision){
        std::ostringstream oss;
        oss << std::fixed << std::setprecision(precision) << value;
        return oss.str();
    }
}