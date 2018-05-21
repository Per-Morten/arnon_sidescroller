#include "sceneManager.h"

void SceneManager::pushScene(std::unique_ptr<Scene> newScene)
{
    m_pendingCommands.push_back({ std::move(newScene), ESCeneCommandType::Push });
}

void SceneManager::popScene()
{
    m_pendingCommands.push_back({ nullptr, ESCeneCommandType::Pop });
}

void SceneManager::update(const float dt)
{
    // Update All Scenes
    for (auto& scene : m_sceneStack)
    {
        if (!scene->update(dt)) break;
    }

    // Process Commands
    for (auto& cmd : m_pendingCommands)
    {
        switch (cmd.commandType)
        {
        case ESCeneCommandType::Push:
            m_sceneStack.emplace_front(std::move(cmd.newScene));
            break;
        case ESCeneCommandType::Pop:
            m_sceneStack.pop_front();
            break;
        default:
            break;
        }
    }

    m_pendingCommands.clear();
}
