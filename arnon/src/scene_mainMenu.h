/// ArnonSidescroller

#ifndef SCENE_MAINMENU_H
#define SCENE_MAINMENU_H

#include "world.h"
#include "scene.h"
#include "debug/arnlog.h"

class SMainMenu : public Scene
{
private:
    // The world
    World m_world;

public:
    using Scene::Scene;

    virtual bool update(const float dt) override
    {
        m_world.update(dt);
        m_world.makeUI();
        return false;
    }
};

#endif // SCENE_MAINMENU_H
