#ifndef COFFEE_FILE_WATCHER_HPP
#define COFFEE_FILE_WATCHER_HPP

#include <ctime>
#include <functional>
#include <string>

#include "Utils/Handle.hpp"

namespace coffee::fileWatcher
{

DEFINE_HANDLE(WatchHandle);

WatchHandle watch(const std::string &dir, std::function<void()> event);
void unwatch(WatchHandle handle);
void poll();

}

#endif