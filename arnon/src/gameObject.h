/// ArnonSidescroller - by Carl Findahl - 2018

#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "component.h"

#include <vector>
#include <memory>
#include <type_traits>

class GameObject
{
private:
    // Vector of components
    std::vector<std::unique_ptr<Component>> m_components;

    // Game Object ID
    uint16_t m_ID = 0;

public:
    GameObject(unsigned ID);

    virtual ~GameObject() = default;

    // Update all components
    void update(float dt);

    // Make UI
    void makeUI();

    // Add a component to the game object
    template<typename T, std::enable_if_t<std::is_base_of_v<Component, T>>>
    Component& addComponent();

};

template<typename T, std::enable_if_t<std::is_base_of_v<Component, T>>>
Component& GameObject::addComponent()
{
    m_components.emplace_back(std::make_unique<T>(*this));
    return *m_components.back();
}

#endif // GAMEOBJECT_H
