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
    * C++17 (Features suported by MSVC)
    * SFML
    * [FMT - Formatting / Logging](https://github.com/fmtlib/fmt)
    * [Dear ImGui](https://github.com/ocornut/imgui)
        * [SFML Binding](https://github.com/eliasdaler/imgui-sfml)
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
* Braces go on next line
* Members
    * m_ for members 
    * g_ for globals
    * s_ for static members
* Standard camelCase
* Indent size 4
* Use fixed width integer typedefs
    * for member variables, or in other places where size matters
    * Function parameters should still be regular int's and uints' unless there are particular reasons.

## Workload
* PMS
    * Entity Component System
* Carl
    * Debug/Stats
    * Event Queue
* Elisa
    * Scene Management
    * Controller handling
