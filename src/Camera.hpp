#ifndef COFFEE_CAMERA_HPP
#define COFFEE_CAMERA_HPP

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

namespace coffee
{

struct Camera
{
    glm::vec3 position;
    glm::quat rotation;
    float fieldOfView;
    float aspectRatio;
    float viewNear;
    float viewFar;
};

namespace camera
{

Camera create(const glm::ivec2 &windowSize);
void onWindowResize(Camera *camera, int width, int height);
glm::mat4 viewProjection(const Camera &camera);

}

}

#endif