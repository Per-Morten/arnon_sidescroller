/// ArnonSidescroller - by Carl Findahl - 2018

#ifndef WORLD_H
#define WORLD_H

#include "gameObject.h"

#include <vector>
#include <memory>
#include <type_traits>

class World
{
private:
    // Vector of all entities in the world
    std::vector<std::unique_ptr<GameObject>> m_entities;

    // Next available game object ID
    uint16_t m_nextID = 0;
    
public:

    template<typename T, std::enable_if_t<std::is_base_of_v<GameObject, T>>>
    void spawn()
    {
        m_entities.emplace_back(std::make_unique<T>(m_nextID++));
    }

};


#endif // WORLD_H
