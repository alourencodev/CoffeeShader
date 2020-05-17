#include "Log.hpp"

#include <cstdarg>
#include <cstdio>
#include <iostream>

namespace coffee::logger
{

constexpr uint16_t k_maxLogSize = 256;
constexpr char k_resetColor[] = "\033[0m";

void rawLog(LogSetting setting, const char *file, const uint32_t line, const char *tag, const char *format, ...)
{
    char buffer[k_maxLogSize];
    va_list args;
    va_start(args, format);
    vsnprintf(buffer, k_maxLogSize, format, args);
    va_end(args);

    std::cout << setting.color << file << ":" << line << " " << setting.label << " [" << tag << "] - " 
              << buffer << k_resetColor << std::endl;
}

}