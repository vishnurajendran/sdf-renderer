//
// Created by ssj5v on 08-03-2025.
//

#ifndef SCENE_ELEMENT_H
#define SCENE_ELEMENT_H
#include <string>

#include "glm/glm.hpp"


class SceneElement {
public:
    virtual ~SceneElement() = default;
    virtual std::string getName() = 0;
    virtual void drawInspectorGui() = 0;
    virtual void updateDataToShader(unsigned int shaderId)=0;
    virtual void update(double deltaTime);
public:
    alignas(16) glm::vec3 position;
    alignas(16) glm::vec3 rotation;
    glm::vec3 forward;
    glm::vec3 up;
    glm::vec3 right;
};



#endif //SCENE_ELEMENT_H
