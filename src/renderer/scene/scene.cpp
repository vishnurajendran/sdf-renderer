//
// Created by ssj5v on 11-03-2025.
//
#include "glad/glad.h"
#include "scene.h"

#include <iostream>

#include "sdf_shape.h"
#include "sdf_sphere.h"
#include "data/SDFShaderDataStruct.h"
#include "sdf_box.h"
#include "sdf_cylinder.h"
#include "glutils/gl_utils.h"

Scene::Scene()
{
    firstTime = true;
    bufferIndex = -1;
    sceneBufferObject = 0;
    cameraRef = new Camera();
    elements.push_back(cameraRef);
    cameraRef->position = glm::vec3(0,0,10);
    cameraRef->rotation = glm::vec3(0,0,0);

    elements.push_back(new SDFSphere(glm::vec3(0,0,0), 0.5));
    elements.push_back(new SDFBox(glm::vec3(1.5,0,0), glm::vec3(0.5f)));
    elements.push_back(new SDFCylinder(glm::vec3(3,0,0), 0.5f, 0.5f));
}

void Scene::initBuffer(unsigned int shaderId)
{
    bufferIndex = glGetUniformBlockIndex(shaderId, "ShapeBlock");
    glUniformBlockBinding(shaderId, bufferIndex, 3);
    glGenBuffers(1, &sceneBufferObject);
    glBindBuffer(GL_UNIFORM_BUFFER, sceneBufferObject);
    glBufferData(GL_UNIFORM_BUFFER, sizeof(SDFShaderDataStruct) * MAX_SCENE_OBJECTS, nullptr, GL_STATIC_DRAW);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
    glBindBufferBase(GL_UNIFORM_BUFFER, 3, sceneBufferObject);
    CheckOpenGLError();
}


void Scene::pushSceneElementsToShader(unsigned int shaderId)
{
    if (firstTime)
    {
        firstTime = false;
        initBuffer(shaderId);
    }

    std::vector<SDFShaderDataStruct> shapesData;
    for (auto& element : elements)
    {
        auto shape = dynamic_cast<SDFShape*>(element);
        if (shape == nullptr)
            continue;

        shapesData.push_back(shape->getDataStruct());
    }

    //just a safe measure
    shapesData.resize(glm::min(static_cast<int>(shapesData.size()), MAX_SCENE_OBJECTS));

    glBindBuffer(GL_UNIFORM_BUFFER, sceneBufferObject);
    glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(SDFShaderDataStruct) * shapesData.size(), shapesData.data());
    glBindBuffer(GL_UNIFORM_BUFFER, 0);

    int sizeLoc = glGetUniformLocation(shaderId, "shapeCount");
    glUniform1i(sizeLoc, static_cast<int>(shapesData.size()));

    if (!CheckOpenGLError())
    {
        std::cerr << "\tObserved at PushToShader (RayShaderData)" << std::endl;
    }
    glFinish();
}

void Scene::update(double deltaTime)
{
    for (const auto& element : elements)
    {
        element->update(deltaTime);
    }
}
