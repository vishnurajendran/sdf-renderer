//
// Created by ssj5v on 11-03-2025.
//

#ifndef SDF_SHAPE_H
#define SDF_SHAPE_H
#include "scene_element.h"
#include "data/SDFShaderDataStruct.h"

enum SDFShapeType
{
    None = 0,
    Sphere=1,
    Box=2,
    Cylinder=3
};

class SDFShape : public SceneElement {
protected:
    SDFShaderDataStruct shaderDataStruct;
    virtual SDFShapeType getType()=0;
public:
    SDFShaderDataStruct getDataStruct();
    void updateDataToShader(unsigned int shaderId) override;
    void update(double deltaTime) override;
};



#endif //SDF_SHAPE_H
