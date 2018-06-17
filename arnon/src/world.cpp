#include "world.h"

#include "imgui/imgui.h"

void World::update(float dt)
{
    for (auto& gameObject : m_entities)
    {
        gameObject->update(dt);
    }
}

void World::makeUI()
{
    ImGui::Begin("World Management");
    ImGui::Text("Number of Game Objects: #%d", m_entities.size());

    for (auto& gameObject : m_entities)
    {
        gameObject->makeUI();
    }

    if (ImGui::Button("Spawn Game Object"))
    {
        spawn<GameObject>();
    }

    ImGui::End();
}
