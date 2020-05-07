#include "File.hpp"

#include <osdialog/osdialog.h>

#include "Utils/Log.hpp"

namespace coffee::file
{

std::string openDialog()
{
    char *filename = osdialog_file(OSDIALOG_OPEN, nullptr, nullptr, nullptr);

    if (filename == nullptr) {
        logError("File", "Unable to open file through dialog.");
        return "";
    }

    auto result = std::string(filename);
    free(filename); // TODO: Get a better way to manage this

    return result;
}

}