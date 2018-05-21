/// ArnonSidescroller

#ifndef SCENE_MAINMENU_H
#define SCENE_MAINMENU_H

#include "scene.h"
#include "debug/arnlog.h"

class SMainMenu : public Scene
{
public:
    using Scene::Scene;

    virtual bool update(const float dt) override
    {

        return false;
    }
};

#endif // SCENE_MAINMENU_H
