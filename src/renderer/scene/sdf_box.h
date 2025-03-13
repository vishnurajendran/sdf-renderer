//
// Created by ssj5v on 11-03-2025.
//

#ifndef SDFBOX_H
#define SDFBOX_H
#include "sdf_shape.h"

class SDFBox : public SDFShape{
protected:
    SDFShapeType getType() override;
public:
    SDFBox(glm::vec3 position, glm::vec3 halfExtents);
    ~SDFBox()=default;
    std::string getName() override { return "Box"; }
    void update(double deltaTime) override;
    void updateDataToShader(unsigned int shaderId) override;
    void drawInspectorGui() override;
};

#endif //SDFBOX_H
