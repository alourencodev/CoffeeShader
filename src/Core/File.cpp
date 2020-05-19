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

bool openDialog(std::string *outFileName, osdialog_filters *filters)
{
    char *filename = osdialog_file(OSDIALOG_OPEN, nullptr, nullptr, filters);

    if (filename == nullptr) {
        return false;
    }

    *outFileName = std::string(filename);
    // TODO: Handle memory in a better way. Probably will need to hack submodule
    free(filename);

    return true;
}

}