//
// Created by ssj5v on 12-03-2025.
//

#include "scene_ui.h"

#include <imgui.h>
#include <imgui_internal.h>
#include <ranges>

#include "renderer/scene/sdf_sphere.h"

void SceneUI::init(Scene* scene)
{
    ctxScene = scene;
}

void SceneUI::draw()
{
    ImGui::Begin("SDF Renderer");
    drawSelector();
    drawControls();
    drawShapeDetails();
    ImGui::End();
}

void SceneUI::drawSelector()
{
    SceneElement* elementToRemove = nullptr;
    std::string title = "Scene (" + std::to_string(ctxScene->getElements().size())+")";
    ImGui::SetNextItemOpen(true, ImGuiCond_Always);
    if (ImGui::CollapsingHeader(title.c_str()))
    {
        ImGui::SetNextItemOpen(true, ImGuiCond_Always);
        if (ImGui::TreeNode("Root"))
        {
            int bttnId = 999;
            for (auto element : ctxScene->getElements())
            {
                //Tree item
                ImGui::PushID(element);
                ImGui::SetNextItemAllowOverlap();
                if (ImGui::Selectable(element->getName().c_str(), selected == element))
                {
                    selected = element;
                }
                ImGui::PopID();

                //close button
                auto shape = dynamic_cast<SDFShape*>(element);
                if (!shape)
                    continue;

                //Close button
                bttnId++;
                ImGui::SameLine();
                ImGui::SetCursorPosX(ImGui::GetWindowWidth() - 20);
                ImGui::PushID(bttnId);
                ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(1, 0, 0, 0));
                if (ImGui::Button("X", ImVec2(15, 15)))
                {
                    elementToRemove = element;
                }
                ImGui::PopStyleColor();
                ImGui::PopID();
            }
            ImGui::TreePop();
        }
    }

    if (elementToRemove != nullptr)
    {
        ctxScene->removeSceneElement(elementToRemove);
    }
}

void SceneUI::drawShapeDetails()
{
    if (selected == nullptr)
        return;

    if (ImGui::CollapsingHeader("Details"))
    {
        ImGui::Text("Position");
        ImGui::Text("X:");
        ImGui::SameLine();
        ImGui::SetNextItemWidth(50);
        ImGui::DragFloat("##LocX", &selected->position.x, 0.01f);
        ImGui::SameLine();
        ImGui::Text("Y:");
        ImGui::SameLine();
        ImGui::SetNextItemWidth(50);
        ImGui::DragFloat("##LocY", &selected->position.y,0.01f);
        ImGui::SameLine();
        ImGui::Text("Z:");
        ImGui::SameLine();
        ImGui::SetNextItemWidth(50);
        ImGui::DragFloat("##LocZ", &selected->position.z, 0.01f);
        ImGui::NewLine();

        ImGui::Text("Rotation");
        ImGui::Text("X:");
        ImGui::SameLine();
        ImGui::SetNextItemWidth(50);
        ImGui::DragFloat("##RotX", &selected->rotation.x, 0.01f);
        ImGui::SameLine();
        ImGui::Text("Y:");
        ImGui::SameLine();
        ImGui::SetNextItemWidth(50);
        ImGui::DragFloat("##RotY", &selected->rotation.y,0.01f);
        ImGui::SameLine();
        ImGui::Text("Z:");
        ImGui::SameLine();
        ImGui::SetNextItemWidth(50);
        ImGui::DragFloat("##RotZ", &selected->rotation.z, 0.01f);
        ImGui::NewLine();

        selected->drawInspectorGui();
    }
}

void SceneUI::drawControls()
{
    //Don't allow any more additions
    auto disabled = ctxScene->maxShapesLimitReached();
    if (disabled)
    {
        ImGui::PushItemFlag(ImGuiItemFlags_Disabled, true);
        ImGui::PushStyleVar(ImGuiStyleVar_Alpha, ImGui::GetStyle().Alpha * 0.5f);
    }

    ImGui::SetNextItemOpen(true, ImGuiCond_Always);
    if (ImGui::CollapsingHeader("Add Shapes"))
    {
        if (ImGui::Button("Add Sphere")) {
            ctxScene->addShape(SDFShapeType::Sphere);
            setSelectedToLast();
        }
        ImGui::SameLine();
        if (ImGui::Button("Add Box"))
        {
            ctxScene->addShape(SDFShapeType::Box);
            setSelectedToLast();
        }
        ImGui::SameLine();
        if (ImGui::Button("Add Cylinder"))
        {
            ctxScene->addShape(SDFShapeType::Cylinder);
            setSelectedToLast();
        }
    }

    if (disabled)
    {
        ImGui::PopItemFlag();
        ImGui::PopStyleVar();
    }
}

void SceneUI::setSelectedToLast()
{
    selected = ctxScene->getElements().at(ctxScene->getElements().size()-1);
}
