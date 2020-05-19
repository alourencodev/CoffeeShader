#ifndef COFFEE_UTILS_FILE
#define COFFEE_UTILS_FILE

#include <string>

struct osdialog_filters;

namespace coffee::file
{

std::string load(const std::string &dir);
bool openDialog(std::string *outFileName, osdialog_filters *filters = nullptr);

}

#endif