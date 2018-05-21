/// ArnonSidescroller

#ifndef SCENE_OPTIONSMENU_H
#define SCENE_OPTIONSMENU_H

#include "scene.h"
#include "debug/arnlog.h"

class SOptionsMenu : public Scene
{
public:
    using Scene::Scene;

    virtual bool update(const float dt) override
    {
        logInfo("This is the OPTIONS MENU scene updating!");
        return false;
    }
};

#endif // SCENE_OPTIONSMENU_H
