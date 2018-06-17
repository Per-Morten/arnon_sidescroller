/// ArnonSidescroller - by Carl Findahl - 2018

#ifndef COMPONENT_H
#define COMPONENT_H

class GameObject;

class Component
{
private:
    // Pointer to gameobject that owns this
    GameObject* m_parent = nullptr;

public:
    Component(GameObject& parent) : m_parent(&parent) {}

    virtual ~Component() = default;

    // Update the component
    virtual void update(float dt) = 0;
};

#endif // COMPONENT_H
