//
// Created by ssj5v on 08-03-2025.
//

#include "scene_element.h"

void SceneElement::update(double deltaTime)
{
    forward = normalize(glm::vec3(
        cos(rotation.y) * sin(rotation.x),  // X component (Yaw applied)
        sin(rotation.y),                    // Y component (Pitch applied)
    -cos(rotation.y) * cos(rotation.x)   // Z component (Yaw & Pitch applied)
    ));

    right = normalize(cross(forward, glm::vec3(0.0f, 1.0f, 0.0f))); // Perpendicular to forward & world-up
    up = normalize(cross(right, forward)); // Perpendicular to forward & right
}
