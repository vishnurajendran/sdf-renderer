//
// Created by ssj5v on 11-03-2025.
//

#ifndef SCENE_H
#define SCENE_H
#include "camera.h"
#include "sdf_shape.h"

class Scene
{
    //Limit the shapes for performance
    const int MAX_SCENE_OBJECTS = 30;
private:
    std::vector<SceneElement*> elements;
    Camera* cameraRef;
    bool firstTime;

    unsigned int bufferIndex;
    unsigned int sceneBufferObject;
    unsigned int shapesInScene;

public:
    Scene();
    inline Camera* getCamera() { return cameraRef; }
    inline std::vector<SceneElement*> getElements() { return elements; }
    [[nodiscard]] bool maxShapesLimitReached() const {return shapesInScene >= MAX_SCENE_OBJECTS;}

    void pushToShader(unsigned int shaderId);
    void update(double deltaTime);
    void addShape(SDFShapeType shapeType);
    void removeSceneElement(SceneElement* element);
private:
    void initBuffer(unsigned int shaderId);
};




#endif //SCENE_H
