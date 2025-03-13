//
// Created by ssj5v on 08-03-2025.
//

#ifndef CAMERA_H
#define CAMERA_H
#include "scene_element.h"

class Camera : public SceneElement {
private:
    float farClip = 100.0f;
public:
    std::string getName() override { return "Camera"; }
    void updateDataToShader(unsigned int shaderId) override;
    void update(double deltaTime) override;
    void drawInspectorGui() override;
};

#endif //CAMERA_H
