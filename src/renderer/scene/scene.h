//
// Created by ssj5v on 11-03-2025.
//

#ifndef SCENE_H
#define SCENE_H
#include "Camera.h"

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
    void pushSceneElementsToShader(unsigned int shaderId);
    void update(double deltaTime);
private:
    void initBuffer(unsigned int shaderId);
};



#endif //SCENE_H
