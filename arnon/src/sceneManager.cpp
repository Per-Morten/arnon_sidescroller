#include "sceneManager.h"
#include "scene_mainMenu.h"
#include "scene_optionsMenu.h"

#include "imgui/imgui.h"

void SceneManager::pushScene(std::unique_ptr<Scene> newScene)
{
    m_pendingCommands.push_back({std::move(newScene), ESCeneCommandType::Push});
}

void SceneManager::popScene() { m_pendingCommands.push_back({nullptr, ESCeneCommandType::Pop}); }

void SceneManager::update(const float dt)
{
    // Update All Scenes
    for (auto& scene : m_sceneStack)
    {
        if (!scene->update(dt))
            break;
    }

    // Process Commands
    for (auto& cmd : m_pendingCommands)
    {
        switch (cmd.commandType)
        {
        case ESCeneCommandType::Push: m_sceneStack.emplace_front(std::move(cmd.newScene)); break;
        case ESCeneCommandType::Pop: m_sceneStack.pop_front(); break;
        default: break;
        }
    }

    m_pendingCommands.clear();
}

void SceneManager::makeUI()
{
    ImGui::Begin("Scene Management");

    ImGui::Text("SCENE STACK:");
    for (const auto& scene : m_sceneStack)
    {
        ImGui::Text("  %s", scene->getName().c_str());
    }

    // Scene selector
    static int selection = 0;
    static const char* selections[2] = {"Main Menu", "Options Menu"};
    ImGui::Combo("Scene Selector", &selection, selections, 2);

    // Add / Remove Scenes
    if (ImGui::Button("Push"))
    {
        if (selection == 0)
        {
            pushScene(std::make_unique<SMainMenu>(*this));
        }
        else if (selection == 1)
        {
            pushScene(std::make_unique<SOptionsMenu>(*this));
        }
    }
    ImGui::SameLine();
    if (ImGui::Button("Pop"))
    {
        popScene();
    }

    ImGui::End();
}
