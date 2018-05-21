#include "sceneManager.h"

void SceneManager::pushScene(std::unique_ptr<Scene> newScene)
{
    m_pendingCommands.push({ std::move(newScene), ESCeneCommandType::Push });
}

void SceneManager::popScene()
{
    m_pendingCommands.push({ nullptr, ESCeneCommandType::Pop });
}

void SceneManager::update(const float dt)
{
    for (auto& scene : m_sceneStack)
    {
        if (!scene->update(dt)) break;
    }
}
