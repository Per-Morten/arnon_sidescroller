/// ArnonSidescroller - by Carl Findahl - 2018

#ifndef COMPONENT_H
#define COMPONENT_H

class GameObject;

class Component
{
private:
    GameObject* m_parent = nullptr;

public:
    Component(GameObject& parent) : m_parent(&parent) {}

    virtual ~Component() = default;
};

#endif // COMPONENT_H
