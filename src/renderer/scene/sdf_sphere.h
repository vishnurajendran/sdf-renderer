//
// Created by ssj5v on 11-03-2025.
//

#ifndef SDFSPHERE_H
#define SDFSPHERE_H
#include "sdf_shape.h"


class SDFSphere : public SDFShape {
protected:
    SDFShapeType getType() override;
public:
    SDFSphere(glm::vec3 position, float radius);
    ~SDFSphere()=default;
    void update(double deltaTime) override;
    void updateDataToShader(unsigned int shaderId) override;
};



#endif //SDFSPHERE_H
