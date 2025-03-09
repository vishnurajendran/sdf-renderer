//
// Created by ssj5v on 08-03-2025.
//

#ifndef CAMERA_H
#define CAMERA_H
#include "scene_element.h"

class Camera : public SceneElement {
public:
    void updateDataToShader(unsigned int shaderId) override;
    void update(double deltaTime) override;
};

#endif //CAMERA_H
