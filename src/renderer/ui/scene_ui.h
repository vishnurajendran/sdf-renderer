//
// Created by ssj5v on 12-03-2025.
//

#ifndef UI_LAYER_H
#define UI_LAYER_H
#include "renderer/scene/scene.h"

class SceneUI {
private:
    Scene* ctxScene = nullptr;
    SceneElement* selected = nullptr;
public:
    SceneUI()=default;
    ~SceneUI()=default;
    void init(Scene* scene);
    void draw();
private:
    void drawSelector();
    void drawShapeDetails();
    void drawControls();
    void setSelectedToLast();
};

#endif //UI_LAYER_H
