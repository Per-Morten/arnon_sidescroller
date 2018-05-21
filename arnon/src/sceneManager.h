/// ArnonSidescroller

#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include "scene.h"

#include <vector>
#include <stack>

class SceneManager
{
private:
    // The stack of active Scenes
    std::stack<Scene, std::vector> m_sceneStack;

public:

    template<typename SceneType>
    void pushScene(const Scene& newScene);

    void popScene();

};

#endif // SCENEMANAGER_H
