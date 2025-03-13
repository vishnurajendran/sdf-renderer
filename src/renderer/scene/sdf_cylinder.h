//
// Created by ssj5v on 11-03-2025.
//

#ifndef SDF_CYLINDER_H
#define SDF_CYLINDER_H
#include "sdf_shape.h"

class SDFCylinder : public SDFShape {
protected:
    SDFShapeType getType() override;
public:
    SDFCylinder(glm::vec3 position, float halfHeight, float radius);
    ~SDFCylinder()=default;
    std::string getName() override { return "Cylinder"; }
    void update(double deltaTime) override;
    void updateDataToShader(unsigned int shaderId) override;
    void drawInspectorGui() override;
};



#endif //SDF_CYLINDER_H
