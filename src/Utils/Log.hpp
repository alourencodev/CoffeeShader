#ifndef COFFEE_LOG_HPP
#define COFFEE_LOG_HPP

#include <cstdint>
#include <cstdlib>
#include <string>

namespace coffee::logger
{

struct LogSetting
{
    std::string label;
    std::string color;
};

constexpr char k_defaultColor[] = "";
constexpr char k_yellowColor[] = "\033[33m";
constexpr char k_redColor[] = "\033[31m";

static const LogSetting k_debugLogSetting = {"D", k_defaultColor};
static const LogSetting k_warnLogSetting = {"W", k_yellowColor};
static const LogSetting k_errorLogSetting = {"E", k_redColor};
static const LogSetting k_fatalLogSetting = {"F", k_redColor};

void rawLog(LogSetting setting, 
         const char *file, 
         const uint32_t line, 
         const char *tag, 
         const char *format, 
         ...);
}

#ifdef DEBUG
#define logDebug(tag, ...) logger::rawLog(logger::k_debugLogSetting, __FILE__, __LINE__, tag, __VA_ARGS__)
#else
#define logDebug(tag, ...)
#endif

#define logWarning(tag, ...) logger::rawLog(logger::k_warnLogSetting, __FILE__, __LINE__, tag, __VA_ARGS__)
#define logError(tag, ...) logger::rawLog(logger::k_errorLogSetting, __FILE__, __LINE__, tag, __VA_ARGS__)
#define logFatal(tag, ...) logger::rawLog(logger::k_fatalLogSetting, __FILE__, __LINE__, tag, __VA_ARGS__); \
        std::exit(EXIT_FAILURE) 

#endif