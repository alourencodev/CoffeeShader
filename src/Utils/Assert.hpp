#ifndef COFFEE_ASSERT_HPP
#define COFFEE_ASSERT_HPP

#include "Log.hpp"

namespace coffee
{

#ifdef DEBUG
#define ASSERT(exp) if (!(exp)) logFatal("Assert", "(%s) is not true.", #exp)
#define ASSERT_MSG(exp, msg, ...) if (!(exp)) logFatal("Assert", msg, __VA_ARGS__)
#else
#define ASSERT(exp) ;
#define ASSERT_MSG(exp, msg, ...) ;
#endif

}

#endif