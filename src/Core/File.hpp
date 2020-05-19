#ifndef COFFEE_UTILS_FILE
#define COFFEE_UTILS_FILE

#include <string>

namespace coffee::file
{

std::string load(const std::string &dir);
bool openDialog(std::string *outFileName);

}

#endif