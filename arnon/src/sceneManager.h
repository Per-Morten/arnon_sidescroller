/// ArnonSidescroller

#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include "scene.h"

#include <memory>
#include <cstdint>
#include <vector>
#include <queue>
#include <stack>

// Declares what the command represents
enum class ESCeneCommandType : uint8_t
{
    Nothing,
    Push,
    Pop
};

class SceneManager
{
private:
    // Defines a command and it's data to be executed at a later time
    struct Command
    {
        // Used when Command is Push
        std::unique_ptr<Scene> newScene = nullptr;

        // The command to execute
        ESCeneCommandType commandType = ESCeneCommandType::Nothing;
    };

    // The stack of active Scenes
    std::stack<std::unique_ptr<Scene>, std::vector<std::unique_ptr<Scene>>> m_sceneStack;
    
    // A queue of Commands to be executed after the next update
    std::queue<Command> m_pendingCommands;

public:

    // Push a new scene onto the Scene Stack
    void pushScene(std::unique_ptr<Scene> newScene);

    // Pop the top scene off the Scene Stack
    void popScene();

};

#endif // SCENEMANAGER_H
