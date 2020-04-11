#ifndef COFFEE_TRACKBALL_SYSTEM_HPP
#define COFFEE_TRACKBALL_SYSTEM_HPP

namespace coffee
{

struct Camera;

namespace trackball
{

void init(Camera &camera);
void update();

}

}

#endif