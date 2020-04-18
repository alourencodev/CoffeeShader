#ifndef COFFEE_FILE_WATCHER_HPP
#define COFFEE_FILE_WATCHER_HPP

#include <ctime>
#include <functional>
#include <string>

namespace coffee::fileWatcher
{

void watch(std::string dir, std::function<void()> event);
void poll();

}

#endif