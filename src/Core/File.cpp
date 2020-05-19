#include "File.hpp"

#include <fstream>
#include <osdialog/osdialog.h>
#include <sstream>

#include "Core/Log.hpp"

namespace coffee::file
{

constexpr char k_logTag[] = "File";

std::string load(const std::string &dir)
{
    std::ifstream file(dir);
        
    if (!file.is_open()) {
        // TODO: Handle this in another way
        logFatal(k_logTag, "Unable to open file %s.", dir);
    }

    std::stringstream buffer;
    buffer << file.rdbuf();

    return buffer.str();  
}

std::string openDialog()
{
    char *filename = osdialog_file(OSDIALOG_OPEN, nullptr, nullptr, nullptr);

    if (filename == nullptr) {
        // TODO: Handle this in another way
        logError(k_logTag, "Unable to open file through dialog.");
        return "";
    }

    auto result = std::string(filename);
    free(filename); // TODO: Get a better way to manage this

    return result;
}

}