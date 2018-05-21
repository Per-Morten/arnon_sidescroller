/// ArnonSidescroller

#ifndef SCENE_H
#define SCENE_H

#include <memory>

class SceneManager;

class Scene
{
private:
    // The owner of this Scene ( CAN NOT BE NULL )
    SceneManager* const m_owner = nullptr;

public:
    // Create a scene and pass a required owner
    explicit Scene(SceneManager& owner);

    // Ask the Scene Manager to push a scene to the stack
    void requestPushScene(std::unique_ptr<Scene> newScene);

    // Ask the Scene Manager to pop the topmost scene from the stack
    void requestPopScene();

    // Update the Scene. Returns true if Scenes below may update while this one is active
    virtual bool update(const float dt) = 0;

};

#endif // SCENE_H
