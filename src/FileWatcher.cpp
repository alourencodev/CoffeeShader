#include "FileWatcher.hpp"

#include <assert.h>
#include <ctime>
#include <filesystem>
#include <vector>

#include "Core/Assert.hpp"
#include "Core/Containers.hpp"

namespace coffee::fileWatcher
{

struct WatchedFile
{
    std::filesystem::path path;
    std::filesystem::file_time_type lastModifiedTime;
    WatchHandle handle;
};

static std::vector<WatchedFile> s_watchedFiles;
static std::vector<onModifiedEvent> s_onModifiedEvents; 
static uint32_t s_currentIdCount = 0;

WatchHandle watch(const std::string &dir, onModifiedEvent event)
{
    WatchedFile file = {dir, std::filesystem::last_write_time(dir), WatchHandle(s_currentIdCount++)};
    s_watchedFiles.emplace_back(file);
    s_onModifiedEvents.emplace_back(event);
    ASSERT(s_watchedFiles.size() == s_onModifiedEvents.size());

    return file.handle;
}

void unwatch(WatchHandle handle)
{
    for (int i = 0; i < s_watchedFiles.size(); i++) {
        if (s_watchedFiles[i].handle == handle) {
            utils::unorderedRemove(s_watchedFiles, s_watchedFiles.begin() + i);
            utils::unorderedRemove(s_onModifiedEvents, s_onModifiedEvents.begin() + i);
        }
    }

    ASSERT(s_watchedFiles.size() == s_onModifiedEvents.size());
}

void poll()
{
    for (int i = 0; i < s_watchedFiles.size(); i++) {
        auto &file = s_watchedFiles[i];
        std::filesystem::file_time_type currentModifiedTime = std::filesystem::last_write_time(file.path);
        if (currentModifiedTime != file.lastModifiedTime) {
            file.lastModifiedTime = currentModifiedTime;
            s_onModifiedEvents[i](s_watchedFiles[i].path.string());
        }
    }
}

}