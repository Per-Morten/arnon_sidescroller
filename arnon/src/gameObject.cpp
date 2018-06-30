#include "gameObject.h"
#include "debug/arnlog.h"

#include "imgui/imgui.h"

GameObject::GameObject(unsigned ID) : m_ID(ID)
{

}

void GameObject::update(float dt)
{
    for (auto& component : m_components)
    {
        component->update(dt);
    }
}

void GameObject::makeUI()
{
    ImGui::BeginChild("Game Objects", ImVec2(-1.f, 200.f));
    ImGui::Text("#%d - ", m_ID); ImGui::SameLine(0.f, 30.f);

    if (ImGui::Button("Delete"))
    {
        logInfo("Game object {} wants to die!", m_ID);
    }

    ImGui::EndChild();
}
