#include "FileWatcher.hpp"

#include <ctime>
#include <filesystem>

namespace coffee::fileWatcher
{
    
static std::filesystem::path s_registeredPath;
static std::filesystem::file_time_type s_lastTimeModified;
static std::function<void()> s_fileModifiedEvent;

void watch(std::string dir, std::function<void()> event)
{
    s_registeredPath = dir;
    s_fileModifiedEvent = event;
    s_lastTimeModified = std::filesystem::last_write_time(s_registeredPath);
}

void poll()
{
    std::filesystem::file_time_type currentModifiedTime = std::filesystem::last_write_time(s_registeredPath);
    if (currentModifiedTime != s_lastTimeModified) {
        s_lastTimeModified = currentModifiedTime;
        s_fileModifiedEvent();
    }
}

}