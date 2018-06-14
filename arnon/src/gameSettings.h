/// ArnonSidescroller
#ifndef GAMESETTINGS_H
#define GAMESETTINGS_H

#include "glm/vec2.hpp"

struct GameSettings
{
    // Whether Vsync is enabled or not
    bool VsyncEnabled = true;
    
    // Resolution of the game window
    glm::ivec2 Resolution = { 1280, 720 };
};


#endif // GAMESETTINGS_H
