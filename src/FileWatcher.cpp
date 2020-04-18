#include "FileWatcher.hpp"

#include <ctime>
#include <filesystem>
#include <vector>

namespace coffee::fileWatcher
{
    
struct WatchedFile
{
    std::filesystem::path path;
    std::filesystem::file_time_type lastModifiedTime; 
};

static std::vector<WatchedFile> s_watchedFiles;
static std::vector<std::function<void()>> s_onModifiedEvents; 

void watch(std::string dir, std::function<void()> event)
{
    WatchedFile file = {dir, std::filesystem::last_write_time(dir)};
    s_watchedFiles.emplace_back(file);
    s_onModifiedEvents.emplace_back(event);

    // TODO: Assert that they keep with the same size
}

// TODO: Unwatch

void poll()
{
    for (int i = 0; i < s_watchedFiles.size(); i++) {
        auto &file = s_watchedFiles[i];
        std::filesystem::file_time_type currentModifiedTime = std::filesystem::last_write_time(file.path);
        if (currentModifiedTime != file.lastModifiedTime) {
            file.lastModifiedTime = currentModifiedTime;
            s_onModifiedEvents[i]();
        }
    }
}

}