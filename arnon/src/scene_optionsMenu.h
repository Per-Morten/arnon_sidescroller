/// ArnonSidescroller

#ifndef SCENE_OPTIONSMENU_H
#define SCENE_OPTIONSMENU_H

#include "scene.h"
#include "debug/arnlog.h"

class SOptionsMenu : public Scene
{
public:
    using Scene::Scene;

    bool update(const float dt) override
    {
        return false;
    }

    std::string getName() const override { return "Options Menu"; }
};

#endif // SCENE_OPTIONSMENU_H
