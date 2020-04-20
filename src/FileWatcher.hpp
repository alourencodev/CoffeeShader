#ifndef COFFEE_FILE_WATCHER_HPP
#define COFFEE_FILE_WATCHER_HPP

#include <ctime>
#include <functional>
#include <string>

namespace coffee::fileWatcher
{

using WatchHandle = uint32_t;   // TODO: Make this hardly typed

WatchHandle watch(const std::string &dir, std::function<void()> event);
void unwatch(WatchHandle handle);
void poll();

}

#endif