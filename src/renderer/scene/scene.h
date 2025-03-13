//
// Created by ssj5v on 11-03-2025.
//

#ifndef SCENE_H
#define SCENE_H
#include "Camera.h"
#include "sdf_shape.h"

class Scene
{
    const int MAX_SCENE_OBJECTS = 10;
private:
    std::vector<SceneElement*> elements;
    Camera* cameraRef;
    bool firstTime;

    unsigned int bufferIndex;
    unsigned int sceneBufferObject;
public:
    Scene();
    inline Camera* getCamera() { return cameraRef; }
    inline std::vector<SceneElement*> getElements() { return elements; }
    void pushToShader(unsigned int shaderId);
    void update(double deltaTime);
    void addShape(SDFShapeType shapeType);
    void removeSceneElement(const SceneElement* element);
private:
    void initBuffer(unsigned int shaderId);
};




#endif //SCENE_H
