#include "scene.h"
#include "sceneManager.h"

Scene::Scene(SceneManager& owner) : m_owner(&owner)
{
}

void Scene::requestPushScene(std::unique_ptr<Scene> newScene)
{
    m_owner->pushScene(std::move(newScene));
}

void Scene::requestPopScene()
{
    m_owner->popScene();
}
