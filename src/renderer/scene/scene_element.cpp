//
// Created by ssj5v on 08-03-2025.
//

#include "scene_element.h"

void SceneElement::update(double deltaTime)
{
    glm::vec3 rotationRad = glm::radians(rotation);
    forward = glm::normalize(glm::vec3(
        -cos(rotationRad.x) * sin(rotationRad.y),
        sin(rotationRad.x),
        -cos(rotationRad.x) * cos(rotationRad.y)
    ));

    right = glm::normalize(glm::cross(forward, glm::vec3(0.0f, 1.0f, 0.0f)));
    up = glm::normalize(glm::cross(right, forward));
}