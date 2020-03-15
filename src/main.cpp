#include "Context.hpp"

using namespace coffee;

int main()
{
    context::init();

    while (context::update()) {
    }

    context::terminate();

    return 0;
}