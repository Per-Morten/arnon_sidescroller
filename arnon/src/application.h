/// ArnonSidescroller

#ifndef APPLICATION_H
#define APPLICATION_H

#include "window.h"
#include "sceneManager.h"
#include "gameSettings.h"

struct ImGuiContext;

/*!
 * \brief The Application is the outermost wrapper for the
 * entire program, containing the main game loop, the SceneManager
 * and other program wide concepts and settings.
 * \note It assumes that GLFW has been initialized already.
 */
class Application final
{
private:
    // The options / settings
    GameSettings m_settings;

    // The window on screen
    Window m_window{ { 1280, 720 }, "Test" };

    // The scene manager
    SceneManager m_sceneManager;

    // Pointer to the imgui context assosciated with this application
    ImGuiContext* m_imguiContext;

public:
    Application();

    ~Application();

    void run();

private:
    // Defined to allow a set of operations to occur before everything will be updated
    void preUpdate();

    // Does the update phase of the main loop
    void update(const float dt);
    
    // Defined to allow a set of operations to occur after everything has been updated
    void postUpdate();

    // Does the draw phase of the main loop
    void draw();
};


#endif // APPLICATION_H
