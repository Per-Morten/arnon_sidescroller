# ARNON PLATFORMER

## Gameplay
* Mario like
* 2D sidescroller
* Get from A to B
* Enemies and Obstacles
* Coins / Collectibles

## Scenario
* Startup
    * Start/Continue
    * Level Select
    * Options
* InGame
    * Go towards the right
    * Camera follows player
    * Dodge incomming enemies
    * Collect collectibles
    * Lose lives when getting hit
        * Level restart upon losing all lives
    * Get to goal
* Highscore - local
    * Show highscore
    * Save
    * Go to next level/exit

## Modules
* Scene-management
    * Main menu
    * Pause menu
    * Game
    * Cross-scene gamestate
* Controllers handling / support for gamepad
* Saving / Loading
    * Game
    * Levels
    * Streaming levels
    * Saving in different thread
* Gameplay
    * Game manager
    * Entity Component System
        * Simple, but with id's instead of pointers
* Event System
    * Event-Queue
* Audio
    * Music
    * SFX
* Graphics
    * [Sprites](https://kenney.nl/assets)
    * Text
* Debug/Stats
    * In-game Console
    * Debug Stat
    * Logging (DEBUG, INFO, WARNING, ERROR)
    * Asserts
    * Instrumentation (Timing, not tied to FMT)
    * Scripting(?) - Python
* UI
    * Widgets etc.

## Technology
* Libraries
    * C++17 (Features suported by MSVC - MSVC is now fully conformant)
    * GLFW and OpenGL
    * [FMT - Formatting / Logging](https://github.com/fmtlib/fmt)
    * [Dear ImGui](https://github.com/ocornut/imgui)
        * GLFW Usage example is in the example folder
    * [JSON](https://github.com/nlohmann/json)
* Platforms
    * Linux & Windows
* Buildsystems
    * CMake
* Level editing
    * Tiled
* Versioning
    * Git
* Documentation
    * Doxygen

## Coding Standards

### Naming Convention

#### Functions

`camelCase(int argumentOne);`

#### Classes

`class ClassName;`

##### Integral Member Variables
* Use fixed width integer typedefs
* for member variables, or in other places where size matters
* Function parameters should still be regular int's and uints' unless there are particular reasons.

##### Class Layout
```C++
class Widget
{
private:        // Member Variables

protected:      // Member Variables

public:         // Member Variables

public:         // Member Functions

protected:      // Member Functions

private:        // Member Functions

};
```

##### Class Members

`int m_classMember;`

#### Variables

`int variableName;`

#### Global Variables

`int g_globalVariable;`

#### Static Variables

`int s_staticVariable;`

### Braces

Allman style, på neste linje

```C++
class Name
{
    // Body
};

void function()
{
    // Body
}

while(...)
{
    // Body
}

for(...;...;...)
{
    // Body
}

if(...)
{
    // Body
}
else
{
    // Body
}
```

### Indentation

| Tab Width | Indent Width |
| --------  | --------     |
| 4         | 4            |

Ensure that indentation is set up using spaces!

### Includes

Sort includes in three chunks:

```C++
#include "fil.h"            // Files from our project
#include "fil2.h"

#include <string>           // Files from STL
#include <some_stl_header>

#include "imgui.h"          // External Libs
#include "fmt.h"
```
