/// ArnonSidescroller

#ifndef SCENE_H
#define SCENE_H

class SceneManager;

class Scene
{
private:
    // The owner of this Scene
    SceneManager* m_owner = nullptr;

public:
    // Create a scene and pass a required owner
    explicit Scene(const SceneManager& owner);

    // Ask the Scene Manager to push a scene to the stack
    void requestPushScene(const Scene& newScene);

    // Ask the Scene Manager to pop the topmost scene from the stack
    void requestPopScene();

};

#endif // SCENE_H
